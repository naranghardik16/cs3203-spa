#include "TNode.h"

#include <utility>

TNode::TNode() = default;

TNode::TNode(TNode::Operator op): op(op) {}

TNode::TNode(std::string value): value(std::move(value)) {}

bool isEqual(const TNode &one, const TNode &two) {
  if (one.op == TNode::Operator::UNK) {
    return one.value == two.value;
  } else {
    bool are_operators_equal = one.op == two.op;
    bool left_sub_tree_equality = isEqual(*one.left_node, *two.left_node);
    bool right_sub_tree_equality = isEqual(*one.right_node, *two.right_node);

    return are_operators_equal && left_sub_tree_equality && right_sub_tree_equality;
  }
}

bool isSubTree(const TNode &one, const TNode &two) {
  if (isEqual(one, two)) {
    return true;
  } else if (one.op == TNode::Operator::UNK) {
    return false;
  } else {
    return isSubTree(*one.left_node, two) || isSubTree(*one.right_node, two);
  }
}

