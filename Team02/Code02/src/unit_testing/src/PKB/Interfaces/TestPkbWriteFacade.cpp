#include "catch.hpp"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"
#include <string>

TEST_CASE("Check if the variables are being correctly added to the PKB variable store") {
  SECTION("Test simple case of adding a single variable") {
    PKB pkb_ = PKB();
    PkbWriteFacade* pkb_write_facade_;
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    PkbTypes::VARIABLE v0 = "a";

    REQUIRE(pkb_write_facade_->AddVariable(v0) == 1);
  }

  SECTION("Test simple case of adding multiple variables") {
    PKB pkb_ = PKB();
    PkbWriteFacade* pkb_write_facade_;
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    PkbTypes::VARIABLE v1 = "b";
    PkbTypes::VARIABLE v2 = "c";
    PkbTypes::VARIABLE v3 = "d";
    PkbTypes::VARIABLE v4 = "bad";

    REQUIRE(pkb_write_facade_->AddVariable(v1) == 1);
    REQUIRE(pkb_write_facade_->AddVariable(v2) == 2);
    REQUIRE(pkb_write_facade_->AddVariable(v3) == 3);
    REQUIRE(pkb_write_facade_->AddVariable(v4) == 4);
  }

  SECTION("Test simple case of adding a single procedure") {
    PKB pkb_ = PKB();
    PkbWriteFacade* pkb_write_facade_;
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    PkbTypes::PROCEDURE p0 = "a";

    REQUIRE(pkb_write_facade_->AddProcedure(p0) == 1);
  }

  SECTION("Test simple case of adding multiple procedures") {
    PKB pkb_ = PKB();
    PkbWriteFacade* pkb_write_facade_;
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    PkbTypes::PROCEDURE p1 = "b";
    PkbTypes::PROCEDURE p2 = "c";
    PkbTypes::PROCEDURE p3 = "d";
    PkbTypes::PROCEDURE p4 = "bad";

    REQUIRE(pkb_write_facade_->AddProcedure(p1) == 1);
    REQUIRE(pkb_write_facade_->AddProcedure(p2) == 2);
    REQUIRE(pkb_write_facade_->AddProcedure(p3) == 3);
    REQUIRE(pkb_write_facade_->AddProcedure(p4) == 4);
  }

  SECTION("Test simple case of populating multiple constants") {
    PKB pkb_ = PKB();
    PkbWriteFacade* pkb_write_facade_;
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    PkbTypes::CONSTANT c1 = "-1";
    PkbTypes::CONSTANT c2 = "0";
    PkbTypes::CONSTANT c3 = "1";
    PkbTypes::CONSTANT c4 = "99";

    pkb_write_facade_->AddConstant(c1);
    pkb_write_facade_->AddConstant(c2);
    pkb_write_facade_->AddConstant(c3);
    pkb_write_facade_->AddConstant(c4);

    PkbReadFacade* pkb_read_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);

    std::unordered_set<std::string> constantStore = pkb_read_facade_->GetConstantStore();
    REQUIRE(constantStore == std::unordered_set<std::string>{c1, c2, c3, c4});
  }

}

