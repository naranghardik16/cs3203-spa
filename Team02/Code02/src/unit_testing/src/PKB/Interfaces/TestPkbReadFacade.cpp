#include <catch.hpp>
#include <string>
#include <unordered_set>
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"

TEST_CASE("Testing PkbReadFacade") {
  SECTION("empty") {
    PKB pkb_ = PKB();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);
    PkbTypes::VARIABLE test_var1_ = "a";
    PkbTypes::CONSTANT test_constant1_ = "5";
    PkbTypes::PROCEDURE test_procedure1_ = "Anya";
    REQUIRE(pkb_read_facade_->GetVariables() == std::unordered_set<std::string>({}));
    pkb_write_facade_->AddVariable(test_var1_);
    pkb_write_facade_->AddConstant(test_constant1_);
    pkb_write_facade_->AddProcedure(test_procedure1_);
    REQUIRE(pkb_read_facade_->GetVariables() == std::unordered_set<std::string>({test_var1_}));
    REQUIRE(pkb_read_facade_->GetConstants() == std::unordered_set<std::string>({test_constant1_}));
    REQUIRE(pkb_read_facade_->GetProcedures() == std::unordered_set<std::string>({test_procedure1_}));
  }

}

