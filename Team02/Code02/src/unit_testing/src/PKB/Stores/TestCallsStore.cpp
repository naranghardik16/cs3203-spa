#include <catch.hpp>
#include "PKB/Stores/CallsStore.h"

/**
 * @brief Unit tests for the CallsStore class.
 */
TEST_CASE("Testcases for Calls Store") {
  SECTION("Empty Calls Store") {
    auto calls_store = new CallsStore();

    // Test that the calls store is empty.

    // Calls Relation
    REQUIRE(calls_store->hasAnyCallsRelation() == false);
    REQUIRE(calls_store->hasCallsRelation("caller procedure", "callee procedure")
                == false);
    REQUIRE(calls_store->retrieveAllCallsPairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({}));

    // Calls* Relation
    REQUIRE(calls_store->hasAnyCallsStarRelation() == false);
    REQUIRE(calls_store->hasCallsStarRelation("caller_procedure", "callee_procedure")
    == false);
    REQUIRE(calls_store->retrieveAllCallsStarPairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({}));
    REQUIRE(calls_store->hasCallsStar("procedure_name") == false);
    REQUIRE(calls_store->hasCallsStarBy("procedure_name") == false);

    // Applicable to both Calls and Calls* Relation
    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("procedure_name") ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(calls_store->retrieveAllCallStatementToProcedurePairs() == std::unordered_set<std::pair<
        PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({}));
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
    REQUIRE(calls_store->hasCallsRelation("caller_procedure1", "callee_procedure1")
    == true);
    REQUIRE(calls_store->hasCallsRelation("caller_procedure2", "callee_procedure2")
    == true);
    REQUIRE_FALSE(calls_store->hasCallsRelation("caller_procedure1", "callee_procedure2")
    == true);
    REQUIRE_FALSE(calls_store->hasCallsRelation("caller_procedure2", "callee_procedure1")
    == true);
    REQUIRE(calls_store->retrieveAllCallsPairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::PROCEDURE>,PairHasherUtil::hash_pair>
            ({std::make_pair("caller_procedure1","callee_procedure1"),
              std::make_pair("caller_procedure2","callee_procedure2")}));
    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("procedure3") ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"4"}));
    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("procedure4") ==
        std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"10"}));
    REQUIRE(calls_store->retrieveAllCallStatementToProcedurePairs() == std::unordered_set<std::pair<
        PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>(
            {std::make_pair("procedure3", "4"),
             std::make_pair("procedure4", "10")}));
  }
//  std::make_pair("caller_procedure1", "callee_procedure1"),
//      std::make_pair("caller_procedure2", "callee_procedure2"),

}