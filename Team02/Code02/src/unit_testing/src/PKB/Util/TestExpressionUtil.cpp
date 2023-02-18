#include <catch.hpp>
#include <string>

#include "PKB/Util/ExpressionUtil.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Expression Util") {
  SECTION("Basic Expression") {
    std::pair<Expression*, Expression*> arguments;
    arguments.first = new Constant("11");
    arguments.second = new Variable("x");
    auto *root = new ArithmeticOperation("+", arguments);

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root) == std::unordered_set<std::string>({ "x" }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root) == std::unordered_set<std::string>({ "11" }));
  }

  SECTION("Complex Expression") {
    std::pair<Expression*, Expression*> left_subtree_args;
    left_subtree_args.first = new Variable("x");
    left_subtree_args.second = new Variable("y");
    auto *left_subtree = new ArithmeticOperation("/", left_subtree_args);
    std::pair<Expression*, Expression*> root_args;
    root_args.first = left_subtree;
    root_args.second = new Variable("z");
    auto *root = new ArithmeticOperation("*", root_args);

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root) == std::unordered_set<std::string>({ "x", "y", "z" }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root) == std::unordered_set<std::string>({ }));
  }
}

