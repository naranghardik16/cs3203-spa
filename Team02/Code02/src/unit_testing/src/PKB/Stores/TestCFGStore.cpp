#include <catch.hpp>
#include "PKB/Stores/CFGStore.h"
#include "core/cfg_model/Cfg.h"

TEST_CASE("Test CFGStore addCfg and getCfg") {
  CFGStore cfg_store;
  std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
  cfg_store.addCfg(cfg);

  REQUIRE(cfg_store.getCfg() == cfg);
}

TEST_CASE("Test CFGStore getCfgNodeFromProcedure") {
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

TEST_CASE("Test CFGStore getCfgNodeFromStatementNumber") {
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
