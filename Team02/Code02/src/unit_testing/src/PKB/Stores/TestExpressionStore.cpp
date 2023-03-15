#include <catch.hpp>
#include <memory>
#include <string>
#include <unordered_set>

#include "PKB/Stores/ExpressionStore.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Expression Store") {
  SECTION("Singleton (One Constant)") {
    auto expression_store = new ExpressionStore();

    std::shared_ptr<Expression> root;
    root = std::make_shared<Constant>("7");

    expression_store->addExpression(root);

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root) == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root) ==
    std::unordered_set<PkbTypes::CONSTANT>({ "7" }));
  }

  SECTION("Singleton (One Variable)") {
    auto expression_store = new ExpressionStore();

    std::shared_ptr<Expression> root;
    root = std::make_shared<Variable>("x");

    expression_store->addExpression(root);

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root) ==
    std::unordered_set<PkbTypes::VARIABLE>({ "x" }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root) == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Simple Arithmetic Expression (One Variable and One Constant)") {
    auto expression_store = new ExpressionStore();

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    expression_store->addExpression(root);

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root) ==
        std::unordered_set<PkbTypes::VARIABLE>({ "x" }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root) ==
    std::unordered_set<PkbTypes::CONSTANT>({ "11" }));
  }

  SECTION("Complex Arithmetic Expression with One Level (Only Variables)") {
    auto expression_store = new ExpressionStore();

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> left_subtree_args;
    left_subtree_args.first = std::make_shared<Variable>("x");
    left_subtree_args.second = std::make_shared<Variable>("y");
    auto left_subtree = std::make_shared<ArithmeticOperation>("/", left_subtree_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args;
    root_args.first = left_subtree;
    root_args.second = std::make_shared<Variable>("z");

    auto root = std::make_shared<ArithmeticOperation>("*", root_args);

    expression_store->addExpression(root);

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root) ==
        std::unordered_set<PkbTypes::VARIABLE>({ "x", "y", "z" }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root) ==
        std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Complex Arithmetic Expression with One Level (Only Constants)") {
    auto expression_store = new ExpressionStore();

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> right_subtree_args;
    right_subtree_args.first = std::make_shared<Constant>("9");
    right_subtree_args.second = std::make_shared<Constant>("4");
    auto right_subtree = std::make_shared<ArithmeticOperation>("-", right_subtree_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args;
    root_args.first = std::make_shared<Constant>("8");
    root_args.second = right_subtree;

    auto root = std::make_shared<ArithmeticOperation>("*", root_args);

    expression_store->addExpression(root);

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root) ==
        std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root) ==
        std::unordered_set<PkbTypes::CONSTANT>({ "9", "4", "8" }));
  }

  SECTION("Multiple Expressions") {
    auto expression_store = new ExpressionStore();

    std::shared_ptr<Expression> root1;
    root1 = std::make_shared<Constant>("69");

    std::shared_ptr<Expression> root2;
    root2 = std::make_shared<Variable>("hardik");

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Variable>("c");
    arguments.second = std::make_shared<Variable>("x");

    auto root3 = std::make_shared<ArithmeticOperation>("-", arguments);

    arguments.first = root2;
    arguments.second = root3;
    auto root4 = std::make_shared<ArithmeticOperation>("/", arguments);

    arguments.first = root4;
    arguments.second = root3;
    auto root5 = std::make_shared<ArithmeticOperation>("-", arguments);

    expression_store->addExpression(root1);
    expression_store->addExpression(root2);
    expression_store->addExpression(root3);
    expression_store->addExpression(root4);
    expression_store->addExpression(root5);

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root1) ==
        std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root1) ==
        std::unordered_set<PkbTypes::CONSTANT>({ "69" }));

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root2) ==
        std::unordered_set<PkbTypes::VARIABLE>({ "hardik" }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root2) ==
        std::unordered_set<PkbTypes::CONSTANT>({ }));

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root3) ==
        std::unordered_set<PkbTypes::VARIABLE>({ "x", "c" }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root3) ==
        std::unordered_set<PkbTypes::CONSTANT>({ }));

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root4) ==
        std::unordered_set<PkbTypes::VARIABLE>({ "hardik", "x", "c" }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root4) ==
        std::unordered_set<PkbTypes::CONSTANT>({ }));

    REQUIRE(expression_store->retrieveVariablesOfTheExpression(root5) ==
        std::unordered_set<PkbTypes::VARIABLE>({ "hardik", "x", "c" }));
    REQUIRE(expression_store->retrieveConstantsOfTheExpression(root5) ==
        std::unordered_set<PkbTypes::CONSTANT>({ }));
  }
}
