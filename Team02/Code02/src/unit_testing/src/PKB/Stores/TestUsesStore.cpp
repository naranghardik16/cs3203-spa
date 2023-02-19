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

  SECTION("Single Procedure Using a single variable") {
    auto uses_store = new UsesStore();

    uses_store->addProcedureUsingVariable("anya", "a");
    uses_store->addProcedureUsingVariable("bumblebee", "b");

    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("anya") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("bumblebee") ==
        std::unordered_set<std::string>({"b"}));
    REQUIRE_FALSE(uses_store->retrieveAllVariablesUsedByAProcedure("bumblebee") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("bumblebee") ==
        std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveProcedureVariablePairs() ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE , PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
                                                                                                               std::make_pair("anya", "a"), std::make_pair("bumblebee", "b") }));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("anya", "a") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("bumblebee", "c") == false);
  }

  SECTION("Single Procedure Using multiple variables") {
    auto uses_store = new UsesStore();

    uses_store->addProcedureUsingVariable("anya", "a");
    uses_store->addProcedureUsingVariable("anya", "b");
    uses_store->addProcedureUsingVariable("anya", "e");
    uses_store->addProcedureUsingVariable("bumblebee", "c");
    uses_store->addProcedureUsingVariable("bumblebee", "d");

    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("anya")
                == std::unordered_set<std::string>({"a", "b", "e"}));
    REQUIRE_FALSE(uses_store->retrieveAllVariablesUsedByAProcedure("bumblebee")
                      == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("bumblebee")
                == std::unordered_set<std::string>({"c", "d"}));
    REQUIRE(uses_store->retrieveProcedureVariablePairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE ,
                                                                                             PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
                                                                                                                                                 std::make_pair("anya", "a"), std::make_pair("anya", "b"),
                                                                                                                                                 std::make_pair("anya", "e"),
                                                                                                                                                 std::make_pair("bumblebee", "c"), std::make_pair("bumblebee", "d")}));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("anya", "a") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("anya", "b") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("anya", "e") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("bumblebee", "c") == true);
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("bumblebee", "d") == true);
  }

  SECTION("Multiple Procedures Using single variable") {
    auto uses_store = new UsesStore();

    uses_store->addProcedureUsingVariable("anya", "a");
    uses_store->addProcedureUsingVariable("bumblebee", "a");
    uses_store->addProcedureUsingVariable("megatron", "a");
    uses_store->addProcedureUsingVariable("ironhide", "a");

    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("anya", "a"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("bumblebee", "a"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("megatron", "a"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("ironhide", "a"));

    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("anya") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("bumblebee") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("megatron") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("ironhide") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveProcedureVariablePairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE ,
                                                                                             PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
                                                                                                                                                 std::make_pair("anya", "a"), std::make_pair("bumblebee", "a"),
                                                                                                                                                 std::make_pair("megatron", "a"),
                                                                                                                                                 std::make_pair("ironhide", "a")}));
  }

  SECTION("Multiple Procedures Using multiple variables") {
    auto uses_store = new UsesStore();

    uses_store->addProcedureUsingVariable("Anya", "a");
    uses_store->addProcedureUsingVariable("Bumblebee", "b");
    uses_store->addProcedureUsingVariable("Megatron", "c");
    uses_store->addProcedureUsingVariable("Ironhide", "d");
    uses_store->addProcedureUsingVariable("Maya", "a");
    uses_store->addProcedureUsingVariable("Sourabh", "b");
    uses_store->addProcedureUsingVariable("Sumanth", "c");
    uses_store->addProcedureUsingVariable("Hanhui", "d");

    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Anya","a"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Bumblebee","b"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Megatron","c"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Ironhide","d"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Maya","a"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Sourabh","b"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Sumanth","c"));
    REQUIRE(uses_store->hasUsesRelationBetweenProcedureAndVariable("Hanhui","d"));

    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Anya") == std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Bumblebee") == std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Megatron") == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Ironhide") == std::unordered_set<std::string>({"d"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Maya") == std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Sourabh") == std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Sumanth") == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAProcedure("Hanhui") == std::unordered_set<std::string>({"d"}));

    REQUIRE(uses_store->retrieveProcedureVariablePairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE ,
                                                                                             PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
                                                                                                                                                 std::make_pair("Anya", "a"), std::make_pair("Bumblebee", "b"),
                                                                                                                                                 std::make_pair("Megatron", "c"), std::make_pair("Ironhide", "d"),
                                                                                                                                                 std::make_pair("Maya", "a"), std::make_pair("Sourabh", "b"),
                                                                                                                                                 std::make_pair("Sumanth", "c"), std::make_pair("Hanhui", "d")}));
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