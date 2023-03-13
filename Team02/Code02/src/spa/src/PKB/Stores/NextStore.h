#pragma once

#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"
#include "CFGStore.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class NextStore {
 public:
  NextStore();

  ~NextStore();

  void setProcedureToCfgRootNodeMap(std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> ptonode);

  void setStatementNumberToCfgRootNodeMap(std::unordered_map<PkbTypes::STATEMENT_NUMBER,
                                          std::shared_ptr<CfgNode>> stonode);

  void extractNextRelations();

  bool hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                       PkbTypes::STATEMENT_NUMBER next_statement_number);

  bool hasAnyNextRelation();

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  retrieveAllNextPairs();

  bool hasNext(PkbTypes::STATEMENT_NUMBER statement_number);

  bool hasNextBy(PkbTypes::STATEMENT_NUMBER statement_number);

//  bool hasNextStarRelation(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::STATEMENT_NUMBER next_statement_number);
//
//  bool hasAnyNextStarRelation();
//
//  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
//  retrieveAllNextStarPairs();

 private:
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER> next_store_;
  std::unordered_map<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<CfgNode>> statement_number_to_cfg_node_map_;
  std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> procedure_name_to_cfg_node_map_;
};

