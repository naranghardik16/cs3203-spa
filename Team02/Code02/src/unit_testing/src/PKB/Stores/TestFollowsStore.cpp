#include <catch.hpp>
#include "PKB/Stores/FollowsStore.h"

TEST_CASE("Testcases for Follows Store") {
  SECTION("Empty Follows Store") {
    auto follows_store = new FollowsStore();
    REQUIRE(follows_store->hasAnyFollowsRelation() == false);
    REQUIRE(follows_store->hasAnyFollowsStarRelation() == false);
    REQUIRE(follows_store->hasFollowsStarRelation("2", "3") == false);

    REQUIRE(follows_store->retrieveAllFollowsPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({ }));

    REQUIRE(follows_store->retrieveAllFollowsStarPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({ }));

    REQUIRE(follows_store->hasFollowsRelation("2", "3") == false);
    REQUIRE(follows_store->hasFollowsStar("2") == false);
    REQUIRE(follows_store->hasFollowsStarBy("2") == false);
  }

  SECTION("Independent Follows without any Transitive Relationship") {
    auto follows_store = new FollowsStore();
    follows_store->addFollowsRelation("1", "2");
    follows_store->addFollowsRelation("4", "8");

    REQUIRE(follows_store->hasFollowsRelation("1", "2") == true);
    REQUIRE(follows_store->hasFollowsRelation("4", "8") == true);
    REQUIRE(follows_store->hasAnyFollowsRelation() == true);

    REQUIRE(follows_store->retrieveAllFollowsPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
      std::make_pair("1", "2"),
      std::make_pair("4", "8")
    }));

    REQUIRE(follows_store->hasAnyFollowsStarRelation() == true);
  }

  SECTION("Dependent Follows with Single Transitive Relationship ") {
    auto follows_store = new FollowsStore();
    follows_store->addFollowsRelation("1", "2");
    follows_store->addFollowsRelation("2", "3");

    REQUIRE(follows_store->hasAnyFollowsRelation() == true);
    REQUIRE(follows_store->hasFollowsRelation("1", "2") == true);
    REQUIRE(follows_store->hasFollowsRelation("2", "3") == true);
    REQUIRE(follows_store->retrieveAllFollowsPairs() ==
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
      std::make_pair("1", "2"),
      std::make_pair("2", "3")
    }));
  }

  SECTION("Dependent Follows with Multiple Transitive Relationship") {
    auto follows_store = new FollowsStore();

    follows_store->addFollowsRelation("1", "2");
    follows_store->addFollowsRelation("2", "3");
    follows_store->addFollowsRelation("3", "4");
    follows_store->addFollowsRelation("4", "5");
    follows_store->addFollowsRelation("5", "6");
    follows_store->addFollowsRelation("6", "7");
    follows_store->addFollowsRelation("7", "8");
    follows_store->addFollowsRelation("8", "9");

    REQUIRE(follows_store->retrieveAllFollowsPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
            PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
              std::make_pair("1", "2"), std::make_pair("2", "3"),
              std::make_pair("3", "4"), std::make_pair("4", "5"),
              std::make_pair("5", "6"), std::make_pair("6", "7"),
              std::make_pair("7", "8"), std::make_pair("8", "9"),
    }));
    REQUIRE(follows_store->hasAnyFollowsRelation() == true);
    REQUIRE(follows_store->hasFollowsRelation("1", "2") == true);
    REQUIRE(follows_store->hasFollowsRelation("2", "3") == true);
    REQUIRE(follows_store->hasFollowsRelation("3", "4") == true);
    REQUIRE(follows_store->hasFollowsRelation("4", "5") == true);
    REQUIRE(follows_store->hasFollowsRelation("5", "6") == true);
    REQUIRE(follows_store->hasFollowsRelation("6", "7") == true);
    REQUIRE(follows_store->hasFollowsRelation("7", "8") == true);
    REQUIRE(follows_store->hasFollowsRelation("8", "9") == true);
  }

  SECTION("Checking FollowsStar") {
    auto follows_store = new FollowsStore();

    follows_store->addFollowsRelation("1", "2");
    follows_store->addFollowsRelation("2", "3");
    follows_store->addFollowsRelation("3", "4");
    follows_store->addFollowsRelation("4", "5");
    follows_store->addFollowsRelation("5", "6");

    REQUIRE(follows_store->hasAnyFollowsStarRelation() == true);
    REQUIRE(follows_store->hasFollowsStar("1") == true);
    REQUIRE(follows_store->hasFollowsStar("2") == true);
    REQUIRE(follows_store->hasFollowsStar("3") == true);
    REQUIRE(follows_store->hasFollowsStar("4") == true);
    REQUIRE(follows_store->hasFollowsStar("5") == true);
    REQUIRE(follows_store->hasFollowsStar("6") == false);

    REQUIRE(follows_store->hasFollowsStarBy("2") == true);
    REQUIRE(follows_store->hasFollowsStarBy("3") == true);
    REQUIRE(follows_store->hasFollowsStarBy("4") == true);
    REQUIRE(follows_store->hasFollowsStarBy("5") == true);
    REQUIRE(follows_store->hasFollowsStarBy("6") == true);
    REQUIRE_FALSE(follows_store->hasFollowsStarBy("1") == true);

    REQUIRE(follows_store->hasFollowsStarRelation("1", "2") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("1", "3") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("1", "4") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("1", "5") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("1", "6") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("2", "3") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("2", "4") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("2", "5") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("2", "6") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("3", "4") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("3", "5") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("3", "6") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("4", "5") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("4", "6") == true);
    REQUIRE(follows_store->hasFollowsStarRelation("5", "6") == true);
    REQUIRE(follows_store->retrieveAllFollowsStarPairs() == std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
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
