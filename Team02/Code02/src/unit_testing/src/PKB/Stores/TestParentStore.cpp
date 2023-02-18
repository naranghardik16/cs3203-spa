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
    auto parent_store = new ParentStore();

    parent_store->addParentRelation("1", "2");
    parent_store->addParentRelation("4", "8");

    REQUIRE(parent_store->hasAnyParentRelation() == true);
    REQUIRE(parent_store->hasParentRelation("1", "2") == true);
    REQUIRE(parent_store->hasParentRelation("4", "8") == true);
    REQUIRE_FALSE(parent_store->hasParentRelation("1", "8") == true);
    REQUIRE(parent_store->retrieveAllParentPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
              std::make_pair("1", "2"), std::make_pair("4", "8")}) );
    REQUIRE(parent_store->retrieveAllParents() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "4" }));
    REQUIRE(parent_store->retrieveAllParents("2") ==  PkbTypes::STATEMENT_NUMBER("1"));
    REQUIRE(parent_store->retrieveAllParents("8") ==  PkbTypes::STATEMENT_NUMBER("4"));
    REQUIRE(parent_store->retrieveAllChildren() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2", "8" }));
    REQUIRE(parent_store->retrieveAllChildren("1") ==  std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2" }));
    REQUIRE(parent_store->retrieveAllChildren("4") ==  std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "8" }));
    REQUIRE(parent_store->retrieveAllAncestors() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "1", "4" }));
    REQUIRE(parent_store->retrieveAllDescendants() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({ "2", "8" }));
  }

  SECTION("Dependent Parent with Single Transitive Relationship") {
    auto parent_store = new ParentStore();

    parent_store->addParentRelation("1", "2");
    parent_store->addParentRelation("2", "3");

  }

  SECTION("Dependent Follows with Multiple Transitive Relationship") {
    auto parent_store = new ParentStore();

  }

  SECTION("Checking ParentStar") {
    auto parent_store = new ParentStore();


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

