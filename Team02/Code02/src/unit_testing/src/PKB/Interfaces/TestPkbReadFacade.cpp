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

    REQUIRE(pkb_read_facade_->GetVariablesModifiedByStatement("3")
                == std::unordered_set<std::string>({"z"}));
    REQUIRE(pkb_read_facade_->GetVariablesModifiedByStatement("2")
                == std::unordered_set<std::string>({"z", "x"}));

    REQUIRE(pkb_read_facade_->GetStatements()
                == std::unordered_set<std::string>({"4", "2", "3", "1"}));
    REQUIRE(pkb_read_facade_->GetStatementsThatModify(STATEMENT)
                == std::unordered_set<std::string>({"2", "3", "4", "1"}));

    REQUIRE(pkb_read_facade_->GetStatementsModifiesVariable("z", IF)
                == std::unordered_set<std::string>({"2"}));
  }
  SECTION("Test Calls API") {
    PKB pkb_ = PKB();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    pkb_write_facade_->AddCallsRelation("proc1", "proc2");
    pkb_write_facade_->AddCallsRelation("proc1", "proc3");
    pkb_write_facade_->AddCallsRelation("proc1", "proc4");
    pkb_write_facade_->AddCallsRelation("proc4","proc5");
    pkb_write_facade_->AddCallsRelation("proc5", "proc6");
    pkb_write_facade_->AddCallsRelation("proc5", "proc7");
    pkb_write_facade_->AddCallsRelation("proc5", "proc8");
    pkb_write_facade_->AddCallsRelation("proc5", "proc9");
    pkb_write_facade_->AddCallsRelation("proc10", "proc11");
    pkb_write_facade_->AddCallsRelation("proc10", "proc12");
    pkb_write_facade_->AddCallsRelation("proc12", "proc13");
    REQUIRE(pkb_read_facade_->GetAllCallsPairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
                      std::make_pair("proc1","proc2"), std::make_pair("proc1", "proc3"),
                      std::make_pair("proc1","proc4"), std::make_pair("proc4", "proc5"),
                      std::make_pair("proc5","proc6"), std::make_pair("proc5", "proc7"),
                      std::make_pair("proc5","proc8"), std::make_pair("proc5", "proc9"),
                      std::make_pair("proc10","proc11"), std::make_pair("proc12", "proc13"),
                      std::make_pair("proc10", "proc12")

            }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairs() == std::unordered_set<std::pair<PkbTypes::PROCEDURE,
            PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
              std::make_pair("proc1","proc2"), std::make_pair("proc1", "proc3"),
              std::make_pair("proc1","proc4"), std::make_pair("proc4", "proc5"),
              std::make_pair("proc5","proc6"), std::make_pair("proc5", "proc7"),
              std::make_pair("proc5","proc8"), std::make_pair("proc5", "proc9"),
              std::make_pair("proc10","proc11"), std::make_pair("proc12", "proc13"),
              std::make_pair("proc1","proc5"), std::make_pair("proc1", "proc6"),
              std::make_pair("proc1","proc7"), std::make_pair("proc1", "proc8"),
              std::make_pair("proc1","proc9"), std::make_pair("proc4", "proc6"),
              std::make_pair("proc4","proc7"), std::make_pair("proc4", "proc8"),
              std::make_pair("proc4","proc9"), std::make_pair("proc10", "proc13"),
              std::make_pair("proc10", "proc12")
            }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc12") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
              std::make_pair("proc12", "proc13")
            }));
    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc1") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc2"), std::make_pair("proc1", "proc3"),
          std::make_pair("proc1", "proc4")
        }));
    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc4") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc4", "proc5")
        }));
    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc5") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc5", "proc6"), std::make_pair("proc5", "proc7"),
          std::make_pair("proc5", "proc8"), std::make_pair("proc5", "proc9")
        }));
    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCaller("proc10") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc10", "proc11"), std::make_pair("proc10", "proc12")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc1") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc2"), std::make_pair("proc1", "proc3"),
          std::make_pair("proc1", "proc4"), std::make_pair("proc1", "proc5"),
          std::make_pair("proc1", "proc6"), std::make_pair("proc1", "proc7"),
          std::make_pair("proc1", "proc8"), std::make_pair("proc1", "proc9"),
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc4") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc4", "proc5"), std::make_pair("proc4", "proc6"),
          std::make_pair("proc4", "proc7"), std::make_pair("proc4", "proc8"),
          std::make_pair("proc4", "proc9")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc5") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc5", "proc6"), std::make_pair("proc5", "proc7"),
          std::make_pair("proc5", "proc8"), std::make_pair("proc5", "proc9")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc10") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc10", "proc11"), std::make_pair("proc10", "proc13"),
          std::make_pair("proc10", "proc12")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCaller("proc12") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc12", "proc13")
        }));



  }


}

