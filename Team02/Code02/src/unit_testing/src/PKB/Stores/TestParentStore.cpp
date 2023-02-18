#include <catch.hpp>
#include "PKB/Stores/ParentStore.h"

TEST_CASE("Testcases for Parent Store") {

  SECTION("Empty Parent Store") {
    auto parent_store = new ParentStore();
    REQUIRE(parent_store->hasAnyParentRelation() == false);
    REQUIRE(parent_store->hasAnyParentStarRelation() == false);
    REQUIRE(parent_store->hasParentStar("2") == false);
    REQUIRE(parent_store->hasParentRelation("1", "2") == false);
    REQUIRE(parent_store->hasParentStarBy("2") == false);
    REQUIRE(parent_store->hasAnyParentRelation() == false);
    REQUIRE(parent_store->retrieveAllParentPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({}));
    REQUIRE(parent_store->retrieveAllParentStarPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({}));
    REQUIRE(parent_store->hasParentStarRelation("1", "2") == false);
    REQUIRE(parent_store->retrieveAllParents() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->retrieveAllParents("2") == PkbTypes::STATEMENT_NUMBER({}));
    REQUIRE(parent_store->retrieveAllChildren() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->retrieveAllChildren("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->retrieveAllAncestors() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->retrieveAllAncestors("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->retrieveAllDescendants() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->retrieveAllDescendants("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
  }

  SECTION("Independent Parent without any Transitive Relationship") {

  }

  SECTION("Dependent Parent with Single Transitive Relationship") {

  }

  SECTION("Dependednt Follows with Multiple Transitive Relationship") {

  }

  SECTION("Checking ParentStar") {


  }

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

