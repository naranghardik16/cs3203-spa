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

  SECTION("Test Next API - Complex CFG") {
    PKB pkb_ = PKB();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg->AddStmtCfg(2, node1);
    node1->AddStmt(3);
    cfg->AddStmtCfg(3, node1);

    std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
    node2->AddStmt(4);
    cfg->AddStmtCfg(4, node2);

    std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
    node3->AddStmt(5);
    cfg->AddStmtCfg(5, node3);

    std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
    node4->AddStmt(6);
    cfg->AddStmtCfg(6, node4);

    std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();
    node5->AddStmt(7);
    cfg->AddStmtCfg(7, node5);

    std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
    node6->AddStmt(8);
    cfg->AddStmtCfg(8, node6);

    std::shared_ptr<CfgNode> node7 = std::make_shared<CfgNode>();
    node7->AddStmt(9);
    cfg->AddStmtCfg(9, node7);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", READ);
    pkb_write_facade_->AddStatementOfAType("3", READ);
    pkb_write_facade_->AddStatementOfAType("4", READ);
    pkb_write_facade_->AddStatementOfAType("5", READ);
    pkb_write_facade_->AddStatementOfAType("6", READ);
    pkb_write_facade_->AddStatementOfAType("7", READ);
    pkb_write_facade_->AddStatementOfAType("8", READ);
    pkb_write_facade_->AddStatementOfAType("9", READ);

    node1->AddTransition(true, node2);
    node2->AddTransition(true, node3);
    node3->AddTransition(true, node2);
    node2->AddTransition(false, node4);
    node4->AddTransition(false, node5);
    node4->AddTransition(true, node6);
    node6->AddTransition(true, node7);

    cfg->AddProcCfg("main", node1);

    pkb_write_facade_->AddCfg(cfg);

    REQUIRE(pkb_read_facade_->IsNext("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "5") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "8") == true);
    REQUIRE(pkb_read_facade_->IsNext("8", "9") == true);


    REQUIRE(pkb_read_facade_->HasNext("1") == true);
    REQUIRE(pkb_read_facade_->HasNext("2") == true);
    REQUIRE(pkb_read_facade_->HasNext("3") == true);
    REQUIRE(pkb_read_facade_->HasNext("5") == true);
    REQUIRE(pkb_read_facade_->HasNext("4") == true);
    REQUIRE(pkb_read_facade_->HasNext("6") == true);
    REQUIRE(pkb_read_facade_->HasNext("8") == true);

    REQUIRE(pkb_read_facade_->GetNext("1", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("2")});
    REQUIRE(pkb_read_facade_->GetNext("2", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("3")});
    REQUIRE(pkb_read_facade_->GetNext("3", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("4")});
    // this should give true for 4 -> 5,6 but giving false
    // this should also give true for 6 -> 7,8 but giving false
    REQUIRE(pkb_read_facade_->GetNext("8", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("9")});

    REQUIRE(pkb_read_facade_->GetNextBy("2", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("1")});
    REQUIRE(pkb_read_facade_->GetNextBy("3", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("2")});
    REQUIRE(pkb_read_facade_->GetNextBy("9", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("8")});

    REQUIRE(pkb_read_facade_->GetNextFirst(READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>({"1","2","3","5","4","6","8"}));
    REQUIRE(pkb_read_facade_->GetNextSecond(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({
      "2","3","4","5","6","7","8","9"
    }));

    REQUIRE(pkb_read_facade_->GetNextPairs(READ, READ) == std::unordered_set<std::pair
    <PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
      std::make_pair("1","2"), std::make_pair("2","3"),
      std::make_pair("3","4"), std::make_pair("4","5"),
      std::make_pair("4","6"), std::make_pair("5","4"),
      std::make_pair("6","7"), std::make_pair("6","8"),
      std::make_pair("8","9")
      }));

  }
  SECTION("Test Next API - With Dummy Node") {
    PKB pkb_ = PKB();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg->AddStmtCfg(2, node1);

    std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
    node2->AddStmt(3);
    cfg->AddStmtCfg(3, node2);
    node2->AddStmt(4);
    cfg->AddStmtCfg(4, node2);

    std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
    node3->AddStmt(5);
    cfg->AddStmtCfg(5, node3);
    node3->AddStmt(6);
    cfg->AddStmtCfg(6, node3);

    std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
    node4->AddStmt(7);
    cfg->AddStmtCfg(7, node4);
    node4->AddStmt(8);
    cfg->AddStmtCfg(8, node4);

    std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();

    std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
    node6->AddStmt(9);
    cfg->AddStmtCfg(9, node6);
    node6->AddStmt(10);
    cfg->AddStmtCfg(10, node6);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", READ);
    pkb_write_facade_->AddStatementOfAType("3", READ);
    pkb_write_facade_->AddStatementOfAType("4", READ);
    pkb_write_facade_->AddStatementOfAType("5", READ);
    pkb_write_facade_->AddStatementOfAType("6", READ);
    pkb_write_facade_->AddStatementOfAType("7", READ);
    pkb_write_facade_->AddStatementOfAType("8", READ);
    pkb_write_facade_->AddStatementOfAType("9", READ);
    pkb_write_facade_->AddStatementOfAType("10", READ);

    node1->AddTransition(true, node2);
    node1->AddTransition(false, node3);

    node2->AddTransition(true, node4);
    node3->AddTransition(true, node4);
    node4->AddTransition(true, node5);
    node5->AddTransition(true, node6);

    cfg->AddProcCfg("main", node1);

    pkb_write_facade_->AddCfg(cfg);

    REQUIRE(pkb_read_facade_->IsNext("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "5") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("7", "8") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("8", "9") == true);
    REQUIRE(pkb_read_facade_->IsNext("9", "10") == true);

    REQUIRE(pkb_read_facade_->HasNext("1") == true);
    REQUIRE(pkb_read_facade_->HasNext("2") == true);
    REQUIRE(pkb_read_facade_->HasNext("3") == true);
    REQUIRE(pkb_read_facade_->HasNext("5") == true);
    REQUIRE(pkb_read_facade_->HasNext("4") == true);
    REQUIRE(pkb_read_facade_->HasNext("6") == true);
    REQUIRE(pkb_read_facade_->HasNext("7") == true);
    REQUIRE(pkb_read_facade_->HasNext("8") == true);
    REQUIRE(pkb_read_facade_->HasNext("9") == true);

    REQUIRE(pkb_read_facade_->GetNext("1", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("2")});
    REQUIRE(pkb_read_facade_->GetNext("3", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("4")});
    REQUIRE(pkb_read_facade_->GetNext("5", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("6")});
    REQUIRE(pkb_read_facade_->GetNext("7", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("8")});
    REQUIRE(pkb_read_facade_->GetNext("9", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("10")});

    REQUIRE(pkb_read_facade_->GetNextBy("2", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("1")});
    REQUIRE(pkb_read_facade_->GetNextBy("4", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("3")});
    REQUIRE(pkb_read_facade_->GetNextBy("6", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("5")});
    REQUIRE(pkb_read_facade_->GetNextBy("8", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("7")});
    REQUIRE(pkb_read_facade_->GetNextBy("10", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("9")});


    REQUIRE(pkb_read_facade_->GetNextFirst(READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>({"1","2","3","5","4","6","7","8","9"}));
    REQUIRE(pkb_read_facade_->GetNextSecond(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({
      "2","3","4","5","6","7","8","9","10"
    }));

    REQUIRE(pkb_read_facade_->GetNextPairs(READ, READ) == std::unordered_set<std::pair
    <PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
      std::make_pair("1","2"), std::make_pair("2","3"),
      std::make_pair("3","4"), std::make_pair("5","6"),
      std::make_pair("2","5"), std::make_pair("4","7"),
      std::make_pair("7","8"), std::make_pair("6","7"),
      std::make_pair("8","9"), std::make_pair("9","10"),
      }));
  }

  SECTION("Test Next API - Basic CFG") {
    PKB pkb_ = PKB();
    PkbReadFacade *pkb_read_facade_;
    PkbWriteFacade *pkb_write_facade_;
    pkb_read_facade_ = new PkbReadFacade(pkb_);
    pkb_write_facade_ = new PkbWriteFacade(pkb_);

    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg->AddStmtCfg(2, node1);

    std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
    node2->AddStmt(3);
    cfg->AddStmtCfg(3, node2);
    node2->AddStmt(4);
    cfg->AddStmtCfg(4, node2);

    std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
    node3->AddStmt(5);
    cfg->AddStmtCfg(5, node3);
    node3->AddStmt(6);
    cfg->AddStmtCfg(6, node3);

    pkb_write_facade_->AddStatementOfAType("1", READ);
    pkb_write_facade_->AddStatementOfAType("2", READ);
    pkb_write_facade_->AddStatementOfAType("3", READ);
    pkb_write_facade_->AddStatementOfAType("4", READ);
    pkb_write_facade_->AddStatementOfAType("5", READ);
    pkb_write_facade_->AddStatementOfAType("6", READ);

    node1->AddTransition(true, node2);
    node1->AddTransition(false, node3);

    cfg->AddProcCfg("main", node1);

    pkb_write_facade_->AddCfg(cfg);

    REQUIRE(pkb_read_facade_->HasNextRelationship() == true);
    REQUIRE(pkb_read_facade_->IsNext("1", "2") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("2", "5") == true);
    REQUIRE(pkb_read_facade_->HasNext("1") == true);
    REQUIRE(pkb_read_facade_->HasNext("2") == true);
    REQUIRE(pkb_read_facade_->HasNext("3") == true);
    REQUIRE(pkb_read_facade_->HasNext("5") == true);
    REQUIRE_FALSE(pkb_read_facade_->HasNext("4") == true);
    REQUIRE_FALSE(pkb_read_facade_->HasNext("6") == true);

    REQUIRE(pkb_read_facade_->GetNext("1", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("2")});
//    REQUIRE(pkb_read_facade_->GetNext("2", READ) == std::unordered_set
//        <PkbTypes::STATEMENT_NUMBER>{("3")});
    REQUIRE(pkb_read_facade_->GetNext("3", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("4")});
    REQUIRE(pkb_read_facade_->GetNext("5", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>{("6")});
//    REQUIRE(pkb_read_facade_->GetNext("2", READ) == std::unordered_set
//        <PkbTypes::STATEMENT_NUMBER>{("5")});
    REQUIRE(pkb_read_facade_->GetNextBy("2", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>({"1"}));
    REQUIRE(pkb_read_facade_->GetNextBy("4", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>({"3"}));
    REQUIRE(pkb_read_facade_->GetNextBy("6", READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>({"5"}));

    REQUIRE(pkb_read_facade_->HasNextBy("2") == true);
    REQUIRE(pkb_read_facade_->GetNextPairs(READ, READ) == std::unordered_set<std::pair
        <PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>({
          std::make_pair("1","2"), std::make_pair("2","3"),
          std::make_pair("3","4"), std::make_pair("5","6"),
          std::make_pair("2","5"),
          }));

    REQUIRE(pkb_read_facade_->GetNextFirst(READ) == std::unordered_set
        <PkbTypes::STATEMENT_NUMBER>({"1","2","3","5"}));
    REQUIRE(pkb_read_facade_->GetNextSecond(READ) == std::unordered_set<PkbTypes::STATEMENT_NUMBER>({
      "2","3","4","5","6"
    }));

  }
}

