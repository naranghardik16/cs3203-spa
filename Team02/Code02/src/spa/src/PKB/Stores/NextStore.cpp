#include <algorithm>

#include "NextStore.h"
#include "core/cfg_model/CfgNode.h"

NextStore::NextStore() = default;

NextStore::~NextStore() = default;

bool NextStore::hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                                PkbTypes::STATEMENT_NUMBER next_statement_number, std::shared_ptr<CFGStore> cfg_store) {
//  std::shared_ptr<CfgNode> node_of_statement = cfg_store->getCfgNodeFromStatementNumber(statement_number);
//  if (!node_of_statement) return false;
//
//  // true transition statements
//  std::shared_ptr<CfgNode> true_trans = node_of_statement->GetNodeTrans()[true];
//  std::shared_ptr<CfgNode> false_trans = node_of_statement->GetNodeTrans()[false];
//
//  if (std::count(true_trans->GetNodeStmts().begin(),
//                 true_trans->GetNodeStmts().end(), std::stoi(next_statement_number)) > 0 ||
//                 std::count(false_trans->GetNodeStmts().begin(),
//                        false_trans->GetNodeStmts().end(), std::stoi(next_statement_number)) > 0) {
//    return true;
//  } else {
//    return false;
//  }
}
