#include <catch.hpp>
#include "PKB/Stores/UsesStore.h"

TEST_CASE("Testcases for Uses Store") {
  SECTION("Basic Statement Number to Variable Mapping") {
    UsesStore* uses_store = new UsesStore();

    uses_store->addStatementUsingVariable("2", "a");
    uses_store->addStatementUsingVariable("2", "b");

    REQUIRE(uses_store->retrieveAllVariablesUsedByAStatement("2") == std::unordered_set<std::string>({"a", "b"}));
  }
}