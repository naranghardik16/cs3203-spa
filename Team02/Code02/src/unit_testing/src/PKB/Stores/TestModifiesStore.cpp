#include <catch.hpp>

#include "PKB/Stores/ModifiesStore.h"

TEST_CASE("Testcases for Modifies Store") {
  SECTION("Basic Statement Number to Variable Mapping") {
    ModifiesStore* modifies_store = new ModifiesStore();

    modifies_store->addStatementModifyingVariable("2", "a");
    modifies_store->addStatementModifyingVariable("2", "b");

    REQUIRE(modifies_store->retrieveAllVariablesModifiedByAStatement("2") == std::unordered_set<std::string>({ "a", "b" }));
  }


}

