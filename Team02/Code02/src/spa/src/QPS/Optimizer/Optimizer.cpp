#include "Optimizer.h"

std::string Optimizer::Find(std::string syn) {
  if (map_.find(syn) == map_.end()) {
    map_[syn] = syn;
    return syn;
  }
  if (map_[syn] == syn) {
    return syn;
  } else {
    map_[syn] = Find(map_[syn]);
    return map_[syn];
  }
}

void Optimizer::Union(const std::shared_ptr<ClauseSyntax>& clause) {
  auto &syn = clause->syn_;
  if (syn.empty()) {
    return;
  } else if (syn.size() == 1) {
    Find(*syn.begin());
  } else {
    std::string first = Find(*syn.begin());
    std::string second = Find(*(++syn.begin()));
    map_[second] = first;
  }
}

std::vector<std::shared_ptr<ClauseGroup>> Optimizer::GetClauseGroups(const ClauseSyntaxPtrList& clause_list) {
  for (auto &kClause : clause_list) {
    Union(kClause);
  }
  std::unordered_map<std::string, std::shared_ptr<ClauseGroup>> groups;

  for (const auto &kClause : clause_list) {
    auto &syn = kClause->syn_;
    if (syn.empty()) {
      if (groups.find("") == groups.end()) {
        groups[""] = std::make_shared<ClauseGroup>();
      }
      groups[""]->AddClause(kClause);
    } else {
      std::string parent = Find(*syn.begin());
      if (groups.find(parent) == groups.end()) {
        groups[parent] = std::make_shared<ClauseGroup>();
      }
      groups[parent]->AddClause(kClause);
    }
  }

  std::vector<std::shared_ptr<ClauseGroup>> result;
  for (auto &kEntry : groups) {
    result.push_back(kEntry.second);
  }
  std::sort(result.begin(), result.end(),
            [] (const std::shared_ptr<ClauseGroup>& grp_1, const std::shared_ptr<ClauseGroup>& grp_2)
            {return grp_1->GetSize() < grp_2->GetSize();});
  return result;
}
