#include <catch.hpp>
#include "PKB/Stores/CfgStore.h"
#include "core/cfg_model/Cfg.h"

TEST_CASE("Test CfgStore AddCfg and GetCfg") {
  typedef std::shared_ptr<Cfg> CfgPtr;

  SECTION("Test GetCfg() with empty CfgStore") {
    CfgStore cfg_store;
    REQUIRE(cfg_store.GetCfgCount() == 0);
  }

  SECTION("Test AddCfg with Empty Cfg") {
    CfgStore cfg_store;
    CfgPtr cfg = std::make_shared<Cfg>();
    cfg_store.AddCfg(cfg);
    REQUIRE(cfg_store.GetCfgCount() == 1);
  }
}

TEST_CASE("Test CfgStore GetCfgNodeFromProcedure") {
  typedef std::shared_ptr<Cfg> CfgPtr;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;

  SECTION("Test GetCfgNodeFromProcedure with empty CfgStore") {
    CfgStore cfg_store;
    CfgPtr cfg = std::make_shared<Cfg>();
    cfg_store.AddCfg(cfg);

    REQUIRE(cfg_store.GetCfgNodeFromProcedure("main") == nullptr);
  }

  SECTION("Test GetCfgNodeFromProcedure Method with Single Procedure") {
    CfgStore cfg_store;
    CfgPtr cfg = std::make_shared<Cfg>();

    CfgNodePtr root_node = std::make_shared<CfgNode>();
    root_node->AddStmt(1);
    cfg->AddProcCfg("main", root_node);

    cfg_store.AddCfg(cfg);

    CfgNodePtr result_node = cfg_store.GetCfgNodeFromProcedure("main");

    REQUIRE(result_node == root_node);
  }

  SECTION("Test GetCfgNodeFromProcedure Method with Multiple Procedures") {
    CfgStore cfg_store;
    CfgPtr cfg1 = std::make_shared<Cfg>();

    CfgNodePtr root_node_1 = std::make_shared<CfgNode>();
    root_node_1->AddStmt(1);
    cfg1->AddProcCfg("main", root_node_1);

    CfgNodePtr root_node_2 = std::make_shared<CfgNode>();
    root_node_2->AddStmt(2);
    cfg1->AddProcCfg("foo", root_node_2);

    cfg_store.AddCfg(cfg1);

    CfgNodePtr result_node_1 = cfg_store.GetCfgNodeFromProcedure("main");
    CfgNodePtr result_node_2 = cfg_store.GetCfgNodeFromProcedure("foo");

    REQUIRE(result_node_1 == root_node_1);
    REQUIRE(result_node_2 == root_node_2);
  }

  SECTION("Test GetCfgNodeFromProcedure with multiple procedures in CfgStore") {
    CfgStore cfg_store;
    CfgPtr cfg1 = std::make_shared<Cfg>();

    CfgNodePtr node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg1->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg1->AddStmtCfg(2, node1);

    CfgNodePtr node2 = std::make_shared<CfgNode>();
    node2->AddStmt(3);
    cfg1->AddStmtCfg(3, node2);
    node2->AddStmt(4);
    cfg1->AddStmtCfg(4, node2);

    node1->AddTransition(true, node2);

    CfgNodePtr node3 = std::make_shared<CfgNode>();
    node3->AddStmt(5);
    cfg1->AddStmtCfg(5, node3);
    node3->AddStmt(6);
    cfg1->AddStmtCfg(6, node3);

    CfgNodePtr node4 = std::make_shared<CfgNode>();
    node4->AddStmt(7);
    cfg1->AddStmtCfg(7, node4);
    node4->AddStmt(8);
    cfg1->AddStmtCfg(8, node4);

    node3->AddTransition(true, node4);

    cfg1->AddProcCfg("main", node1);
    cfg1->AddProcCfg("proc1", node3);
    cfg_store.AddCfg(cfg1);

    REQUIRE(cfg_store.GetCfgNodeFromProcedure("main") == node1);
    REQUIRE(cfg_store.GetCfgNodeFromProcedure("proc1") == node3);
    REQUIRE(cfg_store.GetCfgCount() == 1);
    REQUIRE(cfg_store.GetCfgNodeFromProcedure("nonexistent_proc") == nullptr);
  }
}

TEST_CASE("Test CfgStore GetCfgNodeFromStatementNumber") {
  typedef std::shared_ptr<Cfg> CfgPtr;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;

  SECTION("Test GetCfgNodeFromStatementNumber method with Single Statement") {
    CfgStore cfg_store;
    CfgPtr cfg = std::make_shared<Cfg>();

    CfgNodePtr node = std::make_shared<CfgNode>();
    node->AddStmt(1);
    cfg->AddStmtCfg(1, node);

    cfg_store.AddCfg(cfg);

    CfgNodePtr result_node = cfg_store.GetCfgNodeFromStatementNumber("1");

    REQUIRE(result_node == node);
  }

  SECTION("Test GetCfgNodeFromStatementNumber method with Multiple Statements") {
    CfgStore cfg_store;
    CfgPtr cfg = std::make_shared<Cfg>();

    CfgNodePtr node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);

    CfgNodePtr node2 = std::make_shared<CfgNode>();
    node2->AddStmt(2);
    cfg->AddStmtCfg(2, node2);

    CfgNodePtr node3 = std::make_shared<CfgNode>();
    node3->AddStmt(3);
    cfg->AddStmtCfg(3, node3);

    cfg_store.AddCfg(cfg);

    CfgNodePtr result_node1 = cfg_store.GetCfgNodeFromStatementNumber("1");
    CfgNodePtr result_node2 = cfg_store.GetCfgNodeFromStatementNumber("2");
    CfgNodePtr result_node3 = cfg_store.GetCfgNodeFromStatementNumber("3");

    REQUIRE(result_node1 == node1);
    REQUIRE(result_node2 == node2);
    REQUIRE(result_node3 == node3);
  }

  SECTION("Test AddCfg with Cfg with One Procedure and Multiple Nodes") {
    CfgStore cfg_store;
    CfgPtr cfg = std::make_shared<Cfg>();

    CfgNodePtr node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg->AddStmtCfg(2, node1);

    CfgNodePtr node2 = std::make_shared<CfgNode>();
    node2->AddStmt(3);
    cfg->AddStmtCfg(3, node2);
    node2->AddStmt(4);
    cfg->AddStmtCfg(4, node2);

    CfgNodePtr node3 = std::make_shared<CfgNode>();
    node3->AddStmt(5);
    cfg->AddStmtCfg(5, node3);
    node3->AddStmt(6);
    cfg->AddStmtCfg(6, node3);

    node1->AddTransition(true, node2);
    node2->AddTransition(true, node3);

    cfg->AddProcCfg("main", node1);
    cfg_store.AddCfg(cfg);

    REQUIRE(cfg_store.GetCfgCount() == 1);

    CfgNodePtr result_node1 = cfg_store.GetCfgNodeFromStatementNumber("1");
    CfgNodePtr result_node2 = cfg_store.GetCfgNodeFromStatementNumber("2");
    CfgNodePtr result_node3 = cfg_store.GetCfgNodeFromStatementNumber("3");
    CfgNodePtr result_node4 = cfg_store.GetCfgNodeFromStatementNumber("4");
    CfgNodePtr result_node5 = cfg_store.GetCfgNodeFromStatementNumber("5");
    CfgNodePtr result_node6 = cfg_store.GetCfgNodeFromStatementNumber("6");

    REQUIRE(result_node1 == node1);
    REQUIRE(result_node2 == node1);
    REQUIRE(result_node3 == node2);
    REQUIRE(result_node4 == node2);
    REQUIRE(result_node5 == node3);
    REQUIRE(result_node6 == node3);
  }
}


