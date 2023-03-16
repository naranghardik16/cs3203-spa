#include "ClauseGroup.h"

void ClauseGroup::AddClause(const std::shared_ptr<ClauseSyntax>& clause) {
  clause_list_.push_back(clause);
  synonyms_.insert(clause->syn_.begin(), clause->syn_.end());
}

bool ClauseGroup::HasSelectedSynonym(const SelectedSynonymTuple& synonym_tuple) {
  return std::any_of(synonym_tuple.begin(), synonym_tuple.end(),
                     [this](const std::string& syn)
                     {return synonyms_.find(QueryUtil::GetSynonymFromAttrRef(syn)) != synonyms_.end();});
}

ClauseSyntaxPtrList ClauseGroup::GetClauseList() {
  return clause_list_;
}

int ClauseGroup::GetSize() {
  return static_cast<int>(synonyms_.size());
}

bool IsClauseAccessible(std::unordered_set<std::string> accessible_syn_set, std::unordered_set<std::string>
    clause_syn_set) {
  bool is_accessible = false;
  for (auto syn : accessible_syn_set) {
    if (clause_syn_set.find(syn) != clause_syn_set.end()) {
      is_accessible = true;
      break;
    }
  }
  return is_accessible;
}

void ClauseGroup::SortClauses(Map &declaration_map) {
  std::vector<std::shared_ptr<ClauseSyntax>> sorted_clause_list;

  CompareScore comp(declaration_map);
  // Creates a min heap
  std::priority_queue <std::shared_ptr<ClauseSyntax>, vector<std::shared_ptr<ClauseSyntax>>,
  CompareScore> pq(declaration_map);
  for (auto clause : clause_list_) {
    pq.push(clause);
  }

  // Get clause with lowest score as starting clause
  auto clause = pq.top();
  sorted_clause_list.push_back(clause);
  pq.pop();

  // keep track of all accessible syns
  std::unordered_set<std::string> accessible_syn_set;

  // Track clauses that were filtered out but are to be re-inserted into the PQ
  std::vector<std::shared_ptr<ClauseSyntax>> filtered_clauses;
  while (sorted_clause_list.size() < clause_list_.size()) {
    // Only add the next best clause that can be accessed from the last clause in sorted list
    auto last_clause = sorted_clause_list.back();
    for (auto syn : last_clause->syn_) {
      accessible_syn_set.insert(syn);
    }
    while (!pq.empty()) {
      auto clause = pq.top();
      pq.pop();
      auto clause_syn_set = clause->syn_;
      // accessible if they share any synonyms
      bool is_accessible = IsClauseAccessible(accessible_syn_set, clause_syn_set);
      if (is_accessible) {
        sorted_clause_list.push_back(clause);
        break;
      } else {
        filtered_clauses.push_back(clause);
      }
    }
    for (auto clause : filtered_clauses) {
      pq.push(clause);
    }
    filtered_clauses.clear();
  }

  clause_list_ = sorted_clause_list;
}
