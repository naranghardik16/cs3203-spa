#include <catch.hpp>

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "core/model/Expression.h"
#include "PKB/Stores/ExpressionStore.h"
#include "PKB/Types/PkbTypes.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Expression Store") {
  typedef PkbTypes::VARIABLE PkbVariable;
  typedef PkbTypes::CONSTANT PkbConstant;
  typedef std::unordered_set<PkbVariable> VariableSet;
  typedef std::unordered_set<PkbConstant> ConstantSet;
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef std::pair<ExpressionPtr, ExpressionPtr> ExpressionPtrPair;

  SECTION("Singleton (One Constant)") {
    auto expression_store = new ExpressionStore();

    ExpressionPtr root;
    root = make_shared<Constant>("7");

    expression_store->AddExpression(root);

    REQUIRE(expression_store->GetVariablesFromExpression(root) == VariableSet({}));
    REQUIRE(expression_store->GetConstantsFromExpression(root) == ConstantSet({"7"}));
  }

  SECTION("Singleton (One Variable)") {
    auto expression_store = new ExpressionStore();

    ExpressionPtr root;
    root = make_shared<Variable>("x");

    expression_store->AddExpression(root);

    REQUIRE(expression_store->GetVariablesFromExpression(root) == VariableSet({"x"}));
    REQUIRE(expression_store->GetConstantsFromExpression(root) == ConstantSet({}));
  }

  SECTION("Simple Arithmetic Expression (One Variable and One Constant)") {
    auto expression_store = new ExpressionStore();

    std::pair<ExpressionPtr, ExpressionPtr> arguments;
    arguments.first = make_shared<Constant>("11");
    arguments.second = make_shared<Variable>("x");

    auto root = make_shared<ArithmeticOperation>("+", arguments);

    expression_store->AddExpression(root);

    REQUIRE(expression_store->GetVariablesFromExpression(root) == VariableSet({"x"}));
    REQUIRE(expression_store->GetConstantsFromExpression(root) == ConstantSet({"11"}));
  }

  SECTION("Complex Arithmetic Expression with One Level (Only Variables)") {
    auto expression_store = new ExpressionStore();

    std::pair<ExpressionPtr, ExpressionPtr> left_subtree_args;
    left_subtree_args.first = make_shared<Variable>("x");
    left_subtree_args.second = make_shared<Variable>("y");
    auto left_subtree = make_shared<ArithmeticOperation>("/", left_subtree_args);

    std::pair<ExpressionPtr, ExpressionPtr> root_args;
    root_args.first = left_subtree;
    root_args.second = make_shared<Variable>("z");

    auto root = make_shared<ArithmeticOperation>("*", root_args);

    expression_store->AddExpression(root);

    REQUIRE(expression_store->GetVariablesFromExpression(root) == VariableSet({"x", "y", "z"}));
    REQUIRE(expression_store->GetConstantsFromExpression(root) == ConstantSet({}));
  }

  SECTION("Complex Arithmetic Expression with One Level (Only Constants)") {
    auto expression_store = new ExpressionStore();

    std::pair<ExpressionPtr, ExpressionPtr> right_subtree_args;
    right_subtree_args.first = make_shared<Constant>("9");
    right_subtree_args.second = make_shared<Constant>("4");
    auto right_subtree = make_shared<ArithmeticOperation>("-", right_subtree_args);

    std::pair<ExpressionPtr, ExpressionPtr> root_args;
    root_args.first = make_shared<Constant>("8");
    root_args.second = right_subtree;

    auto root = make_shared<ArithmeticOperation>("*", root_args);

    expression_store->AddExpression(root);

    REQUIRE(expression_store->GetVariablesFromExpression(root) == VariableSet({}));
    REQUIRE(expression_store->GetConstantsFromExpression(root) == ConstantSet({"9", "4", "8"}));
  }

  SECTION("Multiple Expressions") {
    auto expression_store = new ExpressionStore();

    ExpressionPtr root1;
    root1 = make_shared<Constant>("69");

    ExpressionPtr root2;
    root2 = make_shared<Variable>("hardik");

    std::pair<ExpressionPtr, ExpressionPtr> arguments;
    arguments.first = make_shared<Variable>("c");
    arguments.second = make_shared<Variable>("x");

    auto root3 = make_shared<ArithmeticOperation>("-", arguments);

    arguments.first = root2;
    arguments.second = root3;
    auto root4 = make_shared<ArithmeticOperation>("/", arguments);

    arguments.first = root4;
    arguments.second = root3;
    auto root5 = make_shared<ArithmeticOperation>("-", arguments);

    expression_store->AddExpression(root1);
    expression_store->AddExpression(root2);
    expression_store->AddExpression(root3);
    expression_store->AddExpression(root4);
    expression_store->AddExpression(root5);

    REQUIRE(expression_store->GetVariablesFromExpression(root1) == VariableSet({}));
    REQUIRE(expression_store->GetConstantsFromExpression(root1) == ConstantSet({"69"}));

    REQUIRE(expression_store->GetVariablesFromExpression(root2) == VariableSet({"hardik"}));
    REQUIRE(expression_store->GetConstantsFromExpression(root2) == ConstantSet({}));

    REQUIRE(expression_store->GetVariablesFromExpression(root3) == VariableSet({"x", "c"}));
    REQUIRE(expression_store->GetConstantsFromExpression(root3) == ConstantSet({}));

    REQUIRE(expression_store->GetVariablesFromExpression(root4) == VariableSet({"hardik", "x", "c"}));
    REQUIRE(expression_store->GetConstantsFromExpression(root4) == ConstantSet({}));

    REQUIRE(expression_store->GetVariablesFromExpression(root5) == VariableSet({"hardik", "x", "c"}));
    REQUIRE(expression_store->GetConstantsFromExpression(root5) == ConstantSet({}));
  }
}
