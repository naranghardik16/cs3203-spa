#include "CfgStore.h"

CfgStore::CfgStore() = default;

CfgStore::~CfgStore() = default;

void CfgStore::AddCfg(const CfgPtr& cfg) {
  this->cfg_ = cfg;
}

CfgStore::CfgNodePtr CfgStore::GetCfgNodeFromProcedure(const Procedure& procedure) {
  return this->cfg_->GetCfgRootNodes()[procedure];
}

CfgStore::CfgNodePtr CfgStore::GetCfgNodeFromStatementNumber(const StatementNumber& statement_number) {
  return this->cfg_->GetStmtToCfg()[std::stoi(statement_number)];
}

CfgStore::CfgPtr CfgStore::GetCfg() const {
  return cfg_;
}

CfgStore::ProcedureToCfgNodeMap CfgStore::GetProcedureToCfgNodeMap() {
  ProcedureToCfgNodeMap result;
  auto proc_node_map = this->cfg_->GetCfgRootNodes();
  for (const auto& [key, value] : proc_node_map) {
    result.insert(std::make_pair(key, value));
  }
  return result;
}

int CfgStore::GetCfgCount() const {
  if (!cfg_) return 0;
  return 1;
}

CfgStore::StatementNumberToCfgNodeMap
CfgStore::GetStatementNumberToCfgNodeMap() {
  ProcedureToCfgNodeMap result;
  for (const auto& [key, value]: this->cfg_->GetStmtToCfg()) {
    result[std::to_string(key)] = value;
  }
  return result;
}

