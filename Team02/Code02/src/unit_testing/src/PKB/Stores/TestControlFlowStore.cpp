#include <catch.hpp>

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "core/model/Expression.h"
#include "PKB/Stores/ControlFlowStore.h"
#include "PKB/Types/PkbTypes.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Control Flow Store") {
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef std::pair<ExpressionPtr, ExpressionPtr> ExpressionPtrPair;

  SECTION("Basic Conditional Statements for If and While") {
    auto control_flow_store = new ControlFlowStore();

    ExpressionPtrPair arguments;
    arguments.first = std::make_shared<Variable>("x");
    arguments.second = std::make_shared<Constant>("1");

    auto root = std::make_shared<ConditionalOperation>(">", arguments);

    control_flow_store->AddWhileStatementAndExpression("1", root);
    control_flow_store->AddIfStatementAndExpression("2", root);

    REQUIRE(control_flow_store->GetIfStatementsFromExpression(root) == StatementNumberSet({"2"}));
    REQUIRE(control_flow_store->GetWhileStatementsFromExpression(root) == StatementNumberSet({"1"}));
    REQUIRE(control_flow_store->GetExpressionFromIfStatement("2") == root);
    REQUIRE(control_flow_store->GetExpressionFromWhileStatement("1") == root);
  }

  SECTION("Compound Conditional Statements for If and While") {
    auto control_flow_store = new ControlFlowStore();

    ExpressionPtrPair left_subtree_args;
    left_subtree_args.first = std::make_shared<Variable>("x");
    left_subtree_args.second = std::make_shared<Variable>("y");
    auto left_subtree1 = std::make_shared<ArithmeticOperation>("/", left_subtree_args);

    ExpressionPtrPair root_args1;
    root_args1.first = left_subtree1;
    root_args1.second = std::make_shared<Variable>("z");

    auto root1 = std::make_shared<ConditionalOperation>("<=", root_args1);

    ExpressionPtrPair ll1;
    ExpressionPtrPair ll2;

    ll1.first = std::make_shared<Variable>("x");
    ll1.second = std::make_shared<Constant>("1");
    ll2.first = std::make_shared<Variable>("y");
    ll2.second = std::make_shared<Variable>("z");

    auto l1 = std::make_shared<ArithmeticOperation>("+", ll1);
    auto l2 = std::make_shared<ArithmeticOperation>("-", ll2);

    ExpressionPtrPair left_subtree;

    left_subtree.first = l1;
    left_subtree.second = l2;

    auto f = std::make_shared<ArithmeticOperation>("*", left_subtree);

    ExpressionPtrPair root_args;
    root_args.first = f;
    root_args.second = std::make_shared<Constant>("5");

    auto root = std::make_shared<ArithmeticOperation>("/", root_args);

    control_flow_store->AddWhileStatementAndExpression("1", root);
    control_flow_store->AddIfStatementAndExpression("4", root);
    control_flow_store->AddWhileStatementAndExpression("3", root1);
    control_flow_store->AddIfStatementAndExpression("9", root1);

    REQUIRE(control_flow_store->GetIfStatementsFromExpression(root) == StatementNumberSet({"4"}));
    REQUIRE(control_flow_store->GetWhileStatementsFromExpression(root) == StatementNumberSet({"1"}));
    REQUIRE(control_flow_store->GetExpressionFromIfStatement("4") == root);
    REQUIRE(control_flow_store->GetExpressionFromWhileStatement("1") == root);

    REQUIRE(control_flow_store->GetIfStatementsFromExpression(root1) == StatementNumberSet({"9"}));
    REQUIRE(control_flow_store->GetWhileStatementsFromExpression(root1) == StatementNumberSet({"3"}));
    REQUIRE(control_flow_store->GetExpressionFromIfStatement("9") == root1);
    REQUIRE(control_flow_store->GetExpressionFromWhileStatement("3") == root1);
  }
}

