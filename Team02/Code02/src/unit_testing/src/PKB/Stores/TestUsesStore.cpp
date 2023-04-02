#include <catch.hpp>
#include "PKB/Stores/UsesStore.h"

TEST_CASE("Testcases for Uses Store") {
  typedef PkbTypes::VARIABLE Variable;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef std::unordered_set<Variable> VariableSet;
  typedef std::unordered_set<Procedure> ProcedureSet;
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef PairHasherUtil::hash_pair Hasher;
  typedef std::unordered_set<std::pair<Procedure, Variable>, Hasher> ProcedureVariablePairSet;
  typedef std::unordered_set<std::pair<StatementNumber, Variable>, Hasher> StatementNumberVariablePairSet;

  SECTION("Empty uses store") {
    auto uses_store = new UsesStore();

    REQUIRE(uses_store->HasUsesStatementVariableRelation("2", "a") == false);
    REQUIRE(uses_store->HasUsesProcedureVariableRelation("anya", "a") == false);

    REQUIRE(uses_store->GetVariablesUsedByStatement("2") == VariableSet({}));

    REQUIRE(uses_store->GetVariablesUsedByProcedure("anya") == VariableSet({}));

    REQUIRE(uses_store->GetProcedureVariablePairs() == ProcedureVariablePairSet({}));

    REQUIRE(uses_store->GetStatementVariablePairs() == StatementNumberVariablePairSet({}));
  }

  SECTION("Single statement using a single variable") {
    auto uses_store = new UsesStore();

    uses_store->AddStatementUsesVariable("2", "a");
    uses_store->AddStatementUsesVariable("3", "b");

    REQUIRE(uses_store->GetVariablesUsedByStatement("2") == VariableSet({"a"}));

    REQUIRE_FALSE(uses_store->GetVariablesUsedByStatement("3") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("3") == VariableSet({"b"}));

    REQUIRE(uses_store->GetStatementVariablePairs() == StatementNumberVariablePairSet({
                                                                                          std::make_pair("2", "a"),
                                                                                          std::make_pair("3", "b")
                                                                                      }));

    REQUIRE(uses_store->HasUsesStatementVariableRelation("2", "a") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("3", "c") == false);
  }

  SECTION("Multiple statements using a single variable") {
    auto uses_store = new UsesStore();

    uses_store->AddStatementUsesVariable("2", "a");
    uses_store->AddStatementUsesVariable("3", "a");

    REQUIRE(uses_store->GetVariablesUsedByStatement("2") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("3") == VariableSet({"a"}));

    REQUIRE(uses_store->HasUsesStatementVariableRelation("2", "a") == true);
    REQUIRE(uses_store->HasUsesStatementVariableRelation("3", "a") == true);

    REQUIRE_FALSE(uses_store->HasUsesStatementVariableRelation("3", "b") == true);

    REQUIRE(uses_store->GetStatementVariablePairs() == StatementNumberVariablePairSet({
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

    REQUIRE(uses_store->GetVariablesUsedByStatement("1") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("2") == VariableSet({"b"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("3") == VariableSet({"c"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("4") == VariableSet({"d"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("5") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("6") == VariableSet({"b"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("7") == VariableSet({"c"}));
    REQUIRE(uses_store->GetVariablesUsedByStatement("8") == VariableSet({"d"}));

    REQUIRE(uses_store->GetStatementVariablePairs() == StatementNumberVariablePairSet({
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

  SECTION("Single Procedure Using a single variable") {
    auto uses_store = new UsesStore();

    uses_store->AddProcedureUsesVariable("anya", "a");
    uses_store->AddProcedureUsesVariable("bumblebee", "b");

    REQUIRE(uses_store->GetVariablesUsedByProcedure("anya") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee") == VariableSet({"b"}));
    REQUIRE_FALSE(uses_store->GetVariablesUsedByProcedure("bumblebee") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee") == VariableSet({"b"}));

    REQUIRE(uses_store->GetProcedureVariablePairs() == ProcedureVariablePairSet({
                                                                                    std::make_pair("anya", "a"),
                                                                                    std::make_pair("bumblebee", "b")
                                                                                }));

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

    REQUIRE(uses_store->GetVariablesUsedByProcedure("anya") == VariableSet({"a", "b", "e"}));
    REQUIRE_FALSE(uses_store->GetVariablesUsedByProcedure("bumblebee") == VariableSet({"c"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee") == VariableSet({"c", "d"}));

    REQUIRE(uses_store->GetProcedureVariablePairs() == ProcedureVariablePairSet({
                                                                                    std::make_pair("anya", "a"),
                                                                                    std::make_pair("anya", "b"),
                                                                                    std::make_pair("anya", "e"),
                                                                                    std::make_pair("bumblebee", "c"),
                                                                                    std::make_pair("bumblebee", "d")
                                                                                }));

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
        VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("bumblebee") ==
        VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("megatron") ==
        VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("ironhide") ==
        VariableSet({"a"}));
    REQUIRE(uses_store->GetProcedureVariablePairs() ==
        ProcedureVariablePairSet({
                                     std::make_pair("anya", "a"),
                                     std::make_pair("bumblebee", "a"),
                                     std::make_pair("megatron", "a"),
                                     std::make_pair("ironhide", "a")
                                 }));
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

    REQUIRE(uses_store->GetVariablesUsedByProcedure("Anya") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Bumblebee") == VariableSet({"b"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Megatron") == VariableSet({"c"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Ironhide") == VariableSet({"d"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Maya") == VariableSet({"a"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Sourabh") == VariableSet({"b"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Sumanth") == VariableSet({"c"}));
    REQUIRE(uses_store->GetVariablesUsedByProcedure("Hanhui") == VariableSet({"d"}));

    REQUIRE(uses_store->GetProcedureVariablePairs() ==
        ProcedureVariablePairSet({
                                     std::make_pair("Anya", "a"),
                                     std::make_pair("Bumblebee", "b"),
                                     std::make_pair("Megatron", "c"),
                                     std::make_pair("Ironhide", "d"),
                                     std::make_pair("Maya", "a"),
                                     std::make_pair("Sourabh", "b"),
                                     std::make_pair("Sumanth", "c"),
                                     std::make_pair("Hanhui", "d")
                                 }));
  }
}
