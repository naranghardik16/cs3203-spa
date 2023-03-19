#include <catch.hpp>
#include "PKB/Stores/ParentStore.h"

TEST_CASE("Testcases for Parent Store") {
  SECTION("Empty Parent Store") {
    auto parent_store = new ParentStore();
    REQUIRE(parent_store->HasParentRelation() == false);
    REQUIRE(parent_store->HasParentStarRelation() == false);
    REQUIRE(parent_store->HasParentStarRelation("2") == false);
    REQUIRE(parent_store->HasParentRelation("1", "2") == false);
    REQUIRE(parent_store->HasParentStarRelationBy("2") == false);
    REQUIRE(parent_store->GetParentPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                           PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({}));
    REQUIRE(parent_store->GetParentStarPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                               PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({}));
    REQUIRE(parent_store->HasParentStarRelation("1", "2") == false);
    REQUIRE(parent_store->GetParents() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->GetParents("2") == PkbTypes::STATEMENT_NUMBER({}));
    REQUIRE(parent_store->GetChildren() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->GetChildren("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->GetAncestors() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->GetAncestors("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->GetDescendants() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({}));
    REQUIRE(parent_store->GetDescendants("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {}));
  }

  SECTION("Independent Parent without any Transitive Relationship") {
    auto parent_store = new ParentStore();

    parent_store->AddParentRelation("1", "2");
    parent_store->AddParentRelation("4", "8");

    REQUIRE(parent_store->HasParentRelation() == true);
    REQUIRE(parent_store->HasParentRelation("1", "2") == true);
    REQUIRE(parent_store->HasParentRelation("4", "8") == true);
    REQUIRE_FALSE(parent_store->HasParentRelation("1", "8") == true);
    REQUIRE(parent_store->GetParentPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                           PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
              std::make_pair("1", "2"), std::make_pair("4", "8")}));
    REQUIRE(parent_store->GetParents() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1", "4" }));
    REQUIRE(parent_store->GetParents("2") ==  PkbTypes::STATEMENT_NUMBER("1"));
    REQUIRE(parent_store->GetParents("8") ==  PkbTypes::STATEMENT_NUMBER("4"));
    REQUIRE(parent_store->GetChildren() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2", "8" }));
    REQUIRE(parent_store->GetChildren("1") ==  std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "2" }));
    REQUIRE(parent_store->GetChildren("4") ==  std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "8" }));
    REQUIRE(parent_store->GetAncestors() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1", "4" }));
    REQUIRE(parent_store->GetDescendants() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"2", "8" }));
  }

  SECTION("Dependent Parent with Single Transitive Relationship") {
    auto parent_store = new ParentStore();

    parent_store->AddParentRelation("1", "2");
    parent_store->AddParentRelation("1", "3");
    parent_store->AddParentRelation("3", "4");

    REQUIRE(parent_store->HasParentRelation("1", "2") == true);
    REQUIRE(parent_store->HasParentRelation("1", "3") == true);
    REQUIRE(parent_store->HasParentRelation("3", "4") == true);

    REQUIRE(parent_store->GetChildren() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "2", "3", "4" }));
    REQUIRE(parent_store->GetChildren("1") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "2", "3" }));
    REQUIRE(parent_store->GetChildren("3") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "4" }));


    REQUIRE(parent_store->GetParents() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({"1", "3" }));
    REQUIRE(parent_store->GetParents("2") == PkbTypes::STATEMENT_NUMBER("1"));
    REQUIRE(parent_store->GetParents("3") == PkbTypes::STATEMENT_NUMBER("1"));
    REQUIRE(parent_store->GetParents("4") == PkbTypes::STATEMENT_NUMBER("3"));

    REQUIRE(parent_store->GetParentPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                           PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
              std::make_pair("1", "2"), std::make_pair("1", "3"),
              std::make_pair("3", "4")}));

    REQUIRE(parent_store->HasParentRelation() == true);
  }

  SECTION("Dependent Follows with Multiple Transitive Relationship") {
    auto parent_store = new ParentStore();

    parent_store->AddParentRelation("1", "2");
    parent_store->AddParentRelation("1", "3");
    parent_store->AddParentRelation("1", "4");
    parent_store->AddParentRelation("4", "5");
    parent_store->AddParentRelation("5", "6");
    parent_store->AddParentRelation("5", "7");
    parent_store->AddParentRelation("5", "8");
    parent_store->AddParentRelation("5", "9");
    parent_store->AddParentRelation("10", "11");
    parent_store->AddParentRelation("10", "12");
    parent_store->AddParentRelation("12", "13");

    REQUIRE(parent_store->HasParentRelation() == true);

    REQUIRE(parent_store->HasParentRelation("1", "2") == true);
    REQUIRE(parent_store->HasParentRelation("1", "3") == true);
    REQUIRE(parent_store->HasParentRelation("1", "4") == true);
    REQUIRE(parent_store->HasParentRelation("4", "5") == true);
    REQUIRE(parent_store->HasParentRelation("5", "6") == true);
    REQUIRE(parent_store->HasParentRelation("5", "7") == true);
    REQUIRE(parent_store->HasParentRelation("5", "8") == true);
    REQUIRE(parent_store->HasParentRelation("5", "9") == true);
    REQUIRE(parent_store->HasParentRelation("10", "11") == true);
    REQUIRE(parent_store->HasParentRelation("10", "12") == true);
    REQUIRE(parent_store->HasParentRelation("12", "13") == true);

    REQUIRE(parent_store->GetChildren() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "2", "3", "4", "5", "6", "7", "8", "9", "11", "12", "13" }));
    REQUIRE(parent_store->GetChildren("1") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "2", "3", "4" }));
    REQUIRE(parent_store->GetChildren("4") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "5" }));
    REQUIRE(parent_store->GetChildren("5") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "6", "7", "8", "9" }));
    REQUIRE(parent_store->GetChildren("10") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "11", "12" }));
    REQUIRE(parent_store->GetChildren("12") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "13" }));


    REQUIRE(parent_store->GetParents() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "1", "4", "5", "10", "12" }));
    REQUIRE(parent_store->GetParents("2") == PkbTypes::STATEMENT_NUMBER("1"));
    REQUIRE(parent_store->GetParents("3") == PkbTypes::STATEMENT_NUMBER("1"));
    REQUIRE(parent_store->GetParents("4") == PkbTypes::STATEMENT_NUMBER("1"));
    REQUIRE(parent_store->GetParents("5") == PkbTypes::STATEMENT_NUMBER("4"));
    REQUIRE(parent_store->GetParents("6") == PkbTypes::STATEMENT_NUMBER("5"));
    REQUIRE(parent_store->GetParents("7") == PkbTypes::STATEMENT_NUMBER("5"));
    REQUIRE(parent_store->GetParents("8") == PkbTypes::STATEMENT_NUMBER("5"));
    REQUIRE(parent_store->GetParents("9") == PkbTypes::STATEMENT_NUMBER("5"));
    REQUIRE(parent_store->GetParents("11") == PkbTypes::STATEMENT_NUMBER("10"));
    REQUIRE(parent_store->GetParents("12") == PkbTypes::STATEMENT_NUMBER("10"));
    REQUIRE(parent_store->GetParents("13") == PkbTypes::STATEMENT_NUMBER("12"));

    REQUIRE(parent_store->GetParentPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                           PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
              std::make_pair("1", "2"), std::make_pair("1", "3"),
              std::make_pair("1", "4"), std::make_pair("4", "5"),
              std::make_pair("5", "6"), std::make_pair("5", "7"),
              std::make_pair("5", "8"), std::make_pair("5", "9"),
              std::make_pair("10", "11"), std::make_pair("10", "12"),
              std::make_pair("12", "13") }));
  }

  SECTION("Checking ParentStar") {
    auto parent_store = new ParentStore();

    parent_store->AddParentRelation("1", "2");
    parent_store->AddParentRelation("1", "3");
    parent_store->AddParentRelation("1", "4");
    parent_store->AddParentRelation("4", "5");
    parent_store->AddParentRelation("5", "6");
    parent_store->AddParentRelation("5", "7");
    parent_store->AddParentRelation("5", "8");
    parent_store->AddParentRelation("5", "9");
    parent_store->AddParentRelation("10", "11");
    parent_store->AddParentRelation("10", "12");
    parent_store->AddParentRelation("12", "13");

    REQUIRE(parent_store->HasParentStarRelation("1", "2") == true);
    REQUIRE(parent_store->HasParentStarRelation("1", "3") == true);
    REQUIRE(parent_store->HasParentStarRelation("1", "4") == true);
    REQUIRE(parent_store->HasParentStarRelation("4", "5") == true);
    REQUIRE(parent_store->HasParentStarRelation("5", "6") == true);
    REQUIRE(parent_store->HasParentStarRelation("5", "7") == true);
    REQUIRE(parent_store->HasParentStarRelation("5", "8") == true);
    REQUIRE(parent_store->HasParentStarRelation("5", "9") == true);
    REQUIRE(parent_store->HasParentStarRelation("10", "11") == true);
    REQUIRE(parent_store->HasParentStarRelation("10", "12") == true);
    REQUIRE(parent_store->HasParentStarRelation("12", "13") == true);

    REQUIRE(parent_store->HasParentStarRelation("1", "5") == true);
    REQUIRE(parent_store->HasParentStarRelation("1", "6") == true);
    REQUIRE(parent_store->HasParentStarRelation("1", "7") == true);
    REQUIRE(parent_store->HasParentStarRelation("1", "8") == true);
    REQUIRE(parent_store->HasParentStarRelation("1", "9") == true);
    REQUIRE(parent_store->HasParentStarRelation("4", "6") == true);
    REQUIRE(parent_store->HasParentStarRelation("4", "7") == true);
    REQUIRE(parent_store->HasParentStarRelation("4", "8") == true);
    REQUIRE(parent_store->HasParentStarRelation("4", "9") == true);
    REQUIRE(parent_store->HasParentStarRelation("10", "13") == true);

    REQUIRE(parent_store->HasParentStarRelation() == true);
    REQUIRE(parent_store->GetAncestors() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "1", "4", "5", "10", "12"}));
    REQUIRE(parent_store->GetAncestors("5") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "1", "4" }));
    REQUIRE(parent_store->GetAncestors("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "1" }));
    REQUIRE(parent_store->GetAncestors("3") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "1" }));
    REQUIRE(parent_store->GetAncestors("4") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "1" }));
    REQUIRE(parent_store->GetAncestors("5") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "4", "1" }));
    REQUIRE(parent_store->GetAncestors("6") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "5", "4", "1" }));
    REQUIRE(parent_store->GetAncestors("7") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "5", "4", "1" }));
    REQUIRE(parent_store->GetAncestors("8") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "5", "4", "1" }));
    REQUIRE(parent_store->GetAncestors("9") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {  "5", "4", "1" }));
    REQUIRE(parent_store->GetAncestors("11") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {"10"}));
    REQUIRE(parent_store->GetAncestors("12") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {"10"}));
    REQUIRE(parent_store->GetAncestors("13") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {"12", "10"}));
    REQUIRE(parent_store->GetDescendants() == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "2", "3", "4", "5", "6", "7", "8", "9", "11", "12", "13"}));
    REQUIRE(parent_store->GetDescendants("1") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "2", "3", "4", "5", "6", "7", "8", "9"}));
    REQUIRE(parent_store->GetDescendants("2") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { }));
    REQUIRE(parent_store->GetDescendants("3") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { }));
    REQUIRE(parent_store->GetDescendants("4") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "5", "6", "7", "8", "9" }));
    REQUIRE(parent_store->GetDescendants("5") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({
      "6", "7", "8", "9"
    }));
    REQUIRE(parent_store->GetDescendants("6") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { }));
    REQUIRE(parent_store->GetDescendants("7") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { }));
    REQUIRE(parent_store->GetDescendants("8") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { }));
    REQUIRE(parent_store->GetDescendants("9") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { }));
    REQUIRE(parent_store->GetDescendants("10") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "11", "12", "13"}));
    REQUIRE(parent_store->GetDescendants("11") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { }));
    REQUIRE(parent_store->GetDescendants("12") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        { "13" }));
    REQUIRE(parent_store->GetDescendants("13") == std::unordered_set<PkbTypes::STATEMENT_NUMBER>(
        {  }));
  }
}

