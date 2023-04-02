#include <catch.hpp>

#include "PKB/Stores/EntityStore.h"

TEST_CASE("Testcases for Entity Store") {
  typedef PkbTypes::VARIABLE Variable;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::CONSTANT Constant;
  typedef std::unordered_set<Variable> VariableSet;
  typedef std::unordered_set<Procedure> ProcedureSet;
  typedef std::unordered_set<Constant> ConstantSet;

  SECTION("Zero Variables") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetVariables() == VariableSet({}));
  }

  SECTION("Adding a Variable to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddVariable("a");

    REQUIRE(entity_store->GetVariables() == VariableSet({"a"}));
    REQUIRE(entity_store->GetProcedures() == ProcedureSet({}));
    REQUIRE(entity_store->GetConstants() == ConstantSet({}));
  }

  SECTION("Adding Multiple Variables to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddVariable("a");
    entity_store->AddVariable("b");
    entity_store->AddVariable("c");
    entity_store->AddVariable("d");

    REQUIRE(entity_store->GetVariables() == VariableSet({"a", "b", "c", "d"}));
    REQUIRE(entity_store->GetProcedures() == ProcedureSet({}));
    REQUIRE(entity_store->GetConstants() == ConstantSet({}));
  }

  SECTION("Zero Procedures") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetProcedures() == ProcedureSet({}));
  }

  SECTION("Adding a Procedure to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddProcedure("main");

    REQUIRE(entity_store->GetProcedures() == ProcedureSet({"main"}));
    REQUIRE(entity_store->GetVariables() == VariableSet({}));
    REQUIRE(entity_store->GetConstants() == ConstantSet({}));
  }

  SECTION("Adding Multiple Procedures to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddProcedure("main");
    entity_store->AddProcedure("sub_routine");
    entity_store->AddProcedure("compute_something");
    entity_store->AddProcedure("set_state");

    REQUIRE(entity_store->GetProcedures() == ProcedureSet({"main", "sub_routine", "compute_something", "set_state"}));
    REQUIRE(entity_store->GetVariables() == VariableSet({}));
    REQUIRE(entity_store->GetConstants() == ConstantSet({}));
  }

  SECTION("Zero Constants") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetConstants() == ConstantSet({}));
  }

  SECTION("Adding a Constant to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddConstant("0");

    REQUIRE(entity_store->GetConstants() == ConstantSet({"0"}));
    REQUIRE(entity_store->GetVariables() == VariableSet({}));
    REQUIRE(entity_store->GetProcedures() == ProcedureSet({}));
  }

  SECTION("Adding Multiple Constants to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddConstant("0");
    entity_store->AddConstant("1");
    entity_store->AddConstant("2");
    entity_store->AddConstant("3");

    REQUIRE(entity_store->GetConstants() == ConstantSet({"0", "1", "2", "3"}));
    REQUIRE(entity_store->GetVariables() == VariableSet({}));
    REQUIRE(entity_store->GetProcedures() == ProcedureSet({}));
  }

  SECTION("Initial Empty Stores") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetVariables() == VariableSet({}));
    REQUIRE(entity_store->GetProcedures() == ProcedureSet({}));
    REQUIRE(entity_store->GetConstants() == ConstantSet({}));
  }
}

