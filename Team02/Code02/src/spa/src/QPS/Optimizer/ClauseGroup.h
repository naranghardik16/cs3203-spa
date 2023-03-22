#pragma once

#include "QPS/Clause/ClauseSyntax.h"
#include <algorithm>
#include <unordered_set>
#include <queue>
#include "CompareScore.h"

class ClauseGroup {
 private:
  ClauseSyntaxPtrList clause_list_;
  std::unordered_set<std::string> synonyms_;

 public:
  ClauseGroup() = default;
  void AddClause(const std::shared_ptr<ClauseSyntax>& clause);
  bool HasSelectedSynonym(const SelectedSynonymTuple& synonym_tuple);
  ClauseSyntaxPtrList GetClauseList();
  ClauseSyntaxPtrList GetSortedClauses(Map &declaration_map);
  int GetSize();
};

