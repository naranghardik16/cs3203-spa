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

    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root) ==
    std::unordered_set<std::string>({ "x", "y", "z" }));
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

  SECTION("Basic Arithmetic Expression (One Constant And One Variable) Flattening") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "[+ 11 x]");
    REQUIRE(ExpressionUtil::retrieveAllVariablesFromExpression(root)
                == std::unordered_set<std::string>({ "x" }));
    REQUIRE(ExpressionUtil::retrieveAllConstantsFromExpression(root)
                == std::unordered_set<std::string>({ "11" }));

  }

  SECTION("Flatten Complex Arithmetic Expression with Multiple Levels (Both Variables and Constants)") {
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

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "[/ [* [+ x 1] [- y z]] 5]");
  }

  SECTION("Flatten Complex Expression with Nested Relation Operations and Variables") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> left_args;
    left_args.first = std::make_shared<Variable>("a");
    left_args.second = std::make_shared<Variable>("b");
    auto left = std::make_shared<RelationalOperation>("<", left_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> right_args;
    right_args.first = std::make_shared<Variable>("c");
    right_args.second = std::make_shared<Variable>("d");
    auto right = std::make_shared<RelationalOperation>("==", right_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args;
    root_args.first = left;
    root_args.second = right;

    auto root = std::make_shared<ConditionalOperation>("&&", root_args);

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "[&& [< a b] [== c d]]");
  }

  SECTION("Flatten Expression with Nested Logical and Relation Operations and Constants") {
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> left_args;
    left_args.first = std::make_shared<Constant>("1");
    left_args.second = std::make_shared<Constant>("2");
    auto left = std::make_shared<RelationalOperation>(">", left_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> right_args;
    right_args.first = std::make_shared<Constant>("3");
    right_args.second = std::make_shared<Constant>("4");
    auto right = std::make_shared<RelationalOperation>("<=", right_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args;
    root_args.first = left;
    root_args.second = right;

    auto root = std::make_shared<ConditionalOperation>("||", root_args);

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "[|| [> 1 2] [<= 3 4]]");
  }

  SECTION("Flatten Expression with Nested Logical Operations and Constants") {
    auto left = std::make_shared<Constant>("true");
    auto right = std::make_shared<Constant>("false");
    auto root = std::make_shared<ConditionalOperation>("&&", std::make_pair(left, right));
    root = std::make_shared<ConditionalOperation>("||", std::make_pair(root, left));

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "[|| [&& true false] true]");
  }

  SECTION("Flattening Singleton (One Constant)") {
    std::shared_ptr<Expression> root;
    root = std::make_shared<Constant>("7");

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "7");
  }

  SECTION("Flattening Singleton (One Variable)") {
    std::shared_ptr<Expression> root;
    root = std::make_shared<Variable>("a");

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "a");
  }

  SECTION("Flatten Expression with Nested Logical and Relation Operations and Mixed Constants and Variables") {
    auto a = std::make_shared<Variable>("a");
    auto b = std::make_shared<Variable>("b");
    auto c = std::make_shared<Variable>("c");
    auto d = std::make_shared<Variable>("d");
    auto e = std::make_shared<Variable>("e");

    auto left_args1 = std::make_pair(a, std::make_shared<Constant>("10"));
    auto left1 = std::make_shared<RelationalOperation>(">", left_args1);
    auto right_args1 = std::make_pair(b, std::make_shared<Constant>("20"));
    auto right1 = std::make_shared<RelationalOperation>("<=", right_args1);
    auto mid1 = std::make_shared<ConditionalOperation>("||", std::make_pair(left1, right1));

    auto left_args2 = std::make_pair(c, std::make_shared<Constant>("5"));
    auto left2 = std::make_shared<RelationalOperation>(">=", left_args2);
    auto right_args2 = std::make_pair(d, std::make_shared<Constant>("15"));
    auto right2 = std::make_shared<RelationalOperation>("<", right_args2);
    auto mid_left2 = std::make_shared<ConditionalOperation>("&&", std::make_pair(left2, right2));

    auto mid_right = std::make_shared<Variable>("e");
    auto mid = std::make_shared<ConditionalOperation>("&&", std::make_pair(mid_left2, mid_right));
    auto root = std::make_shared<ConditionalOperation>("||", std::make_pair(mid, mid1));

    REQUIRE(ExpressionUtil::prefixFlatten(root) == "[|| [&& [&& [>= c 5] [< d 15]] e] [|| [> a 10] [<= b 20]]]");
  }
}

