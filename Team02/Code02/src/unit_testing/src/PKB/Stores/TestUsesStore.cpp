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

  SECTION("Multiple statements Using multiple variables") {
    auto uses_store = new UsesStore();
    uses_store->addStatementUsingVariable("1", "a");
    uses_store->addStatementUsingVariable("2", "b");
    uses_store->addStatementUsingVariable("3", "c");
    uses_store->addStatementUsingVariable("4", "d");
    uses_store->addStatementUsingVariable("5", "a");
    uses_store->addStatementUsingVariable("6", "b");
    uses_store->addStatementUsingVariable("7", "c");
    uses_store->addStatementUsingVariable("8", "d");

    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("1", "a") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("2", "b") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("3", "c") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("4", "d") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("5", "a") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("6", "b") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("7", "c") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenStatementAndVariable("8", "d") == true);

    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("1") == std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("3") == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("4") == std::unordered_set<std::string>({"d"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("5") == std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("6") == std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("7") == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("8") == std::unordered_set<std::string>({"d"}));

    REQUIRE(uses_store->retrieveStatementVariablePairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                                             PkbTypes::VARIABLE>,PairHasherUtil::hash_pair>(
        { std::make_pair("1", "a"), std::make_pair("2", "b"),
          std::make_pair("3", "c"), std::make_pair("4", "d"),
          std::make_pair("5", "a"), std::make_pair("6", "b"),
          std::make_pair("7", "c"), std::make_pair("8", "d")}));

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