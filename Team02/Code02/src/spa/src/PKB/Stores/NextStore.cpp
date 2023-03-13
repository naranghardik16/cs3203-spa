#include <algorithm>
#include <string>

#include "NextStore.h"
#include "core/cfg_model/CfgNode.h"

NextStore::NextStore() = default;

NextStore::~NextStore() = default;

void NextStore::setProcedureToCfgRootNodeMap(std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> ptonode) {
  this->procedure_name_to_cfg_node_map_ = ptonode;
}

void NextStore::setStatementNumberToCfgRootNodeMap(std::unordered_map<PkbTypes::STATEMENT_NUMBER,
                                                           std::shared_ptr<CfgNode>> stonode) {
  this->statement_number_to_cfg_node_map_ = stonode;
}

void NextStore::extractNextRelations() {
  for (const auto& p: this->procedure_name_to_cfg_node_map_) {

    // bfs to get all the next relations
    std::unordered_set<std::string> visited;

    while (!queue.empty()) {
      std::shared_ptr<CfgNode> current = p.second;
      std::vector<int> s = current->GetNodeStmts();

      for (int i = 0; i < s.size() - 1; ++i) {
        this->next_store_.insert(std::to_string(s[i]), std::to_string(s[i + 1]));
      }

    }
  }
}

//bool NextStore::hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
//                                PkbTypes::STATEMENT_NUMBER next_statement_number) {

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
//}
