#include <catch.hpp>
#include "PKB/Stores/FollowsStore.h"

TEST_CASE("Testcases for Follows Store") {
  SECTION("Basic Statement Number to Variable Mapping") {
    FollowsStore* follows_store = new FollowsStore();

    follows_store->addFollowsRelation("1", "2");
    follows_store->addFollowsRelation("2", "3");
    follows_store->addFollowsRelation("3", "4");

    REQUIRE(follows_store->retrieveAllFollowsPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
        PairHasherUtil::hash_pair>({ std::make_pair("1", "2"), std::make_pair("2", "3"),
                                     std::make_pair("3", "4") }));

    REQUIRE(follows_store->retrieveAllFollowsStarPairs() ==
        std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
            PairHasherUtil::hash_pair>({ std::make_pair("1", "2"), std::make_pair("2", "3"),
                                         std::make_pair("1", "3"), std::make_pair("3", "4"),
                                         std::make_pair("2", "4"), std::make_pair("1", "4") }));

  }
}