#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class FollowsStore {
 public:
  FollowsStore();

  ~FollowsStore();

  void addFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1, PkbTypes::STATEMENT_NUMBER statement_number_2);

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllFollowsPairs();

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllFollowsStarPairs();

  bool hasFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1, PkbTypes::STATEMENT_NUMBER statement_number_2);

  bool hasAnyFollowsRelation();

 private:
  OneToOneStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_store_;
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_star_store_;
};

