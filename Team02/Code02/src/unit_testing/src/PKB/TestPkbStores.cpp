
#include "catch.hpp"
#include "PKB.h"
#include <string>

TEST_CASE("Check if the variables are being correctly added to the PKB variable store") {
  SECTION("Test simple case of adding a single variable") {
    PKB pkb;
    PKBStores *pkb_stores= pkb.getStores();

    PKB::VARIABLE v0 = "a";

    REQUIRE(pkb_stores->addVariable(v0) == 1);

  }

  SECTION("Test simple case of adding multiple variables") {
    PKB pkb;
    PKBStores *pkb_stores= pkb.getStores();

    PKB::VARIABLE v1 = "b";
    PKB::VARIABLE v2 = "c";
    PKB::VARIABLE v3 = "d";
    PKB::VARIABLE v4 = "bad";

    REQUIRE(pkb_stores->addVariable(v1) == 1);
    REQUIRE(pkb_stores->addVariable(v2) == 2);
    REQUIRE(pkb_stores->addVariable(v3) == 3);
  }
}

