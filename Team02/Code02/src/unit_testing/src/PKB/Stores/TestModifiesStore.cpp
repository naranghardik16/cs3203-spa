#include <catch.hpp>

#include "PKB/Stores/ModifiesStore.h"

TEST_CASE("Testcases for Modifies Store") {
  SECTION("Empty Modifies store") {
    auto modifies_store = new ModifiesStore();
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("2", "a") == false);
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("anya", "a") == false);

    REQUIRE(modifies_store->GetVariablesModifiedByStatement("2") ==
    std::unordered_set<PkbTypes::VARIABLE>({}));

    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("anya") ==
    std::unordered_set<PkbTypes::VARIABLE>({}));

    REQUIRE(modifies_store->GetProcedureVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({}));

    REQUIRE(modifies_store->GetStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({ }));
  }

  SECTION("Single statement modifying a single variable") {
    auto modifies_store = new ModifiesStore();

    modifies_store->AddStatementModifiesVariable("2", "a");
    modifies_store->AddStatementModifiesVariable("3", "b");

    REQUIRE(modifies_store->GetVariablesModifiedByStatement("2") == std::unordered_set<std::string>({"a" }));
    REQUIRE_FALSE(modifies_store->GetVariablesModifiedByStatement("3") ==
    std::unordered_set<std::string>({ "a" }));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("3") == std::unordered_set<std::string>({"b" }));

    REQUIRE(modifies_store->GetStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("2", "a"),
      std::make_pair("3", "b")
    }));

    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("2", "a") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("3", "c") == false);
  }

  SECTION("Multiple statements modifying a single variable") {
    auto modifies_store = new ModifiesStore();
    modifies_store->AddStatementModifiesVariable("2", "a");
    modifies_store->AddStatementModifiesVariable("3", "a");


    REQUIRE(modifies_store->GetVariablesModifiedByStatement("2") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("3") ==
        std::unordered_set<std::string>({"a"}));

    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("2", "a") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("3", "a") == true);
    REQUIRE_FALSE(modifies_store->HasModifiesStatementVariableRelation("3", "b") == true);

    REQUIRE(modifies_store->GetStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("2", "a"),
      std::make_pair("3", "a")
    }));
  }


  // should adhere to the rule that a single statement cannot modify multiple variables
  SECTION("Multiple statements modifying multiple variables") {
    auto modifies_store = new ModifiesStore();
    modifies_store->AddStatementModifiesVariable("1", "a");
    modifies_store->AddStatementModifiesVariable("2", "b");
    modifies_store->AddStatementModifiesVariable("3", "c");
    modifies_store->AddStatementModifiesVariable("4", "d");
    modifies_store->AddStatementModifiesVariable("5", "a");
    modifies_store->AddStatementModifiesVariable("6", "b");
    modifies_store->AddStatementModifiesVariable("7", "c");
    modifies_store->AddStatementModifiesVariable("8", "d");

    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("1", "a") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("2", "b") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("3", "c") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("4", "d") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("5", "a") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("6", "b") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("7", "c") == true);
    REQUIRE(modifies_store->HasModifiesStatementVariableRelation("8", "d") == true);

    REQUIRE(modifies_store->GetVariablesModifiedByStatement("1") == std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("2") == std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("3") == std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("4") == std::unordered_set<std::string>({"d"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("5") == std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("6") == std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("7") == std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->GetVariablesModifiedByStatement("8") == std::unordered_set<std::string>({"d"}));

    REQUIRE(modifies_store->GetStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("1", "a"),
      std::make_pair("2", "b"),
      std::make_pair("3", "c"),
      std::make_pair("4", "d"),
      std::make_pair("5", "a"),
      std::make_pair("6", "b"),
      std::make_pair("7", "c"),
      std::make_pair("8", "d")
    }));
  }


  SECTION("Single Procedure modifying a single variable") {
    auto modifies_store = new ModifiesStore();

    modifies_store->AddProcedureModifiesVariable("anya", "a");
    modifies_store->AddProcedureModifiesVariable("bumblebee", "b");

    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("anya") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("bumblebee") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE_FALSE(modifies_store->GetVariablesModifiedByProcedure("bumblebee") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("bumblebee") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->GetProcedureVariablePairs() ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE , PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
          std::make_pair("anya", "a"), std::make_pair("bumblebee", "b") }));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("anya", "a") == true);
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("bumblebee", "c") == false);
  }

  SECTION("Single Procedure modifying multiple variables") {
    auto modifies_store = new ModifiesStore();

    modifies_store->AddProcedureModifiesVariable("anya", "a");
    modifies_store->AddProcedureModifiesVariable("anya", "b");
    modifies_store->AddProcedureModifiesVariable("anya", "e");
    modifies_store->AddProcedureModifiesVariable("bumblebee", "c");
    modifies_store->AddProcedureModifiesVariable("bumblebee", "d");

    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("anya")
    == std::unordered_set<std::string>({"a", "b", "e"}));
    REQUIRE_FALSE(modifies_store->GetVariablesModifiedByProcedure("bumblebee")
    == std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("bumblebee")
    == std::unordered_set<std::string>({"c", "d"}));

    REQUIRE(modifies_store->GetProcedureVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("anya", "a"),
      std::make_pair("anya", "b"),
      std::make_pair("anya", "e"),
      std::make_pair("bumblebee", "c"),
      std::make_pair("bumblebee", "d")}));

    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("anya", "a") == true);
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("anya", "b") == true);
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("anya", "e") == true);
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("bumblebee", "c") == true);
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("bumblebee", "d") == true);
  }

  SECTION("Multiple Procedures modifying single variable") {
    auto modifies_store = new ModifiesStore();

    modifies_store->AddProcedureModifiesVariable("anya", "a");
    modifies_store->AddProcedureModifiesVariable("bumblebee", "a");
    modifies_store->AddProcedureModifiesVariable("megatron", "a");
    modifies_store->AddProcedureModifiesVariable("ironhide", "a");

    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("anya", "a"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("bumblebee", "a"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("megatron", "a"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("ironhide", "a"));

    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("anya") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("bumblebee") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("megatron") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("ironhide") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetProcedureVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("anya", "a"),
      std::make_pair("bumblebee", "a"),
      std::make_pair("megatron", "a"),
      std::make_pair("ironhide", "a")}));
  }

  SECTION("Multiple Procedures modifying multiple variables") {
    auto modifies_store = new ModifiesStore();

    modifies_store->AddProcedureModifiesVariable("Anya", "a");
    modifies_store->AddProcedureModifiesVariable("Bumblebee", "b");
    modifies_store->AddProcedureModifiesVariable("Megatron", "c");
    modifies_store->AddProcedureModifiesVariable("Ironhide", "d");
    modifies_store->AddProcedureModifiesVariable("Maya", "a");
    modifies_store->AddProcedureModifiesVariable("Sourabh", "b");
    modifies_store->AddProcedureModifiesVariable("Sumanth", "c");
    modifies_store->AddProcedureModifiesVariable("Hanhui", "d");

    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Anya", "a"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Bumblebee", "b"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Megatron", "c"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Ironhide", "d"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Maya", "a"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Sourabh", "b"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Sumanth", "c"));
    REQUIRE(modifies_store->HasModifiesProcedureVariableRelation("Hanhui", "d"));

    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Anya") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Bumblebee") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Megatron") ==
    std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Ironhide") ==
    std::unordered_set<std::string>({"d"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Maya") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Sourabh") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Sumanth") ==
    std::unordered_set<std::string>({"c"}));
    REQUIRE(modifies_store->GetVariablesModifiedByProcedure("Hanhui") ==
    std::unordered_set<std::string>({"d"}));

    REQUIRE(modifies_store->GetProcedureVariablePairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE ,
                                                                                        PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
              std::make_pair("Anya", "a"), std::make_pair("Bumblebee", "b"),
              std::make_pair("Megatron", "c"), std::make_pair("Ironhide", "d"),
              std::make_pair("Maya", "a"), std::make_pair("Sourabh", "b"),
              std::make_pair("Sumanth", "c"), std::make_pair("Hanhui", "d")}));
  }
}

