#pragma once

#include <unordered_map>
#include <string>

#include "CfgNode.h"
#include "General/SpaException/SemanticErrorException.h"

class Cfg {
 public:
  void AddProcCfg(const std::string &proc_name,
                  std::shared_ptr<CFGNode> node);
  void AddStmtCfg(int stmt_number, std::shared_ptr<CFGNode> node);
 private:
  std::unordered_map<std::string, std::shared_ptr<CFGNode>> cfg_root_nodes_;
  std::unordered_map<int, std::shared_ptr<CFGNode>> stmt_to_cfg_;
};