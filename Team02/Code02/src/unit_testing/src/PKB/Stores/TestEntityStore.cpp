#include <catch.hpp>

#include "PKB/Stores/EntityStore.h"

TEST_CASE("Testcases for Entity Store") {
  SECTION("Zero Variables") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
  }

  SECTION("Adding a Variable to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->addVariable("a");

    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ "a" }));
    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Adding Multiple Variables to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->addVariable("a");
    entity_store->addVariable("b");
    entity_store->addVariable("c");
    entity_store->addVariable("d");

    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ "a", "b", "c", "d" }));
    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Zero Procedures") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
  }

  SECTION("Adding a Procedure to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->addProcedure("main");

    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ "main" }));
    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Adding Multiple Procedures to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->addProcedure("main");
    entity_store->addProcedure("sub_routine");
    entity_store->addProcedure("compute_something");
    entity_store->addProcedure("set_state");

    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ "main", "sub_routine",
                                                                                       "compute_something",
                                                                                       "set_state" }));
    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Zero Constants") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }

  SECTION("Adding a Constant to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->addConstant("0");

    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ "0" }));
    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
  }

  SECTION("Adding Multiple Constants to the Store") {
    auto *entity_store = new EntityStore();
    entity_store->addConstant("0");
    entity_store->addConstant("1");
    entity_store->addConstant("2");
    entity_store->addConstant("3");

    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ "0", "1", "2", "3" }));
    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
  }

  SECTION("Initial Empty Stores") {
    auto *entity_store = new EntityStore();

    REQUIRE(entity_store->getVariables() == std::unordered_set<PkbTypes::VARIABLE>({ }));
    REQUIRE(entity_store->getProcedures() == std::unordered_set<PkbTypes::PROCEDURE>({ }));
    REQUIRE(entity_store->getConstants() == std::unordered_set<PkbTypes::CONSTANT>({ }));
  }
}

