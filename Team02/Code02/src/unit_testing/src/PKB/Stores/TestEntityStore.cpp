#include <catch.hpp>

#include "PKB/Stores/EntityStore.h"

TEST_CASE("Testcases for Entity Store") {
  SECTION("Zero Variables") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
  }

  SECTION("Adding a Variable to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddVariable("a");

    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({"a" }));
    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Adding Multiple Variables to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddVariable("a");
    entity_store->AddVariable("b");
    entity_store->AddVariable("c");
    entity_store->AddVariable("d");

    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({"a", "b", "c", "d" }));
    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Zero Procedures") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
  }

  SECTION("Adding a Procedure to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddProcedure("main");

    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({"main" }));
    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Adding Multiple Procedures to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddProcedure("main");
    entity_store->AddProcedure("sub_routine");
    entity_store->AddProcedure("compute_something");
    entity_store->AddProcedure("set_state");

    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({"main", "sub_routine",
                                                                                      "compute_something",
                                                                                      "set_state" }));
    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Zero Constants") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Adding a Constant to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddConstant("0");

    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({"0" }));
    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
  }

  SECTION("Adding Multiple Constants to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->AddConstant("0");
    entity_store->AddConstant("1");
    entity_store->AddConstant("2");
    entity_store->AddConstant("3");

    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({"0", "1", "2", "3" }));
    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
  }

  SECTION("Initial Empty Stores") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->GetVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->GetProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
    REQUIRE(entity_store->GetConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }
}

