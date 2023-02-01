#include "catch.hpp"
#include "TNode.h"

TEST_CASE("Check if the TNode class is working as expected") {
  TNode *T1 = new TNode("y");
  TNode *T2 = new TNode("z");
  TNode *T3 = new TNode(TNode::Operator::MULTIPLY);
  T3->left_node = T1;
  T3->right_node = T2;

// "x + y * z"
  TNode *T4 = new TNode("x");
  TNode *T5 = new TNode(TNode::Operator::PLUS);
  T5->left_node = T4;
  T5->right_node = T3;

// T6 is T3.
  TNode *T6 = new TNode(TNode::Operator::MULTIPLY);
  T6->left_node = new TNode("y");
  T6->right_node = new TNode("z");

  REQUIRE(T1->op == TNode::Operator::UNK);
  REQUIRE(T2->op == TNode::Operator::UNK);
  REQUIRE(T4->op == TNode::Operator::UNK);
}
