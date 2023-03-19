#include <catch.hpp>
#include <memory>
#include <string>
#include <unordered_set>

#include "PKB/Stores/ControlFlowStore.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Control Flow Store") {
  SECTION("Basic Conditional Statements for If and While") {
    auto control_flow_store = new ControlFlowStore();

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Variable>("x");
    arguments.second = std::make_shared<Constant>("1");

    auto root = std::make_shared<ConditionalOperation>(">", arguments);

    control_flow_store->AddWhileStatementAndExpression("1", root);
    control_flow_store->AddIfStatementAndExpression("2", root);

    REQUIRE(control_flow_store->GetIfStatementsFromExpression(root) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));
    REQUIRE(control_flow_store->GetWhileStatementsFromExpression(root) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
    REQUIRE(control_flow_store->GetExpressionFromIfStatement("2") == root);
    REQUIRE(control_flow_store->GetExpressionFromWhileStatement("1") == root);
  }

  SECTION("Compound Conditional Statements for If and While") {
    auto control_flow_store = new ControlFlowStore();

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> left_subtree_args;
    left_subtree_args.first = std::make_shared<Variable>("x");
    left_subtree_args.second = std::make_shared<Variable>("y");
    auto left_subtree1 = std::make_shared<ArithmeticOperation>("/", left_subtree_args);

    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> root_args1;
    root_args1.first = left_subtree1;
    root_args1.second = std::make_shared<Variable>("z");

    auto root1 = std::make_shared<ConditionalOperation>("<=", root_args1);

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

    control_flow_store->AddWhileStatementAndExpression("1", root);
    control_flow_store->AddIfStatementAndExpression("4", root);
    control_flow_store->AddWhileStatementAndExpression("3", root1);
    control_flow_store->AddIfStatementAndExpression("9", root1);

    REQUIRE(control_flow_store->GetIfStatementsFromExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "4" }));
    REQUIRE(control_flow_store->GetWhileStatementsFromExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
    REQUIRE(control_flow_store->GetExpressionFromIfStatement("4") == root);
    REQUIRE(control_flow_store->GetExpressionFromWhileStatement("1") == root);

    REQUIRE(control_flow_store->GetIfStatementsFromExpression(root1) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "9" }));
    REQUIRE(control_flow_store->GetWhileStatementsFromExpression(root1) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "3" }));
    REQUIRE(control_flow_store->GetExpressionFromIfStatement("9") == root1);
    REQUIRE(control_flow_store->GetExpressionFromWhileStatement("3") == root1);
  }
}

