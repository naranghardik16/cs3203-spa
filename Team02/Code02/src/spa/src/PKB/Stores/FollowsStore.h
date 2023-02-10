#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class FollowsStore {
 public:
  FollowsStore();

  ~FollowsStore();

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllFollowsPairs();

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllFollowsStarPairs();

  bool hasFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1_, PkbTypes::STATEMENT_NUMBER statement_number_2_);

  bool hasAnyFollowsRelation();

 private:
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_store_;
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> follows_star_store_;
};

