#pragma once

#include "PKB/Types//PkbTypes.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class ParentStore {
 public:
  ParentStore();
  ~ParentStore();

  void addParentRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllParentPairs();

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllParentStarPairs();

  bool hasParentRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  bool hasParentStarRelation(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);

  bool hasAnyParentRelation();

  bool hasAnyParentStarRelation();

  bool hasParentStar(PkbTypes::STATEMENT_NUMBER statement);

  bool hasParentStarBy(PkbTypes::STATEMENT_NUMBER statement);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllParents();

  PkbTypes::STATEMENT_NUMBER retrieveAllParents(PkbTypes::STATEMENT_NUMBER statement);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllChildren();

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllChildren(PkbTypes::STATEMENT_NUMBER statement);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllAncestors();

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllAncestors(PkbTypes::STATEMENT_NUMBER statement);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllDescendants();

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> retrieveAllDescendants(PkbTypes::STATEMENT_NUMBER statement);

 private:
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> parent_store_;
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> parent_star_store_;
//  void dfs(PkbTypes::STATEMENT_NUMBER first_statement, PkbTypes::STATEMENT_NUMBER second_statement);
};