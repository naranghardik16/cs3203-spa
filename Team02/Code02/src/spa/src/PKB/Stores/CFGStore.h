#pragma once

#include <memory>
#include "core/cfg_model/Cfg.h"
#include "PKB/Types/PkbTypes.h"

class CFGStore {
 public:
  CFGStore();

  ~CFGStore();

  void addCfg(std::shared_ptr<Cfg> cfg);

  std::shared_ptr<CfgNode> getCfgNodeFromProcedure(PkbTypes::PROCEDURE procedure);

  std::shared_ptr<CfgNode> getCfgNodeFromStatementNumber(PkbTypes::STATEMENT_NUMBER statement_number);

 private:
  std::shared_ptr<Cfg> cfg_;
};

