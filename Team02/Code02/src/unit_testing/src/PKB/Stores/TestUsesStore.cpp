#include <catch.hpp>
#include "PKB/Stores/UsesStore.h"

TEST_CASE("Testcases for Uses Store") {
  SECTION("Empty uses store") {
    auto uses_store = new UsesStore();
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("2", "a") == false);
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("anya", "a") == false);
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<PkbTypes
                                                                                                ::VARIABLE>({}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("anya") ==
    std::unordered_set<PkbTypes::VARIABLE>({}));
    REQUIRE(uses_store->retrieveProcedureVariablePairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({}));
    REQUIRE(uses_store->retrieveStatementVariablePairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({}));
  }

  SECTION("Single statement using a single variable") {
    auto uses_store = new UsesStore();

    uses_store->addStatementUsingVariable("2", "a");
    uses_store->addStatementUsingVariable("3", "b");

    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<std::string>(
        {"a"}));
    REQUIRE_FALSE(uses_store->retrieveAllVariablesUsedByAStatement("3") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("3") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveStatementVariablePairs() ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
          std::make_pair("2", "a"), std::make_pair("3", "b") }));
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("2", "a") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("3", "c") == false);
  }

  SECTION("Multiple statements using a single variable") {
    auto uses_store = new UsesStore();
    uses_store->addStatementUsingVariable("2", "a");
    uses_store->addStatementUsingVariable("3", "a");


    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("3") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("2", "a") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("3", "a") == true);
    REQUIRE_FALSE(uses_store->hasUsesRelationBetweenStatementAndVariable("3", "b") == true);
    REQUIRE(uses_store->retrieveStatementVariablePairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({ std::make_pair("2", "a"),
                                                              std::make_pair("3", "a")}));
  }
//  SECTION("Basic Statement Number to Variable Mapping") {
//    UsesStore* uses_store = new UsesStore();
//
//    uses_store->addStatementUsingVariable("2", "a");
//    uses_store->addStatementUsingVariable("2", "b");
//
//    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<std::string>({"a", "b"}));
//  }
}