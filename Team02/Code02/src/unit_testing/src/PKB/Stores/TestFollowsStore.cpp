#include <catch.hpp>
#include "PKB/Stores/FollowsStore.h"

TEST_CASE("Testcases for Follows Store") {
  SECTION("Empty Follows Store") {
    auto follows_store = new FollowsStore();
    REQUIRE(follows_store->HasFollowsRelation() == false);
    REQUIRE(follows_store->HasFollowsStarRelation() == false);
    REQUIRE(follows_store->HasFollowsStarRelation("2", "3") == false);

    REQUIRE(follows_store->GetFollowsPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({ }));

    REQUIRE(follows_store->GetFollowsStarPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({ }));

    REQUIRE(follows_store->HasFollowsRelation("2", "3") == false);
    REQUIRE(follows_store->HasFollowsStarRelation("2") == false);
    REQUIRE(follows_store->HasFollowsStarRelationBy("2") == false);
  }

  SECTION("Independent Follows without any Transitive Relationship") {
    auto follows_store = new FollowsStore();
    follows_store->AddFollowsRelation("1", "2");
    follows_store->AddFollowsRelation("4", "8");

    REQUIRE(follows_store->HasFollowsRelation("1", "2") == true);
    REQUIRE(follows_store->HasFollowsRelation("4", "8") == true);
    REQUIRE(follows_store->HasFollowsRelation() == true);

    REQUIRE(follows_store->GetFollowsPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
      std::make_pair("1", "2"),
      std::make_pair("4", "8")
    }));

    REQUIRE(follows_store->HasFollowsStarRelation() == true);
  }

  SECTION("Dependent Follows with Single Transitive Relationship ") {
    auto follows_store = new FollowsStore();
    follows_store->AddFollowsRelation("1", "2");
    follows_store->AddFollowsRelation("2", "3");

    REQUIRE(follows_store->HasFollowsRelation() == true);
    REQUIRE(follows_store->HasFollowsRelation("1", "2") == true);
    REQUIRE(follows_store->HasFollowsRelation("2", "3") == true);
    REQUIRE(follows_store->GetFollowsPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
      std::make_pair("1", "2"),
      std::make_pair("2", "3")
    }));
  }

  SECTION("Dependent Follows with Multiple Transitive Relationship") {
    auto follows_store = new FollowsStore();

    follows_store->AddFollowsRelation("1", "2");
    follows_store->AddFollowsRelation("2", "3");
    follows_store->AddFollowsRelation("3", "4");
    follows_store->AddFollowsRelation("4", "5");
    follows_store->AddFollowsRelation("5", "6");
    follows_store->AddFollowsRelation("6", "7");
    follows_store->AddFollowsRelation("7", "8");
    follows_store->AddFollowsRelation("8", "9");

    REQUIRE(follows_store->GetFollowsPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                             PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
              std::make_pair("1", "2"), std::make_pair("2", "3"),
              std::make_pair("3", "4"), std::make_pair("4", "5"),
              std::make_pair("5", "6"), std::make_pair("6", "7"),
              std::make_pair("7", "8"), std::make_pair("8", "9"),
    }));
    REQUIRE(follows_store->HasFollowsRelation() == true);
    REQUIRE(follows_store->HasFollowsRelation("1", "2") == true);
    REQUIRE(follows_store->HasFollowsRelation("2", "3") == true);
    REQUIRE(follows_store->HasFollowsRelation("3", "4") == true);
    REQUIRE(follows_store->HasFollowsRelation("4", "5") == true);
    REQUIRE(follows_store->HasFollowsRelation("5", "6") == true);
    REQUIRE(follows_store->HasFollowsRelation("6", "7") == true);
    REQUIRE(follows_store->HasFollowsRelation("7", "8") == true);
    REQUIRE(follows_store->HasFollowsRelation("8", "9") == true);
  }

  SECTION("Checking FollowsStar") {
    auto follows_store = new FollowsStore();

    follows_store->AddFollowsRelation("1", "2");
    follows_store->AddFollowsRelation("2", "3");
    follows_store->AddFollowsRelation("3", "4");
    follows_store->AddFollowsRelation("4", "5");
    follows_store->AddFollowsRelation("5", "6");

    REQUIRE(follows_store->HasFollowsStarRelation() == true);
    REQUIRE(follows_store->HasFollowsStarRelation("1") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("2") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("3") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("4") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("5") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("6") == false);

    REQUIRE(follows_store->HasFollowsStarRelationBy("2") == true);
    REQUIRE(follows_store->HasFollowsStarRelationBy("3") == true);
    REQUIRE(follows_store->HasFollowsStarRelationBy("4") == true);
    REQUIRE(follows_store->HasFollowsStarRelationBy("5") == true);
    REQUIRE(follows_store->HasFollowsStarRelationBy("6") == true);
    REQUIRE_FALSE(follows_store->HasFollowsStarRelationBy("1") == true);

    REQUIRE(follows_store->HasFollowsStarRelation("1", "2") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("1", "3") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("1", "4") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("1", "5") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("1", "6") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("2", "3") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("2", "4") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("2", "5") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("2", "6") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("3", "4") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("3", "5") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("3", "6") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("4", "5") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("4", "6") == true);
    REQUIRE(follows_store->HasFollowsStarRelation("5", "6") == true);
    REQUIRE(follows_store->GetFollowsStarPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                                                                 PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
              std::make_pair("1", "2"),
              std::make_pair("1", "2"),
              std::make_pair("1", "2"),
              std::make_pair("2", "3"),
              std::make_pair("1", "3"),
              std::make_pair("2", "4"),
              std::make_pair("1", "4"),
              std::make_pair("2", "5"),
              std::make_pair("1", "5"),
              std::make_pair("2", "6"),
              std::make_pair("1", "6"),
              std::make_pair("3", "4"),
              std::make_pair("4", "6"),
              std::make_pair("3", "5"),
              std::make_pair("5", "6"),
              std::make_pair("3", "6"),
              std::make_pair("4", "5")
            }));
  }
}
