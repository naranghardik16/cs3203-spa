#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"
#include "CFGStore.h"
#include "PKB/AbstractDataModels/OneToManyStore.h"

class NextStore {
 public:
  NextStore();

  ~NextStore();

  bool hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                       PkbTypes::STATEMENT_NUMBER next_statement_number, std::shared_ptr<CFGStore> cfg_store);

  bool hasAnyNextRelation();

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllNextPairs();

  bool hasNextStarRelation(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::STATEMENT_NUMBER next_statement_number);

  bool hasAnyNextStarRelation();

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllNextStarPairs();

 private:
  OneToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> next_store_;
};

