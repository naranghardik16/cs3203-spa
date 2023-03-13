#include <string>
#include <utility>

#include "CFGStore.h"

CFGStore::CFGStore() = default;

CFGStore::~CFGStore() = default;

void CFGStore::addCfg(std::shared_ptr<Cfg>& cfg) {
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


std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> CFGStore::getProcedureToCfgRootNodeMap() {
  std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> temp;
  auto proc_node_map = this->cfg_->GetCfgRootNodes();
  for (const auto& [key, value] : proc_node_map) {
    temp.insert(std::pair<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>>(key, value));
  }
  return temp;
}

int CFGStore::getCfgCount() const {
  if (!cfg_) {
    return 0;
  }
  return 1;
}

std::unordered_map<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<CfgNode>> CFGStore::getStatementNumberToCfgRootNodeMap() {
  std::unordered_map<PkbTypes::STATEMENT_NUMBER, std::shared_ptr<CfgNode>> temp;
  for (const auto& [key, value]: this->cfg_->GetStmtToCfg()) {
    temp[std::to_string(key)] = value;
  }
  return temp;
}

