#include <catch.hpp>
#include "PKB/Stores/ParentStore.h"

TEST_CASE("Testcases for Parent Store") {
  SECTION("Basic Mapping") {
    auto* parent_store = new ParentStore();

    parent_store->addParentRelation("1", "2");
    parent_store->addParentRelation("1", "4");
    parent_store->addParentRelation("1", "5");
    parent_store->addParentRelation("2", "3");

    REQUIRE(parent_store->retrieveAllParentPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
        PairHasherUtil::hash_pair>({ std::make_pair("1", "2"), std::make_pair("1", "4"),
                                     std::make_pair("1", "5"), std::make_pair("2", "3") }));

    REQUIRE(parent_store->retrieveAllParentStarPairs() ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                           PairHasherUtil::hash_pair>({ std::make_pair("1", "2"), std::make_pair("1", "4"),
                                                        std::make_pair("1", "5"), std::make_pair("2", "3"),
                                                        std::make_pair("1", "3") }));

  }
}

