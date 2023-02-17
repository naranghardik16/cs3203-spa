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


  }


  SECTION("Single Procedure modifying a single variable") {


  }

  SECTION("Single Procedure modifying multiple variables") {


  }

  SECTION("Multiple Procedures modifying single variable") {

  }

  SECTION("Multiple Procedures modifying multiple variables") {

  }




}

