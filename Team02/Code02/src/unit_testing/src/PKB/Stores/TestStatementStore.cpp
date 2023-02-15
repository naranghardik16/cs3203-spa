#include <catch.hpp>

#include "General/StatementTypeEnum.h"
#include "PKB/Stores/StatementStore.h"

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

    REQUIRE(statement_store->getStatementTypeByNumber("1") == IF );
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
    REQUIRE(statement_store->getStatementsFromType(STATEMENT) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("2") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("3") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("4") == READ );
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
    std::unordered_set<StatementType>({ StatementType::IF, READ, ASSIGN, WHILE, CALL, UNK, PRINT }));
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
    REQUIRE(statement_store->getStatementsFromType(STATEMENT) ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("2") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("3") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("4") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("5") == IF );
    REQUIRE(statement_store->getStatementTypeByNumber("6") == IF );
    REQUIRE(statement_store->getStatementTypeByNumber("7") == PRINT );
    REQUIRE(statement_store->getStatementTypeByNumber("8") == CALL );
    REQUIRE(statement_store->getStatementTypeByNumber("9") == CALL );
    REQUIRE(statement_store->getStatementTypeByNumber("10") == CALL );
    REQUIRE(statement_store->getStatementTypeByNumber("11") == ASSIGN );
    REQUIRE(statement_store->getStatementTypeByNumber("12") == WHILE );
    REQUIRE(statement_store->getStatementTypeByNumber("13") == WHILE );
    REQUIRE(statement_store->getStatementTypeByNumber("14") == UNK );
  }

  SECTION("Single Statement to Single Field Mapping") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(IF, "1");
    statement_store->addStatementAndField("1", "a");

    REQUIRE(statement_store->getFieldsForStatement("1") == std::unordered_set<PkbTypes::FIELD>({ "a" }));
    REQUIRE(statement_store->getAllStatements() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
    REQUIRE(statement_store->getStatementsFromType(IF) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == IF );
  }

  SECTION("Single Statement to Multiple Fields Mapping") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(ASSIGN, "1");
    statement_store->addStatementAndField("1", "a");
    statement_store->addStatementAndField("1", "4");
    statement_store->addStatementAndField("1", "main");

    REQUIRE(statement_store->getFieldsForStatement("1") == std::unordered_set<PkbTypes::FIELD>({ "a", "4", "main" }));
    REQUIRE(statement_store->getAllStatements() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
    REQUIRE(statement_store->getStatementsFromType(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == ASSIGN );
  }

  SECTION("Multiple Statements to Single Field Mapping") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(ASSIGN, "1");
    statement_store->addStatementForAType(READ, "2");
    statement_store->addStatementForAType(CALL, "3");

    statement_store->addStatementAndField("1", "a");
    statement_store->addStatementAndField("2", "a");
    statement_store->addStatementAndField("3", "a");

    REQUIRE(statement_store->getFieldsForStatement("1") == std::unordered_set<PkbTypes::FIELD>({ "a" }));
    REQUIRE(statement_store->getFieldsForStatement("2") == std::unordered_set<PkbTypes::FIELD>({ "a" }));
    REQUIRE(statement_store->getFieldsForStatement("3") == std::unordered_set<PkbTypes::FIELD>({ "a" }));

    REQUIRE(statement_store->getAllStatements() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "2", "3" }));

    REQUIRE(statement_store->getStatementsFromType(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));
    REQUIRE(statement_store->getStatementsFromType(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));
    REQUIRE(statement_store->getStatementsFromType(CALL) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "3" }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == ASSIGN );
    REQUIRE(statement_store->getStatementTypeByNumber("2") == READ );
    REQUIRE(statement_store->getStatementTypeByNumber("3") == CALL );
  }

  SECTION("Multiple Statements to Multiple Fields Mapping") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(ASSIGN, "1");
    statement_store->addStatementForAType(READ, "2");
    statement_store->addStatementForAType(CALL, "3");
    statement_store->addStatementForAType(ASSIGN, "4");
    statement_store->addStatementForAType(IF, "5");
    statement_store->addStatementForAType(READ, "6");
    statement_store->addStatementForAType(IF, "8");

    statement_store->addStatementAndField("1", "c");
    statement_store->addStatementAndField("2", "a");
    statement_store->addStatementAndField("4", "main");
    statement_store->addStatementAndField("3", "4");
    statement_store->addStatementAndField("6", "a");
    statement_store->addStatementAndField("8", "b");
    statement_store->addStatementAndField("5", "3");
    statement_store->addStatementAndField("2", "5");
    statement_store->addStatementAndField("4", "a");
    statement_store->addStatementAndField("3", "d");
    statement_store->addStatementAndField("1", "main");
    statement_store->addStatementAndField("4", "c");
    statement_store->addStatementAndField("1", "something");
    statement_store->addStatementAndField("8", "main");
    statement_store->addStatementAndField("6", "d");

    REQUIRE(statement_store->getFieldsForStatement("1") == std::unordered_set<PkbTypes::FIELD>({ "c", "main", "something" }));
    REQUIRE(statement_store->getFieldsForStatement("2") == std::unordered_set<PkbTypes::FIELD>({ "a", "5" }));
    REQUIRE(statement_store->getFieldsForStatement("3") == std::unordered_set<PkbTypes::FIELD>({ "4", "d" }));
    REQUIRE(statement_store->getFieldsForStatement("4") == std::unordered_set<PkbTypes::FIELD>({ "main", "a", "c" }));
    REQUIRE(statement_store->getFieldsForStatement("5") == std::unordered_set<PkbTypes::FIELD>({ "3" }));
    REQUIRE(statement_store->getFieldsForStatement("6") == std::unordered_set<PkbTypes::FIELD>({ "d", "a" }));
    REQUIRE(statement_store->getFieldsForStatement("8") == std::unordered_set<PkbTypes::FIELD>({ "b", "main" }));

    REQUIRE(statement_store->getAllStatements() ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "2", "3", "4", "5", "6", "8" }));

    REQUIRE(statement_store->getStatementsFromType(ASSIGN) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "4" }));
    REQUIRE(statement_store->getStatementsFromType(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2", "6" }));
    REQUIRE(statement_store->getStatementsFromType(CALL) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "3" }));
    REQUIRE(statement_store->getStatementsFromType(IF) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "5", "8" }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == ASSIGN);
    REQUIRE(statement_store->getStatementTypeByNumber("2") == READ);
    REQUIRE(statement_store->getStatementTypeByNumber("3") == CALL);
    REQUIRE(statement_store->getStatementTypeByNumber("4") == ASSIGN);
    REQUIRE(statement_store->getStatementTypeByNumber("5") == IF);
    REQUIRE(statement_store->getStatementTypeByNumber("6") == READ);
    REQUIRE(statement_store->getStatementTypeByNumber("8") == IF);
  }

  SECTION("Retrieve All Statements") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(ASSIGN, "1");
    statement_store->addStatementForAType(READ, "2");
    statement_store->addStatementForAType(CALL, "3");
    statement_store->addStatementForAType(ASSIGN, "4");
    statement_store->addStatementForAType(IF, "5");
    statement_store->addStatementForAType(READ, "6");
    statement_store->addStatementForAType(IF, "8");

    REQUIRE(statement_store->getAllStatements() ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "2", "3", "4", "5", "6", "8" }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == ASSIGN);
    REQUIRE(statement_store->getStatementTypeByNumber("2") == READ);
    REQUIRE(statement_store->getStatementTypeByNumber("3") == CALL);
    REQUIRE(statement_store->getStatementTypeByNumber("4") == ASSIGN);
    REQUIRE(statement_store->getStatementTypeByNumber("5") == IF);
    REQUIRE(statement_store->getStatementTypeByNumber("6") == READ);
    REQUIRE(statement_store->getStatementTypeByNumber("8") == IF);
  }

  SECTION("Retrieve All Statement Types") {
    auto statement_store = new StatementStore();

    statement_store->addStatementForAType(ASSIGN, "1");
    statement_store->addStatementForAType(READ, "2");
    statement_store->addStatementForAType(CALL, "3");
    statement_store->addStatementForAType(ASSIGN, "4");
    statement_store->addStatementForAType(IF, "5");
    statement_store->addStatementForAType(READ, "6");
    statement_store->addStatementForAType(IF, "8");

    REQUIRE(statement_store->getAllStatementTypes() ==
    std::unordered_set<StatementType>({ ASSIGN, READ, CALL, IF }));

    REQUIRE(statement_store->getStatementTypeByNumber("1") == ASSIGN);
    REQUIRE(statement_store->getStatementTypeByNumber("2") == READ);
    REQUIRE(statement_store->getStatementTypeByNumber("3") == CALL);
    REQUIRE(statement_store->getStatementTypeByNumber("4") == ASSIGN);
    REQUIRE(statement_store->getStatementTypeByNumber("5") == IF);
    REQUIRE(statement_store->getStatementTypeByNumber("6") == READ);
    REQUIRE(statement_store->getStatementTypeByNumber("8") == IF);
  }
}

