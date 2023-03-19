#include <catch.hpp>
#include "PKB/Stores/UsesStore.h"

TEST_CASE("Testcases for Uses Store") {
  SECTION("Empty uses store") {
    auto uses_store = new UsesStore();
    REQUIRE(uses_store->HasUsesStatementVariableRelation("2", "a") == false);
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("anya", "a") == false);
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<PkbTypes::VARIABLE>({}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("anya") ==
    std::unordered_set<PkbTypes::VARIABLE>({}));
    REQUIRE(uses_store->GetProcedureVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({}));
    REQUIRE(uses_store->GetStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({}));
  }

  SECTION("Single statement using a single variable") {
    auto uses_store = new UsesStore();

    uses_store->AddStatementUsesVariable("2", "a");
    uses_store->AddStatementUsesVariable("3", "b");

    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<std::string>(
        {"a"}));
    REQUIRE_FALSE(uses_store->retrieveAllVariablesUsedByAStatement("3") ==
    std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("3") ==
    std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->GetStatementVariablePairs() ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
          std::make_pair("2", "a"), std::make_pair("3", "b") }));
    REQUIRE(uses_store->HasUsesStatementVariableRelation("2", "a") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("3", "c") == false);
  }

  SECTION("Multiple statements using a single variable") {
    auto uses_store = new UsesStore();
    uses_store->AddStatementUsesVariable("2", "a");
    uses_store->AddStatementUsesVariable("3", "a");


    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("3") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->HasUsesStatementVariableRelation("2", "a") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("3", "a") == true);
    REQUIRE_FALSE(uses_store->HasUsesStatementVariableRelation("3", "b") == true);
    REQUIRE(uses_store->GetStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("2", "a"),
      std::make_pair("3", "a")
    }));
  }

  SECTION("Multiple statements Using multiple variables") {
    auto uses_store = new UsesStore();
    uses_store->AddStatementUsesVariable("1", "a");
    uses_store->AddStatementUsesVariable("2", "b");
    uses_store->AddStatementUsesVariable("3", "c");
    uses_store->AddStatementUsesVariable("4", "d");
    uses_store->AddStatementUsesVariable("5", "a");
    uses_store->AddStatementUsesVariable("6", "b");
    uses_store->AddStatementUsesVariable("7", "c");
    uses_store->AddStatementUsesVariable("8", "d");

    REQUIRE(uses_store->HasUsesStatementVariableRelation("1", "a") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("2", "b") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("3", "c") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("4", "d") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("5", "a") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("6", "b") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("7", "c") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("8", "d") == true);

    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("1") == std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("3") == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("4") == std::unordered_set<std::string>({"d"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("5") == std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("6") == std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("7") == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("8") == std::unordered_set<std::string>({"d"}));

    REQUIRE(uses_store->GetStatementVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("1", "a"), std::make_pair("2", "b"),
      std::make_pair("3", "c"), std::make_pair("4", "d"),
      std::make_pair("5", "a"), std::make_pair("6", "b"),
      std::make_pair("7", "c"), std::make_pair("8", "d")
    }));
  }

  SECTION("Single Procedure Using a single variable") {
    auto uses_store = new UsesStore();

    uses_store->AddProcedureUsesVariable("anya", "a");
    uses_store->AddProcedureUsesVariable("bumblebee", "b");

    REQUIRE(uses_store->GetVariablesUsedByProcedure("anya") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee") ==
        std::unordered_set<std::string>({"b"}));
    REQUIRE_FALSE(uses_store->GetVariablesUsedByProcedure("bumblebee") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee") ==
        std::unordered_set<std::string>({"b"}));
    REQUIRE(uses_store->GetProcedureVariablePairs() ==
        std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>,
            PairHasherUtil::hash_pair>({ std::make_pair("anya", "a"), std::make_pair("bumblebee", "b") }));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("anya", "a") == true);
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("bumblebee", "c") == false);
  }

  SECTION("Single Procedure Using multiple variables") {
    auto uses_store = new UsesStore();

    uses_store->AddProcedureUsesVariable("anya", "a");
    uses_store->AddProcedureUsesVariable("anya", "b");
    uses_store->AddProcedureUsesVariable("anya", "e");
    uses_store->AddProcedureUsesVariable("bumblebee", "c");
    uses_store->AddProcedureUsesVariable("bumblebee", "d");

    REQUIRE(uses_store->GetVariablesUsedByProcedure("anya")
                == std::unordered_set<std::string>({"a", "b", "e"}));
    REQUIRE_FALSE(uses_store->GetVariablesUsedByProcedure("bumblebee")
                      == std::unordered_set<std::string>({"c"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee")
                == std::unordered_set<std::string>({"c", "d"}));

    REQUIRE(uses_store->GetProcedureVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("anya", "a"),
      std::make_pair("anya", "b"),
      std::make_pair("anya", "e"),
      std::make_pair("bumblebee", "c"),
      std::make_pair("bumblebee", "d")}));

    REQUIRE(uses_store->HasUsesProcedureVariableRelation("anya", "a") == true);
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("anya", "b") == true);
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("anya", "e") == true);
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("bumblebee", "c") == true);
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("bumblebee", "d") == true);
  }

  SECTION("Multiple Procedures Using single variable") {
    auto uses_store = new UsesStore();

    uses_store->AddProcedureUsesVariable("anya", "a");
    uses_store->AddProcedureUsesVariable("bumblebee", "a");
    uses_store->AddProcedureUsesVariable("megatron", "a");
    uses_store->AddProcedureUsesVariable("ironhide", "a");

    REQUIRE(uses_store->HasUsesProcedureVariableRelation("anya", "a"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("bumblebee", "a"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("megatron", "a"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("ironhide", "a"));

    REQUIRE(uses_store->GetVariablesUsedByProcedure("anya") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("megatron") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("ironhide") ==
        std::unordered_set<std::string>({"a"}));
    REQUIRE(uses_store->GetProcedureVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("anya", "a"),
      std::make_pair("bumblebee", "a"),
      std::make_pair("megatron", "a"),
      std::make_pair("ironhide", "a")}));
  }

  SECTION("Multiple Procedures Using multiple variables") {
    auto uses_store = new UsesStore();

    uses_store->AddProcedureUsesVariable("Anya", "a");
    uses_store->AddProcedureUsesVariable("Bumblebee", "b");
    uses_store->AddProcedureUsesVariable("Megatron", "c");
    uses_store->AddProcedureUsesVariable("Ironhide", "d");
    uses_store->AddProcedureUsesVariable("Maya", "a");
    uses_store->AddProcedureUsesVariable("Sourabh", "b");
    uses_store->AddProcedureUsesVariable("Sumanth", "c");
    uses_store->AddProcedureUsesVariable("Hanhui", "d");

    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Anya", "a"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Bumblebee", "b"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Megatron", "c"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Ironhide", "d"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Maya", "a"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Sourabh", "b"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Sumanth", "c"));
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("Hanhui", "d"));

    REQUIRE(uses_store->GetVariablesUsedByProcedure("Anya") == std::unordered_set<std::string>({"a" }));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Bumblebee") == std::unordered_set<std::string>({"b" }));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Megatron") == std::unordered_set<std::string>({"c" }));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Ironhide") == std::unordered_set<std::string>({"d" }));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Maya") == std::unordered_set<std::string>({"a" }));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Sourabh") == std::unordered_set<std::string>({"b" }));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Sumanth") == std::unordered_set<std::string>({"c" }));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Hanhui") == std::unordered_set<std::string>({"d" }));

    REQUIRE(uses_store->GetProcedureVariablePairs() ==
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>({
      std::make_pair("Anya", "a"), std::make_pair("Bumblebee", "b"),
      std::make_pair("Megatron", "c"), std::make_pair("Ironhide", "d"),
      std::make_pair("Maya", "a"), std::make_pair("Sourabh", "b"),
      std::make_pair("Sumanth", "c"), std::make_pair("Hanhui", "d")}));
  }
}
