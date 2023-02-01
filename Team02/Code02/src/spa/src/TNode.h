#pragma once

#include <string>

class TNode {
 public:
  enum class Operator {
    UNK,
    PLUS,
    MINUS,
    DIVIDE,
    MULTIPLY,
    MOD
  };

  TNode::Operator op = TNode::Operator::UNK;

  std::string value = "";

  TNode *left_node = nullptr;
  TNode *right_node = nullptr;

  TNode();
  TNode(TNode::Operator op);
  TNode(std::string value);

  friend bool isEqual(const TNode &one, const TNode &two);

  friend bool isSubTree(const TNode &one, const TNode &two);
};
