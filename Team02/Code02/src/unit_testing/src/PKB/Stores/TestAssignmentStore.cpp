#include <catch.hpp>

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "core/model/Expression.h"
#include "PKB/Stores/AssignmentStore.h"
#include "PKB/Types/PkbTypes.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Assignment Store") {
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;
  typedef std::shared_ptr<Expression> ExpressionPtr;
  typedef std::pair<ExpressionPtr, ExpressionPtr> ExpressionPtrPair;

  SECTION("Singleton (One Constant)") {
    auto assignment_store = new AssignmentStore();
    ExpressionPtr root;
    root = std::make_shared<Constant>("7");

    assignment_store->AddAssignmentExpression("1", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("1") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) == StatementNumberSet({"1"}));
  }

  SECTION("Singleton (One Variable)") {
    auto assignment_store = new AssignmentStore();
    ExpressionPtr root;
    root = std::make_shared<Variable>("x");

    assignment_store->AddAssignmentExpression("2", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("2") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) == StatementNumberSet({"2"}));
  }

  SECTION("Simple Expression") {
    auto assignment_store = new AssignmentStore();
    ExpressionPtrPair arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    assignment_store->AddAssignmentExpression("2", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("2") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) == StatementNumberSet({"2"}));
  }

  SECTION("Multiple Assignment Statements with the same RHS") {
    auto assignment_store = new AssignmentStore();
    ExpressionPtrPair arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    assignment_store->AddAssignmentExpression("2", root);
    assignment_store->AddAssignmentExpression("3", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("2") == root);
    REQUIRE(assignment_store->GetExpressionFromStatementNumber("3") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) == StatementNumberSet({"2", "3"}));
  }
}

