#include <catch.hpp>
#include "PKB/Stores/ParentStore.h"

TEST_CASE("Testcases for Parent Store") {
  typedef PkbTypes::STATEMENT_NUMBER StatementNumber;
  typedef std::unordered_set<std::pair<StatementNumber, StatementNumber>, PairHasherUtil::hash_pair>
      StatementStatementPairSet;
  typedef std::unordered_set<StatementNumber> StatementNumberSet;

  SECTION("Empty Parent Store") {
    auto parent_store = new ParentStore();

    REQUIRE(parent_store->HasParentRelation() == false);
    REQUIRE(parent_store->HasParentRelation("1", "2") == false);

    REQUIRE(parent_store->HasParentStarRelation() == false);
    REQUIRE(parent_store->HasParentStarRelation("2") == false);

    REQUIRE(parent_store->HasParentStarRelationBy("2") == false);

    REQUIRE(parent_store->GetParentPairs() == StatementStatementPairSet({}));
    REQUIRE(parent_store->GetParentStarPairs() == StatementStatementPairSet({}));

    REQUIRE(parent_store->HasParentStarRelation("1", "2") == false);
    REQUIRE(parent_store->GetParents() == StatementNumberSet({}));
    REQUIRE(parent_store->GetParents("2") == StatementNumber({}));
    REQUIRE(parent_store->GetChildren() == StatementNumberSet({}));
    REQUIRE(parent_store->GetChildren("2") == StatementNumberSet({}));
    REQUIRE(parent_store->GetAncestors() == StatementNumberSet({}));
    REQUIRE(parent_store->GetAncestors("2") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants() == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("2") == StatementNumberSet({}));
  }

  SECTION("Independent Parent without any Transitive Relationship") {
    auto parent_store = new ParentStore();

    parent_store->AddParentRelation("1", "2");
    parent_store->AddParentRelation("4", "8");
    parent_store->AddParentStarRelation();

    REQUIRE(parent_store->HasParentRelation() == true);
    REQUIRE(parent_store->HasParentRelation("1", "2") == true);
    REQUIRE(parent_store->HasParentRelation("4", "8") == true);
    REQUIRE_FALSE(parent_store->HasParentRelation("1", "8") == true);

    REQUIRE(parent_store->GetParents() == StatementNumberSet({"1", "4"}));
    REQUIRE(parent_store->GetParents("2") == StatementNumber("1"));
    REQUIRE(parent_store->GetParents("8") == StatementNumber("4"));

    REQUIRE(parent_store->GetChildren() == StatementNumberSet({"2", "8"}));
    REQUIRE(parent_store->GetChildren("1") == StatementNumberSet({"2"}));
    REQUIRE(parent_store->GetChildren("4") == StatementNumberSet({"8"}));

    REQUIRE(parent_store->GetAncestors() == StatementNumberSet({"1", "4"}));
    REQUIRE(parent_store->GetDescendants() == StatementNumberSet({"2", "8"}));

    REQUIRE(parent_store->GetParentPairs() ==
        StatementStatementPairSet({std::make_pair("1", "2"), std::make_pair("4", "8")}));
  }

  SECTION("Dependent Parent with Single Transitive Relationship") {
    auto parent_store = new ParentStore();

    parent_store->AddParentRelation("1", "2");
    parent_store->AddParentRelation("1", "3");
    parent_store->AddParentRelation("3", "4");
    parent_store->AddParentStarRelation();

    REQUIRE(parent_store->HasParentRelation("1", "2") == true);
    REQUIRE(parent_store->HasParentRelation("1", "3") == true);
    REQUIRE(parent_store->HasParentRelation("3", "4") == true);

    REQUIRE(parent_store->GetChildren() == StatementNumberSet({"2", "3", "4"}));
    REQUIRE(parent_store->GetChildren("1") == StatementNumberSet({"2", "3"}));
    REQUIRE(parent_store->GetChildren("3") == StatementNumberSet({"4"}));

    REQUIRE(parent_store->GetParents() == StatementNumberSet({"1", "3"}));
    REQUIRE(parent_store->GetParents("2") == StatementNumber("1"));
    REQUIRE(parent_store->GetParents("3") == StatementNumber("1"));
    REQUIRE(parent_store->GetParents("4") == StatementNumber("3"));

    REQUIRE(parent_store->GetParentPairs() ==
        StatementStatementPairSet({std::make_pair("1", "2"), std::make_pair("1", "3"),
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
    parent_store->AddParentStarRelation();

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

    REQUIRE(parent_store->GetChildren() == StatementNumberSet({"2", "3", "4", "5", "6", "7",
                                                               "8", "9", "11", "12", "13"}));
    REQUIRE(parent_store->GetChildren("1") == StatementNumberSet({"2", "3", "4"}));
    REQUIRE(parent_store->GetChildren("4") == StatementNumberSet({"5"}));
    REQUIRE(parent_store->GetChildren("5") == StatementNumberSet({"6", "7", "8", "9"}));
    REQUIRE(parent_store->GetChildren("10") == StatementNumberSet({"11", "12"}));
    REQUIRE(parent_store->GetChildren("12") == StatementNumberSet({"13"}));

    REQUIRE(parent_store->GetParents() == StatementNumberSet({"1", "4", "5", "10", "12"}));
    REQUIRE(parent_store->GetParents("2") == StatementNumber("1"));
    REQUIRE(parent_store->GetParents("3") == StatementNumber("1"));
    REQUIRE(parent_store->GetParents("4") == StatementNumber("1"));
    REQUIRE(parent_store->GetParents("5") == StatementNumber("4"));
    REQUIRE(parent_store->GetParents("6") == StatementNumber("5"));
    REQUIRE(parent_store->GetParents("7") == StatementNumber("5"));
    REQUIRE(parent_store->GetParents("8") == StatementNumber("5"));
    REQUIRE(parent_store->GetParents("9") == StatementNumber("5"));
    REQUIRE(parent_store->GetParents("11") == StatementNumber("10"));
    REQUIRE(parent_store->GetParents("12") == StatementNumber("10"));
    REQUIRE(parent_store->GetParents("13") == StatementNumber("12"));

    REQUIRE(parent_store->GetParentPairs() ==
        StatementStatementPairSet({std::make_pair("1", "2"), std::make_pair("1", "3"),
                                   std::make_pair("1", "4"), std::make_pair("4", "5"),
                                   std::make_pair("5", "6"), std::make_pair("5", "7"),
                                   std::make_pair("5", "8"), std::make_pair("5", "9"),
                                   std::make_pair("10", "11"), std::make_pair("10", "12"),
                                   std::make_pair("12", "13")}));
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
    parent_store->AddParentStarRelation();

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
    REQUIRE(parent_store->GetAncestors() == StatementNumberSet({"1", "4", "5", "10", "12"}));
    REQUIRE(parent_store->GetAncestors("5") == StatementNumberSet({"1", "4"}));
    REQUIRE(parent_store->GetAncestors("2") == StatementNumberSet({"1"}));
    REQUIRE(parent_store->GetAncestors("3") == StatementNumberSet({"1"}));
    REQUIRE(parent_store->GetAncestors("4") == StatementNumberSet({"1"}));
    REQUIRE(parent_store->GetAncestors("5") == StatementNumberSet({"4", "1"}));
    REQUIRE(parent_store->GetAncestors("6") == StatementNumberSet({"5", "4", "1"}));
    REQUIRE(parent_store->GetAncestors("7") == StatementNumberSet({"5", "4", "1"}));
    REQUIRE(parent_store->GetAncestors("8") == StatementNumberSet({"5", "4", "1"}));
    REQUIRE(parent_store->GetAncestors("9") == StatementNumberSet({"5", "4", "1"}));
    REQUIRE(parent_store->GetAncestors("11") == StatementNumberSet({"10"}));
    REQUIRE(parent_store->GetAncestors("12") == StatementNumberSet({"10"}));
    REQUIRE(parent_store->GetAncestors("13") == StatementNumberSet({"12", "10"}));
    REQUIRE(parent_store->GetDescendants() == StatementNumberSet({"2", "3", "4", "5", "6", "7",
                                                                  "8", "9", "11", "12", "13"}));
    REQUIRE(parent_store->GetDescendants("1") == StatementNumberSet({"2", "3", "4", "5", "6", "7", "8", "9"}));
    REQUIRE(parent_store->GetDescendants("2") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("3") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("4") == StatementNumberSet({"5", "6", "7", "8", "9"}));
    REQUIRE(parent_store->GetDescendants("5") == StatementNumberSet({"6", "7", "8", "9"}));
    REQUIRE(parent_store->GetDescendants("6") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("7") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("8") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("9") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("10") == StatementNumberSet({"11", "12", "13"}));
    REQUIRE(parent_store->GetDescendants("11") == StatementNumberSet({}));
    REQUIRE(parent_store->GetDescendants("12") == StatementNumberSet({"13"}));
    REQUIRE(parent_store->GetDescendants("13") == StatementNumberSet({}));
  }
}

