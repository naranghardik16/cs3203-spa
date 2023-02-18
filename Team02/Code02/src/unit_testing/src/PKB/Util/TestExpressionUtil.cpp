
#include <catch.hpp>
#include <string>
#include <unordered_set>
#include <memory>

#include "PKB/Util/ExpressionUtil.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Expression Util") {
  SECTION("Basic Expression") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");
    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root)
                == std::unordered_set<std::string>({"x"}));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root)
                == std::unordered_set<std::string>({"11"}));
  }

  SECTION("Complex Expression") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> left_subtree_args;
    left_subtree_args.first = std::make_shared<Variable>("x");
    left_subtree_args.second = std::make_shared<Variable>("y");
    auto left_subtree = std::make_shared<ArithmeticOperation>("/", left_subtree_args);
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args;
    root_args.first = left_subtree;
    root_args.second = std::make_shared<Variable>("z");
    auto root = std::make_shared<ArithmeticOperation>("*", root_args);

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root) == std::unordered_set<std::string>({ "x", "y", "z" }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root) == std::unordered_set<std::string>({ }));
  }
}

