#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "General/SpaException/SemanticErrorException.h"

class CfgNode {
 public:
  void AddTransition(bool is_true, std::shared_ptr<CfgNode> node);
  void AddStmt(int stmt_number);
  void AddParent(const std::shared_ptr<CfgNode> &node);
 private:
  std::unordered_map<bool, std::shared_ptr<CfgNode>> node_trans_;
  std::vector<int> node_stmts_;
  std::vector<std::shared_ptr<CfgNode>> parent_nodes_;
};