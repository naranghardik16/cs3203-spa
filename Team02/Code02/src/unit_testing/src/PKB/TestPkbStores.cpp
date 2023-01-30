
#include "catch.hpp"
#include "PKB.h"
#include <string>

TEST_CASE("Check if the variables are being correctly added to the PKB variable store") {
  SECTION("Test simple case of adding a single variable") {
    PKB pkb;
    PKBStores *pkb_stores = pkb.getStores();

    PKB::VARIABLE v0 = "a";

    REQUIRE(pkb_stores->addVariable(v0) == 1);
  }

  SECTION("Test simple case of adding multiple variables") {
    PKB pkb;
    PKBStores *pkb_stores = pkb.getStores();

    PKB::VARIABLE v1 = "b";
    PKB::VARIABLE v2 = "c";
    PKB::VARIABLE v3 = "d";
    PKB::VARIABLE v4 = "bad";

    REQUIRE(pkb_stores->addVariable(v1) == 1);
    REQUIRE(pkb_stores->addVariable(v2) == 2);
    REQUIRE(pkb_stores->addVariable(v3) == 3);
    REQUIRE(pkb_stores->addVariable(v4) == 4);
  }

  SECTION("Test simple case of adding a single procedure") {
    PKB pkb;
    PKBStores *pkb_stores = pkb.getStores();

    PKB::PROCEDURE p0 = "a";

    REQUIRE(pkb_stores->addProcedure(p0) == 1);
  }

  SECTION("Test simple case of adding multiple procedures") {
    PKB pkb;
    PKBStores *pkb_stores = pkb.getStores();

    PKB::PROCEDURE p1 = "b";
    PKB::PROCEDURE p2 = "c";
    PKB::PROCEDURE p3 = "d";
    PKB::PROCEDURE p4 = "bad";

    REQUIRE(pkb_stores->addProcedure(p1) == 1);
    REQUIRE(pkb_stores->addProcedure(p2) == 2);
    REQUIRE(pkb_stores->addProcedure(p3) == 3);
    REQUIRE(pkb_stores->addProcedure(p4) == 4);
  }

  SECTION("Test simple case of populating multiple constants") {
    PKB pkb;
    PKBStores *pkb_stores = pkb.getStores();

    PKB::CONSTANT c1 = "-1";
    PKB::CONSTANT c2 = "0";
    PKB::CONSTANT c3 = "1";
    PKB::CONSTANT c4 = "99";

    pkb_stores->addConstant(c1);
    pkb_stores->addConstant(c2);
    pkb_stores->addConstant(c3);
    pkb_stores->addConstant(c4);

    PKB::CONSTANT_STORE constantStore = pkb_stores->getConstantStore();
    REQUIRE(constantStore == PKB::CONSTANT_STORE{c1, c2, c3, c4});
  }


}

