#include <catch.hpp>
#include <memory>
#include <string>
#include <unordered_set>

#include "PKB/Util/ExpressionUtil.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Expression Util") {
  SECTION("Singleton (One Constant)") {
    std::shared_ptr<Expression> root;
    root = std::make_shared<Constant>("7");

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root)
                == std::unordered_set<std::string>({ }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root)
                == std::unordered_set<std::string>({ "7" }));
  }

  SECTION("Singleton (One Variable)") {
    std::shared_ptr<Expression> root;
    root = std::make_shared<Variable>("a");

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root)
                == std::unordered_set<std::string>({ "a" }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root)
                == std::unordered_set<std::string>({  }));
  }

  SECTION("Basic Arithmetic Expression (One Constant And One Variable)") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root)
                == std::unordered_set<std::string>({ "x" }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root)
                == std::unordered_set<std::string>({ "11" }));
  }

  SECTION("Complex Arithmetic Expression with One Level (Only Variables)") {
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

  SECTION("Complex Arithmetic Expression with One Level (Only Constants)") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> right_subtree_args;
    right_subtree_args.first = std::make_shared<Constant>("9");
    right_subtree_args.second = std::make_shared<Constant>("4");
    auto right_subtree = std::make_shared<ArithmeticOperation>("-", right_subtree_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args;
    root_args.first = std::make_shared<Constant>("8");
    root_args.second = right_subtree;

    auto root = std::make_shared<ArithmeticOperation>("*", root_args);

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root) == std::unordered_set<std::string>({ }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root) ==
    std::unordered_set<std::string>({ "9", "4", "8" }));
  }

  SECTION("Complex Arithmetic Expression with Multiple Levels (Both Variables and Constants)") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> ll1;
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> ll2;

    ll1.first = std::make_shared<Variable>("x");
    ll1.second = std::make_shared<Constant>("1");
    ll2.first = std::make_shared<Variable>("y");
    ll2.second = std::make_shared<Variable>("z");

    auto l1 = std::make_shared<ArithmeticOperation>("+", ll1);
    auto l2 = std::make_shared<ArithmeticOperation>("-", ll2);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> left_subtree;

    left_subtree.first = l1;
    left_subtree.second = l2;

    auto f =  std::make_shared<ArithmeticOperation>("*", left_subtree);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args;
    root_args.first = f;
    root_args.second = std::make_shared<Constant>("5");

    auto root = std::make_shared<ArithmeticOperation>("/", root_args);

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root) == std::unordered_set<std::string>({ "x", "y", "z" }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root) == std::unordered_set<std::string>({ "1", "5" }));
  }
}

