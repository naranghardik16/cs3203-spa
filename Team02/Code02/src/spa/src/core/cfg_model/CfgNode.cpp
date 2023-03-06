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

std::vector<int> CfgNode::GetNodeStmts() {
  return node_stmts_;
}

CfgNode::BoolToCfgNodeMap CfgNode::GetNodeTrans() {
  return node_trans_;
}

CfgNode::CfgNodeContainer CfgNode::GetParentNodes() {
  return parent_nodes_;
}
