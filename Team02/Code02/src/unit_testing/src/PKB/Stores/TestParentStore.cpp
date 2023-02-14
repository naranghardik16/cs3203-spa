#include <catch.hpp>

#include "PKB/Stores/ParentStore.h"

TEST_CASE("Testcases for Parent Store") {
  SECTION("Basic Statement Number to Variable Mapping") {
    auto parent_store = new ParentStore();

    parent_store->addParentRelation("1", "2");
    parent_store->addParentRelation("1", "3");
//    parent_store->addParentRelation("2", "4");

    REQUIRE(parent_store->retrieveAllParents() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1" }));

  }
}

