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

    assignment_store->addAssignmentExpression("1", root);

    REQUIRE(assignment_store->retrieveAssignmentExpressionByStatementNumber("1") == root);
    REQUIRE(assignment_store->retrieveAllStatementNumbersWhichContainExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
  }

  SECTION("Singleton (One Variable)") {
    auto assignment_store = new AssignmentStore();
    std::shared_ptr<Expression> root;
    root = std::make_shared<Variable>("x");

    assignment_store->addAssignmentExpression("2", root);

    REQUIRE(assignment_store->retrieveAssignmentExpressionByStatementNumber("2") == root);
    REQUIRE(assignment_store->retrieveAllStatementNumbersWhichContainExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));
  }

  SECTION("Simple Expression") {
    auto assignment_store = new AssignmentStore();
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    assignment_store->addAssignmentExpression("2", root);

    REQUIRE(assignment_store->retrieveAssignmentExpressionByStatementNumber("2") == root);
    REQUIRE(assignment_store->retrieveAllStatementNumbersWhichContainExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));
  }

  SECTION("Multiple Assignment Statements with the same RHS") {
    auto assignment_store = new AssignmentStore();
    std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>> arguments;
    arguments.first = std::make_shared<Constant>("11");
    arguments.second = std::make_shared<Variable>("x");

    auto root = std::make_shared<ArithmeticOperation>("+", arguments);

    assignment_store->addAssignmentExpression("2", root);
    assignment_store->addAssignmentExpression("3", root);

    REQUIRE(assignment_store->retrieveAssignmentExpressionByStatementNumber("2") == root);
    REQUIRE(assignment_store->retrieveAssignmentExpressionByStatementNumber("3") == root);
    REQUIRE(assignment_store->retrieveAllStatementNumbersWhichContainExpression(root) ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2", "3" }));
  }
}

