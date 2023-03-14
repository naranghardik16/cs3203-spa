#include <catch.hpp>
#include "PKB/Stores/NextStore.h"

TEST_CASE("Testcases for Next Store") {
  SECTION("Empty Next Store") {
    auto next_store = new NextStore();
    REQUIRE(next_store->hasAnyNextRelation() == false);
  }

}

//  SECTION("Independent Next without any Transitive Relationship") {
//    auto next_store = new NextStore();
//    REQUIRE(next_store->hasNextRelation("1", "2") == true);
//    REQUIRE(next_store->hasNextRelation("4", "8") == true);
//    REQUIRE(next_store->hasAnyNextRelation() == true);
//
//    REQUIRE(next_store->retrieveAllNextPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
//                                                                                     PkbTypes::STATEMENT_NUMBER>,
//                                                                           PairHasherUtil::hash_pair>(
//        {std::make_pair("1", "2"), std::make_pair("4", "8")}));
//  }
