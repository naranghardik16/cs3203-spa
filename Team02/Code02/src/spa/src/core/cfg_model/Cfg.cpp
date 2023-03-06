#include "Cfg.h"

void Cfg::AddProcCfg(const std::string &proc_name,
                     std::shared_ptr<CFGNode> node) {
  if (cfg_root_nodes_.count(proc_name) > 0) {
    throw SemanticErrorException(
        "CFG for the given proc name already exists");
  }

  cfg_root_nodes_[proc_name] = std::move(node);
}

void Cfg::AddStmtCfg(int stmt_number, std::shared_ptr<CFGNode> node) {
  if (stmt_to_cfg_.count(stmt_number) > 0) {
    throw SemanticErrorException(
        "stmt number " + std::to_string(stmt_number)
            + " is already assigned a node");
  }

  stmt_to_cfg_[stmt_number] = std::move(node);
}