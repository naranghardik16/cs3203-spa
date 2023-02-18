#include <catch.hpp>
#include "PKB/Stores/ParentStore.h"

TEST_CASE("Testcases for Parent Store") {
  SECTION("Basic Mapping") {
    auto* parent_store = new ParentStore();

    parent_store->addParentRelation("2", "3");
    parent_store->addParentRelation("2", "4");

//    REQUIRE(parent_store->retrieveAllParentPairs() ==
//    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
//        PairHasherUtil::hash_pair>({ std::make_pair("1", "2"), std::make_pair("1", "4"),
//                                     std::make_pair("1", "5"), std::make_pair("2", "3") }));

    REQUIRE(parent_store->retrieveAllParentStarPairs() ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
                           PairHasherUtil::hash_pair>({ std::make_pair("2", "3"), std::make_pair("2", "4") }));

    REQUIRE(parent_store->retrieveAllAncestors("3") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));

  }
}

