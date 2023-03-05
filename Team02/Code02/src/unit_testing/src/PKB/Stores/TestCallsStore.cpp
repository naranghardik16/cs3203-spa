#include <catch.hpp>
#include "PKB/Stores/CallsStore.h"

TEST_CASE("Testcases for Calls Store") {
  SECTION("Empty Calls Store") {
    auto calls_store = new CallsStore();
    REQUIRE(calls_store->hasAnyCallsRelation() == false);
    REQUIRE(calls_store->hasAnyCallsStarRelation() == false);
    REQUIRE(calls_store->hasCallsRelation("caller procedure", "callee procedure")
    == false);
    REQUIRE(calls_store->hasCallsStarRelation("caller_procedure", "callee_procedure")
    == false);
    REQUIRE(calls_store->retrieveAllCallsPairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
        ({}));
    REQUIRE(calls_store->retrieveAllCallsStarPairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
        ({}));
    REQUIRE(calls_store->hasCallsStar("procedure_name") == false);
    REQUIRE(calls_store->hasCallsStarBy("procedure_name") == false);
    REQUIRE(calls_store->retrieveCallStatementsFromAProcedure("procedure_name") ==
    std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
  }
}