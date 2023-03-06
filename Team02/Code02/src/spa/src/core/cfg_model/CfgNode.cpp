#include "CfgNode.h"

void CfgNode::AddTransition(bool is_true, std::shared_ptr<CfgNode> node) {
  if (node_trans_.count(is_true) < 1) {
    throw SemanticErrorException(
        "CFGNode already has a transition node here");
  }
  node_trans_[is_true] = std::move(node);
}

void CfgNode::AddStmt(int stmt_number) {
  node_stmts_.push_back(stmt_number);
}

void CfgNode::AddParent(const std::shared_ptr<CfgNode> &node) {
  parent_nodes_.emplace_back(node);
}