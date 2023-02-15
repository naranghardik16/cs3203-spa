#include <catch.hpp>

#include "PKB/Stores/StatementStore.h"
#include "General/StatementTypeEnum.h"

TEST_CASE("Testcases for Statement Store") {
  SECTION("Empty Statement Store") {
    auto statement_store = new StatementStore();

    REQUIRE(statement_store->getAllStatementTypes() == std::unordered_set<StatementType>({ }));
    REQUIRE(statement_store->getStatementsFromType(IF) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(PRINT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(CALL) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(UNK) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(WHILE) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(STATEMENT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
  }

  SECTION("Single Statement Type to Single Statement Mapping") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(IF, "1");

    REQUIRE(statement_store->getAllStatementTypes() == std::unordered_set<StatementType>({ IF }));
    REQUIRE(statement_store->getStatementsFromType(IF) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
    REQUIRE(statement_store->getStatementsFromType(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(PRINT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(CALL) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(UNK) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(WHILE) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(STATEMENT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
  }

  SECTION("Single Statement Type to Multiple Statements Mapping") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(READ, "1");
    statement_store->addStatementForAType(READ, "2");
    statement_store->addStatementForAType(READ, "3");
    statement_store->addStatementForAType(READ, "4");

    REQUIRE(statement_store->getAllStatementTypes() == std::unordered_set<StatementType>({ READ }));
    REQUIRE(statement_store->getStatementsFromType(IF) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(READ) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "2", "3", "4" }));
    REQUIRE(statement_store->getStatementsFromType(PRINT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(CALL) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(UNK) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(WHILE) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
    REQUIRE(statement_store->getStatementsFromType(STATEMENT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
  }

//  Should throw error
//  SECTION("Multiple Statement Types to Single Statement Mapping") {
//    auto statement_store = new StatementStore();
//  }

  SECTION("Multiple Statement Types to Multiple Statements Mapping") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(READ, "1");
    statement_store->addStatementForAType(READ, "2");
    statement_store->addStatementForAType(READ, "3");
    statement_store->addStatementForAType(READ, "4");

    statement_store->addStatementForAType(IF, "5");
    statement_store->addStatementForAType(IF, "6");

    statement_store->addStatementForAType(PRINT, "7");

    statement_store->addStatementForAType(CALL, "8");
    statement_store->addStatementForAType(CALL, "9");
    statement_store->addStatementForAType(CALL, "10");

    statement_store->addStatementForAType(ASSIGN, "11");

    statement_store->addStatementForAType(WHILE, "12");
    statement_store->addStatementForAType(WHILE, "13");

    statement_store->addStatementForAType(UNK, "14");

    REQUIRE(statement_store->getAllStatementTypes() ==
    std::unordered_set<StatementType>({ IF, READ, ASSIGN, WHILE, CALL, UNK, PRINT }));
    REQUIRE(statement_store->getStatementsFromType(IF) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "5", "6" }));
    REQUIRE(statement_store->getStatementsFromType(READ) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "2", "3", "4" }));
    REQUIRE(statement_store->getStatementsFromType(PRINT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "7" }));
    REQUIRE(statement_store->getStatementsFromType(CALL) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "8", "9", "10" }));
    REQUIRE(statement_store->getStatementsFromType(UNK) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "14" }));
    REQUIRE(statement_store->getStatementsFromType(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "11" }));
    REQUIRE(statement_store->getStatementsFromType(WHILE) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "12", "13" }));
    REQUIRE(statement_store->getStatementsFromType(STATEMENT) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));
  }

  SECTION("Single Statement to Single Field Mapping") {
    auto statement_store = new StatementStore();
  }

  SECTION("Single Statement to Multiple Fields Mapping") {
    auto statement_store = new StatementStore();
  }

  SECTION("Multiple Statements to Single Field Mapping") {
    auto statement_store = new StatementStore();
  }

  SECTION("Multiple Statements to Multiple Fields Mapping") {
    auto statement_store = new StatementStore();
  }

  SECTION("Retrieve All Statements") {
    auto statement_store = new StatementStore();
  }

  SECTION("Retrieve All Statement Types") {
    auto statement_store = new StatementStore();
  }
}

