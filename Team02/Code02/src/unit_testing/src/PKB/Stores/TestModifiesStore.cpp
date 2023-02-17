#include <catch.hpp>

#include "PKB/Stores/ModifiesStore.h"

TEST_CASE("Testcases for Modifies Store") {
  SECTION("Basic Statement Number to Variable Mapping") {
    auto modifies_store = new ModifiesStore();

    modifies_store->addStatementModifyingVariable("2", "a");
    modifies_store->addStatementModifyingVariable("2", "b");

    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("2") ==
    std::unordered_set<std::string>({ "a", "b" }));
  }

  SECTION("Empty Modifies store") {
    auto modifies_store = new ModifiesStore();
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("2", "a") == false);
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("anya", "a") == false);
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("2") == std::unordered_set<PkbTypes
    ::VARIABLE>({}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAProcedure("anya") == std::unordered_set<PkbTypes::VARIABLE>({}));
    REQUIRE(modifies_store->retrieveProcedureVariablePairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({}));
    REQUIRE(modifies_store->retrieveStatementVariablePairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({}));
  }

  SECTION("Single statement modifying a single variable") {
    auto modifies_store = new ModifiesStore();

    modifies_store->addStatementModifyingVariable("2", "a");
    modifies_store->addStatementModifyingVariable("3", "b");

    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("2") == std::unordered_set<std::string>({"a"}));
    REQUIRE_FALSE(modifies_store->retrieveAllVariablesModifiedByAStatement("3") == std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("3") == std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->retrieveStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("2", "a"), std::make_pair("3", "b") }));
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("2", "a") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("3", "c") == false);
  }

//  Should throw error
//  SECTION("Single statement modifying multiple variables") {
//
//
//  }

  SECTION("Multiple statements modifying a single variable") {
    auto modifies_store = new ModifiesStore();
    modifies_store->addStatementModifyingVariable("2", "a");
    modifies_store->addStatementModifyingVariable("3", "a");


    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("2") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("3") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("2", "a") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("3", "a") == true);
    REQUIRE_FALSE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("3", "b") == true);
    REQUIRE(modifies_store->retrieveStatementVariablePairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({ std::make_pair("2", "a"),
                                                              std::make_pair("3", "a")}));

  }


  // should adhere to the rule that a single statement cannot modify multiple variables
  SECTION("Multiple statements modifying a multiple variables") {
    auto modifies_store = new ModifiesStore();
    modifies_store->addStatementModifyingVariable("1", "a");
    modifies_store->addStatementModifyingVariable("2", "b");
    modifies_store->addStatementModifyingVariable("3", "c");
    modifies_store->addStatementModifyingVariable("4", "d");
    modifies_store->addStatementModifyingVariable("5", "a");
    modifies_store->addStatementModifyingVariable("6", "b");
    modifies_store->addStatementModifyingVariable("7", "c");
    modifies_store->addStatementModifyingVariable("8", "d");

    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("1", "a") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("2", "b") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("3", "c") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("4", "d") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("5", "a") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("6", "b") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("7", "c") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenStatementAndVariable("8", "d") == true);

    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("1") == std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("2") == std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("3") == std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("4") == std::unordered_set<std::string>({"d"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("5") == std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("6") == std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("7") == std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("8") == std::unordered_set<std::string>({"d"}));

    REQUIRE(modifies_store->retrieveStatementVariablePairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::VARIABLE>,PairHasherUtil::hash_pair>(
                { std::make_pair("1", "a"), std::make_pair("2", "b"),
                  std::make_pair("3", "c"), std::make_pair("4", "d"),
                  std::make_pair("5", "a"), std::make_pair("6", "b"),
                  std::make_pair("7", "c"), std::make_pair("8", "d")}));

  }


  SECTION("Single Procedure modifying a single variable") {
    auto modifies_store = new ModifiesStore();

    modifies_store->addProcedureModifyingVariable("anya", "a");
    modifies_store->addProcedureModifyingVariable("bumblebee", "b");

    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAProcedure("anya") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAProcedure("bumblebee") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE_FALSE(modifies_store->retrieveAllVariablesModifiedByAProcedure("bumblebee") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAProcedure("bumblebee") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->retrieveProcedureVariablePairs() ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE , PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
          std::make_pair("anya", "a"), std::make_pair("bumblebee", "b") }));
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("anya", "a") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("bumblebee", "c") == false);
  }

  SECTION("Single Procedure modifying multiple variables") {
    auto modifies_store = new ModifiesStore();

    modifies_store->addProcedureModifyingVariable("anya", "a");
    modifies_store->addProcedureModifyingVariable("anya", "b");
    modifies_store->addProcedureModifyingVariable("anya", "e");
    modifies_store->addProcedureModifyingVariable("bumblebee", "c");
    modifies_store->addProcedureModifyingVariable("bumblebee", "d");

    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAProcedure("anya")
    == std::unordered_set<std::string>({"a", "b", "e"}));
    REQUIRE_FALSE(modifies_store->retrieveAllVariablesModifiedByAStatement("bumblebee")
    == std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAProcedure("bumblebee")
    == std::unordered_set<std::string>({"c", "d"}));
    REQUIRE(modifies_store->retrieveProcedureVariablePairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE ,
            PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
              std::make_pair("anya", "a"), std::make_pair("anya", "b"),
              std::make_pair("anya", "e"),
              std::make_pair("bumblebee", "c"), std::make_pair("bumblebee", "d")}));
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("anya", "a") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("anya", "b") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("anya", "e") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("bumblebee", "c") == true);
    REQUIRE(modifies_store->hasModifiesRelationBetweenProcedureAndVariable("bumblebee", "d") == true);
  }

  SECTION("Multiple Procedures modifying single variable") {

  }

  SECTION("Multiple Procedures modifying multiple variables") {

  }




}

