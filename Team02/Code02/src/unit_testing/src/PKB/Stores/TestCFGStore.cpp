#include <catch.hpp>
#include "PKB/Stores/CFGStore.h"
#include "core/cfg_model/Cfg.h"

TEST_CASE("Test CFGStore addCfg and getCfg") {
  SECTION("Test CFGStore methods") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
    cfg_store.addCfg(cfg);

    REQUIRE(cfg_store.getCfg() == cfg);
  }

  SECTION("Test addCfg with Empty Cfg") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
    cfg_store.addCfg(cfg);
    REQUIRE(cfg_store.getCfgCount() == 1);
  }

}

TEST_CASE("Test CFGStore getCfgNodeFromProcedure") {

  SECTION("Test getCfgNodeFromProcedure with empty CFGStore") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
    cfg_store.addCfg(cfg);

    // Assert that getCfgNodeFromProcedure returns nullptr for an empty CFGStore
    REQUIRE(cfg_store.getCfgNodeFromProcedure("main") == nullptr);
  }

  SECTION("Test getCfgNodeFromProcedure Method with Single Procedure") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    // Create a CFG with a single node for procedure "main"
    std::shared_ptr<CfgNode> root_node = std::make_shared<CfgNode>();
    root_node->AddStmt(1);
    cfg->AddProcCfg("main", root_node);

    cfg_store.addCfg(cfg);

    // Get the root node for procedure "main" from the CFGStore
    std::shared_ptr<CfgNode> result_node = cfg_store.getCfgNodeFromProcedure("main");

    // Ensure the root node returned from the CFGStore is the same as the one we added
    REQUIRE(result_node == root_node);
  }

  SECTION("Test getCfgNodeFromProcedure Method with Multiple Procedures") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg1 = std::make_shared<Cfg>();

    // Create a CFG with a single root node for procedure "main"
    std::shared_ptr<CfgNode> root_node_1 = std::make_shared<CfgNode>();
    root_node_1->AddStmt(1);
    cfg1->AddProcCfg("main", root_node_1);

    // Create a CFG with a single root node for procedure "foo"
    std::shared_ptr<CfgNode> root_node_2 = std::make_shared<CfgNode>();
    root_node_2->AddStmt(2);
    cfg1->AddProcCfg("foo", root_node_2);

    cfg_store.addCfg(cfg1);

    // Get the root nodes for "main" and "foo" procedures from the CFGStore
    std::shared_ptr<CfgNode> result_node_1 = cfg_store.getCfgNodeFromProcedure("main");
    std::shared_ptr<CfgNode> result_node_2 = cfg_store.getCfgNodeFromProcedure("foo");

    // Ensure the root nodes returned from the CFGStore are the same as the ones we added
    REQUIRE(result_node_1 == root_node_1);
    REQUIRE(result_node_2 == root_node_2);
  }

  SECTION("Test getCfgNodeFromProcedure with multiple procedures in CFGStore") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg1 = std::make_shared<Cfg>();

    std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg1->AddStmtCfg(1, node1);
    node1->AddStmt(2);
    cfg1->AddStmtCfg(2, node1);

    std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
    node2->AddStmt(3);
    cfg1->AddStmtCfg(3, node2);
    node2->AddStmt(4);
    cfg1->AddStmtCfg(4, node2);

    node1->AddTransition(true, node2);

    std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
    node3->AddStmt(5);
    cfg1->AddStmtCfg(5, node3);
    node3->AddStmt(6);
    cfg1->AddStmtCfg(6, node3);

    std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
    node4->AddStmt(7);
    cfg1->AddStmtCfg(7, node4);
    node4->AddStmt(8);
    cfg1->AddStmtCfg(8, node4);

    node3->AddTransition(true, node4);

    cfg1->AddProcCfg("main", node1);
    cfg1->AddProcCfg("proc1", node3);
    cfg_store.addCfg(cfg1);

    REQUIRE(cfg_store.getCfgNodeFromProcedure("main") == node1);
    REQUIRE(cfg_store.getCfgNodeFromProcedure("proc1") == node3);
    REQUIRE(cfg_store.getCfgCount() == 1);
    REQUIRE(cfg_store.getCfgNodeFromProcedure("nonexistent_proc") == nullptr);
  }

}

TEST_CASE("Test CFGStore getCfgNodeFromStatementNumber") {
  SECTION("Test getCfgNodeFromStatementNumber method with Single Statement") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    // Create a CFG with a single node for statement 1
    std::shared_ptr<CfgNode> node = std::make_shared<CfgNode>();
    node->AddStmt(1);
    cfg->AddStmtCfg(1, node);

    cfg_store.addCfg(cfg);

    // Get the node for statement 1 from the CFGStore
    std::shared_ptr<CfgNode> result_node = cfg_store.getCfgNodeFromStatementNumber("1");

    // Ensure the node returned from the CFGStore is the same as the one we added
    REQUIRE(result_node == node);
  }

  SECTION("Test getCfgNodeFromStatementNumber method with Multiple Statements") {
    CFGStore cfg_store;
    std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();

    // Create a CFG with three nodes for statements 1, 2, and 3
    std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
    node1->AddStmt(1);
    cfg->AddStmtCfg(1, node1);

    std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
    node2->AddStmt(2);
    cfg->AddStmtCfg(2, node2);

    std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
    node3->AddStmt(3);
    cfg->AddStmtCfg(3, node3);

    cfg_store.addCfg(cfg);

    // Get the nodes for statements 1, 2, and 3 from the CFGStore
    std::shared_ptr<CfgNode> result_node1 = cfg_store.getCfgNodeFromStatementNumber("1");
    std::shared_ptr<CfgNode> result_node2 = cfg_store.getCfgNodeFromStatementNumber("2");
    std::shared_ptr<CfgNode> result_node3 = cfg_store.getCfgNodeFromStatementNumber("3");

    // Ensure the nodes returned from the CFGStore are the same as the ones we added
    REQUIRE(result_node1 == node1);
    REQUIRE(result_node2 == node2);
    REQUIRE(result_node3 == node3);
  }

  SECTION("Test addCfg with Cfg with One Procedure and Multiple Nodes") {
    CFGStore cfg_store;
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

    node1->AddTransition(true, node2);
    node2->AddTransition(true, node3);

    cfg->AddProcCfg("main", node1);
    cfg_store.addCfg(cfg);

    REQUIRE(cfg_store.getCfgCount() == 1);

    std::shared_ptr<CfgNode> result_node1 = cfg_store.getCfgNodeFromStatementNumber("1");
    std::shared_ptr<CfgNode> result_node2 = cfg_store.getCfgNodeFromStatementNumber("2");
    std::shared_ptr<CfgNode> result_node3 = cfg_store.getCfgNodeFromStatementNumber("3");
    std::shared_ptr<CfgNode> result_node4 = cfg_store.getCfgNodeFromStatementNumber("4");
    std::shared_ptr<CfgNode> result_node5 = cfg_store.getCfgNodeFromStatementNumber("5");
    std::shared_ptr<CfgNode> result_node6 = cfg_store.getCfgNodeFromStatementNumber("6");

    REQUIRE(result_node1 == node1);
    REQUIRE(result_node2 == node1);
    REQUIRE(result_node3 == node2);
    REQUIRE(result_node4 == node2);
    REQUIRE(result_node5 == node3);
    REQUIRE(result_node6 == node3);
  }

}


