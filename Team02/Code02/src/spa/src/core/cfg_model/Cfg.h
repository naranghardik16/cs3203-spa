#pragma once

#include <unordered_map>
#include <string>

#include "CfgNode.h"
#include "General/SpaException/SemanticErrorException.h"

class Cfg {
 public:
  typedef std::unordered_map<std::string, std::shared_ptr<CfgNode>>
      ProcToCfgNodeMap;
  typedef std::unordered_map<int, std::shared_ptr<CfgNode>> StmtNoToNodeMap;
  void AddProcCfg(const std::string &proc_name,
                  std::shared_ptr<CfgNode> node);
  void AddStmtCfg(int stmt_number, std::shared_ptr<CfgNode> node);

  ProcToCfgNodeMap GetCfgRootNodes();
  StmtNoToNodeMap GetStmtToCfg();
 private:
  ProcToCfgNodeMap cfg_root_nodes_;
  StmtNoToNodeMap stmt_to_cfg_;
};