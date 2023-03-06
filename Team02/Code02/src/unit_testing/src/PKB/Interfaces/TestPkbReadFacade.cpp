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

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc2") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc2")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc3") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc3")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc4") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc4")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc5") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc4", "proc5")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc6") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc5", "proc6")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc7") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc5", "proc7")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc8") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc5", "proc8")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc9") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc5", "proc9")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc11") == std::unordered_set<std::pair
    <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
      std::make_pair("proc10", "proc11")
    }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc12") == std::unordered_set<std::pair
    <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
      std::make_pair("proc10", "proc12")
    }));

    REQUIRE(pkb_read_facade_->GetAllCallsPairsWithSpecifiedCallee("proc13") == std::unordered_set<std::pair
    <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
      std::make_pair("proc12", "proc13")
    }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc2") == std::unordered_set<std::pair
    <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
      std::make_pair("proc1", "proc2")
    }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc3") == std::unordered_set<std::pair
    <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
      std::make_pair("proc1", "proc3")
    }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc4") == std::unordered_set<std::pair
    <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
      std::make_pair("proc1", "proc4")
    }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc5") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc5"), std::make_pair("proc4", "proc5")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc6") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc6"), std::make_pair("proc4", "proc6"),
          std::make_pair("proc5", "proc6"),
          }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc7") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc7"), std::make_pair("proc4", "proc7"),
          std::make_pair("proc5", "proc7")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc8") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc8"), std::make_pair("proc4", "proc8"),
          std::make_pair("proc5", "proc8")
        }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc9") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc1", "proc9"), std::make_pair("proc4", "proc9"),
          std::make_pair("proc5", "proc9"),
          }));

    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc11") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc10", "proc11")
          }));
    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc12") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc10", "proc12")
          }));
    REQUIRE(pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee("proc13") == std::unordered_set<std::pair
        <PkbTypes::PROCEDURE,PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>({
          std::make_pair("proc10", "proc13"), std::make_pair("proc12", "proc13"),
          }));

    REQUIRE(pkb_read_facade_->HasCallsRelation("proc1", "proc2") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc1", "proc3") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc1", "proc4") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc4", "proc5") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc8") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc5", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc10", "proc11") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc10", "proc12") == true);
    REQUIRE(pkb_read_facade_->HasCallsRelation("proc12", "proc13") == true);

    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc2") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc3") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc4") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc5") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc10", "proc11") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc10", "proc12") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc12", "proc13") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc5", "proc8") == true);

    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc5") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc8") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc1", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc6") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc7") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc8") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc4", "proc9") == true);
    REQUIRE(pkb_read_facade_->HasCallsStarRelation("proc10", "proc13") == true);



  }
}

