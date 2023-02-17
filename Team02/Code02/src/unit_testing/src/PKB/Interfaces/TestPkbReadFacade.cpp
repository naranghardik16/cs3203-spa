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

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", IF);
    pkb_write_facade_->AddStatementOfAType("3", ASSIGN);
    pkb_write_facade_->AddStatementOfAType("4", ASSIGN);

    pkb_write_facade_->AddParentRelation("2", "3");
    pkb_write_facade_->AddParentRelation("2", "4");

    pkb_write_facade_->AddStatementModifyingVariable("1", "x");
    pkb_write_facade_->AddStatementModifyingVariable("3", "z");
    pkb_write_facade_->AddStatementModifyingVariable("4", "x");


    REQUIRE(pkb_read_facade_->GetVariablesModifiedByStatement("3") == std::unordered_set<std::string>({ "z" }));
    REQUIRE(pkb_read_facade_->GetVariablesModifiedByStatement("2") == std::unordered_set<std::string>({ "z", "x" }));

    REQUIRE(pkb_read_facade_->GetStatements() == std::unordered_set<std::string>({ "4", "2", "3", "1" }));
    REQUIRE(pkb_read_facade_->GetStatementsThatModify(STATEMENT) == std::unordered_set<std::string>({ "2", "3", "4", "1" }));

    REQUIRE(pkb_read_facade_->GetStatementsModifiesVariable("z", STATEMENT) == std::unordered_set<std::string>({ "2", "3" }));
  }

}

