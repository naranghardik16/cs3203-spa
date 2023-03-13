#include <vector>
#include <algorithm>

#include "NextStore.h"
#include "core/cfg_model/CfgNode.h"

NextStore::NextStore() = default;

NextStore::~NextStore() = default;

bool NextStore::hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                                PkbTypes::STATEMENT_NUMBER next_statement_number, std::shared_ptr<CFGStore> cfg_store) {
//  std::shared_ptr<CfgNode> node_of_statement = cfg_store->getCfgNodeFromStatementNumber(statement_number);
//
//  if (!node_of_statement) return false;
//
//  for (std::shared_ptr<CfgNode> child: node_of_statement->GetNodeTrans()) {
//    if (child)
//    if (std::count(child->GetNodeStmts().begin(), child->GetNodeStmts().end(), std::stoi(next_statement_number)) > 0) return true;
//  }
//  return false;
  return true;

}
