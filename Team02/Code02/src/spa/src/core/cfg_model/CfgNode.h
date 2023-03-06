#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "General/SpaException/SemanticErrorException.h"

class CfgNode {
 public:
  typedef std::unordered_map<bool, std::shared_ptr<CfgNode>> BoolToCfgNodeMap;
  typedef std::vector<std::shared_ptr<CfgNode>> CfgNodeContainer;
  void AddTransition(bool is_true, std::shared_ptr<CfgNode> node);
  void AddStmt(int stmt_number);
  void AddParent(const std::shared_ptr<CfgNode> &node);
  BoolToCfgNodeMap GetNodeTrans();
  std::vector<int> GetNodeStmts();
  CfgNodeContainer GetParentNodes();

 private:
  BoolToCfgNodeMap node_trans_;
  std::vector<int> node_stmts_;
  CfgNodeContainer parent_nodes_;
};