#include <string>
#include <utility>

#include "CFGStore.h"

CFGStore::CFGStore() = default;

CFGStore::~CFGStore() = default;

void CFGStore::addCfg(std::shared_ptr<Cfg> cfg) {
  this->cfg_ = std::move(cfg);
}

std::shared_ptr<CfgNode> CFGStore::getCfgNodeFromProcedure(PkbTypes::PROCEDURE procedure) {
  return this->cfg_->GetCfgRootNodes()[procedure];
}

std::shared_ptr<CfgNode> CFGStore::getCfgNodeFromStatementNumber(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->cfg_->GetStmtToCfg()[std::stoi(statement_number)];
}

std::shared_ptr<Cfg> CFGStore::getCfg() const {
  return cfg_;
}

int CFGStore::getCfgCount() const {
  if (!cfg_) {
    return 0;
  }
  return 1;
}



