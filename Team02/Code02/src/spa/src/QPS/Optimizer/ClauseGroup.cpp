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
