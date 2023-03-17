#include <catch.hpp>
#include "PKB/Stores/CallsStore.h"

/**
 * @brief Unit tests for the CallsStore class.
 */
TEST_CASE("Testcases for Calls Store") {
  SECTION("Empty Calls Store") {
    auto calls_store = new CallsStore();

    REQUIRE(calls_store->hasAnyCallsRelation() == false);
    REQUIRE(
        calls_store->hasCallsRelation("caller procedure", "callee procedure")
            == false);

    REQUIRE(calls_store->retrieveAllCallsPairs()
                == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
                                                PkbTypes::PROCEDURE>,
                                      PairHasherUtil::hash_pair>({}));

    REQUIRE(calls_store->hasAnyCallsStarRelation() == false);
    REQUIRE(calls_store->hasCallsStarRelation("caller_procedure",
                                              "callee_procedure") == false);

    REQUIRE(calls_store->retrieveAllCallsStarPairs()
                == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
                                                PkbTypes::PROCEDURE>,
                                      PairHasherUtil::hash_pair>({}));

    REQUIRE(calls_store->hasCallsStar("procedure_name") == false);
    REQUIRE(calls_store->hasCallsStarBy("procedure_name") == false);

    REQUIRE(
        calls_store->retrieveCallStatementsFromAProcedure("procedure_name") ==
            std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));

    REQUIRE(calls_store->retrieveAllCallStatementToProcedurePairs() ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                     PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({}));
  }

  SECTION("Independent Calls without any Transitive Relationship") {
    auto calls_store = new CallsStore();

    // Add independent Calls Relation
    calls_store->addCallsRelation("caller_procedure1", "callee_procedure1");
    calls_store->addCallsRelation("caller_procedure2", "callee_procedure2");
    calls_store->addCallStatementToProcedureName("4", "procedure3");
    calls_store->addCallStatementToProcedureName("10", "procedure4");

    // Test independent Calls Relation with expected behaviour
    REQUIRE(calls_store->hasAnyCallsRelation() == true);
    REQUIRE(
        calls_store->hasCallsRelation("caller_procedure1", "callee_procedure1")
            == true);
    REQUIRE(
        calls_store->hasCallsRelation("caller_procedure2", "callee_procedure2")
            == true);

    REQUIRE_FALSE(
        calls_store->hasCallsRelation("caller_procedure1", "callee_procedure2")
            == true);
    REQUIRE_FALSE(
        calls_store->hasCallsRelation("caller_procedure2", "callee_procedure1")
            == true);

    REQUIRE(calls_store->retrieveAllCallsPairs() ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair(
                                                              "caller_procedure1",
                                                              "callee_procedure1"),
                                                          std::make_pair(
                                                              "caller_procedure2",
                                                              "callee_procedure2")
                                                      }));

    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("procedure3") ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"4"}));

    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("procedure4") ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"10"}));

    REQUIRE(calls_store->retrieveAllCallStatementToProcedurePairs()
                == std::unordered_set<std::pair<
                    PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE>,
                                      PairHasherUtil::hash_pair>({
                                                                     std::make_pair(
                                                                         "procedure3",
                                                                         "4"),
                                                                     std::make_pair(
                                                                         "procedure4",
                                                                         "10")
                                                                 }));
  }

  SECTION("Test CallsStar Relation") {
    auto calls_star_store = new CallsStore();

    calls_star_store->addCallsRelation("proc1", "proc2");
    calls_star_store->addCallsRelation("proc1", "proc3");
    calls_star_store->addCallsRelation("proc1", "proc4");
    calls_star_store->addCallsRelation("proc4", "proc5");
    calls_star_store->addCallsRelation("proc5", "proc6");
    calls_star_store->addCallsRelation("proc5", "proc7");
    calls_star_store->addCallsRelation("proc5", "proc8");
    calls_star_store->addCallsRelation("proc5", "proc9");
    calls_star_store->addCallsRelation("proc10", "proc11");
    calls_star_store->addCallsRelation("proc10", "proc12");
    calls_star_store->addCallsRelation("proc12", "proc13");

    calls_star_store->addCallsStarRelation();

    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc2") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc3") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc4") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc4", "proc5") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc5", "proc6") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc5", "proc7") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc5", "proc8") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc5", "proc9") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc10", "proc11") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc10", "proc12") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc12", "proc13") == true);

    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc5") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc6") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc7") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc8") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc1", "proc9") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc4", "proc6") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc4", "proc7") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc4", "proc8") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc4", "proc9") == true);
    REQUIRE(calls_star_store->hasCallsStarRelation("proc10", "proc13") == true);

    REQUIRE(calls_star_store->hasAnyCallsStarRelation() == true);
    REQUIRE_FALSE(calls_star_store->hasCallsStar("proc1") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc2") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc3") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc4") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc5") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc6") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc7") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc8") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc9") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc11") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc12") == true);
    REQUIRE(calls_star_store->hasCallsStar("proc13") == true);

    REQUIRE(calls_star_store->hasCallsStarBy("proc1") == true);
    REQUIRE(calls_star_store->hasCallsStarBy("proc4") == true);
    REQUIRE(calls_star_store->hasCallsStarBy("proc5") == true);
    REQUIRE(calls_star_store->hasCallsStarBy("proc10") == true);
    REQUIRE(calls_star_store->hasCallsStarBy("proc12") == true);
    REQUIRE_FALSE(calls_star_store->hasCallsStarBy("proc2") == true);

    REQUIRE(calls_star_store->retrieveAllCallsStarPairs()
                == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
                                                PkbTypes::PROCEDURE>,
                                      PairHasherUtil::hash_pair>({
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc2"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc3"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc4"),
                                                                     std::make_pair(
                                                                         "proc4",
                                                                         "proc5"),
                                                                     std::make_pair(
                                                                         "proc5",
                                                                         "proc6"),
                                                                     std::make_pair(
                                                                         "proc5",
                                                                         "proc7"),
                                                                     std::make_pair(
                                                                         "proc5",
                                                                         "proc8"),
                                                                     std::make_pair(
                                                                         "proc5",
                                                                         "proc9"),
                                                                     std::make_pair(
                                                                         "proc10",
                                                                         "proc11"),
                                                                     std::make_pair(
                                                                         "proc10",
                                                                         "proc12"),
                                                                     std::make_pair(
                                                                         "proc12",
                                                                         "proc13"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc5"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc6"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc7"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc8"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc9"),
                                                                     std::make_pair(
                                                                         "proc4",
                                                                         "proc6"),
                                                                     std::make_pair(
                                                                         "proc4",
                                                                         "proc7"),
                                                                     std::make_pair(
                                                                         "proc4",
                                                                         "proc8"),
                                                                     std::make_pair(
                                                                         "proc4",
                                                                         "proc9"),
                                                                     std::make_pair(
                                                                         "proc10",
                                                                         "proc13")
                                                                 }));
  }

  SECTION("Dependent Calls with Single Transitive Relationship") {
    auto calls_store = new CallsStore();

    calls_store->addCallsRelation("proc1", "proc2");
    calls_store->addCallsRelation("proc1", "proc3");
    calls_store->addCallsRelation("proc3", "proc4");

    REQUIRE(calls_store->hasCallsRelation("proc1", "proc2") == true);
    REQUIRE(calls_store->hasCallsRelation("proc1", "proc3") == true);
    REQUIRE(calls_store->hasCallsRelation("proc3", "proc4") == true);

    REQUIRE(calls_store->hasAnyCallsRelation() == true);

    REQUIRE(calls_store->retrieveAllCallsPairs()
                == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
                                                PkbTypes::PROCEDURE>,
                                      PairHasherUtil::hash_pair>({
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc2"),
                                                                     std::make_pair(
                                                                         "proc1",
                                                                         "proc3"),
                                                                     std::make_pair(
                                                                         "proc3",
                                                                         "proc4")
                                                                 }));
  }

  SECTION("Test OneToMany Calls Relation with statements and procedure") {
    auto calls_store = new CallsStore();

    calls_store->addCallStatementToProcedureName("4", "proc1");
    calls_store->addCallStatementToProcedureName("5", "proc1");
    calls_store->addCallStatementToProcedureName("6", "proc2");
    calls_store->addCallStatementToProcedureName("7", "proc2");
    calls_store->addCallStatementToProcedureName("8", "proc3");
    calls_store->addCallStatementToProcedureName("9", "proc3");

    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("proc1") ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"4", "5"}));

    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("proc2") ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"6", "7"}));

    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("proc3") ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"8", "9"}));

    REQUIRE(calls_store->retrieveAllCallStatementToProcedurePairs() ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                     PkbTypes::PROCEDURE>,
                           PairHasherUtil::hash_pair>({
                                                          std::make_pair("proc1",
                                                                         "4"),
                                                          std::make_pair("proc1",
                                                                         "5"),
                                                          std::make_pair("proc2",
                                                                         "6"),
                                                          std::make_pair("proc2",
                                                                         "7"),
                                                          std::make_pair("proc3",
                                                                         "8"),
                                                          std::make_pair("proc3",
                                                                         "9")
                                                      }));
  }
}
