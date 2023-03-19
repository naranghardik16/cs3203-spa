#include <catch.hpp>
#include <memory>
#include <string>
#include <unordered_set>

#include "PKB/Stores/AssignmentStore.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Assignment Store") {
  SECTION("Singleton (One Constant)") {
    auto assignment_store = new AssignmentStore();
    std::shared_ptr<Expression> root;
    root = std::make_shared<Constant>("7");

    assignment_store->AddAssignmentExpression("1", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("1") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
  }

  SECTION("Singleton (One Variable)") {
    auto assignment_store = new AssignmentStore();
    std::shared_ptr<Expression> root;
    root = std::make_shared<Variable>("x");

    assignment_store->AddAssignmentExpression("2", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("2") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));
  }

  SECTION("Simple Expression") {
    auto assignment_store = new AssignmentStore();
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    assignment_store->AddAssignmentExpression("2", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("2") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));
  }

  SECTION("Multiple Assignment Statements with the same RHS") {
    auto assignment_store = new AssignmentStore();
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    assignment_store->AddAssignmentExpression("2", root);
    assignment_store->AddAssignmentExpression("3", root);

    REQUIRE(assignment_store->GetExpressionFromStatementNumber("2") == root);
    REQUIRE(assignment_store->GetExpressionFromStatementNumber("3") == root);
    REQUIRE(assignment_store->GetStatementNumbersFromExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2", "3" }));
  }
}

