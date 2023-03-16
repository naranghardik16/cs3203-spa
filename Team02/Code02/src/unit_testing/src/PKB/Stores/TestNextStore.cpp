#include <catch.hpp>

#include "PKB/Stores/NextStore.h"

TEST_CASE("Testcases for Next Store") {
  SECTION("Empty Next Store") {
    auto next_store = new NextStore();

    REQUIRE(next_store->hasAnyNextRelation() == false);
  }

  SECTION("Extract Next Star Relations") {
    auto next_store = new NextStore();
  }

  SECTION("Check for Next Star Relation Existence") {}

  SECTION("Check for Next Relation Existence") {}
}
