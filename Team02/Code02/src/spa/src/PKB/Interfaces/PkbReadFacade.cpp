#include "PkbReadFacade.h"

#include <memory>
#include "PKB/PKB.h"

PkbReadFacade::PkbReadFacade(PKB& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() {}

std::unordered_set<std::string> PkbReadFacade::GetVariables() {
  return this->pkb.entity_store_->getVariables();
}

std::unordered_set<std::string> PkbReadFacade::GetConstants() {
  return this->pkb.entity_store_->getConstants();
}

std::unordered_set<std::string> PkbReadFacade::GetProcedures() {
  return this->pkb.entity_store_->getProcedures();
}

std::unordered_set<std::string> PkbReadFacade::GetStatements() {
  return this->pkb.statement_store_->getAllStatements();
}

std::unordered_set<std::string> PkbReadFacade::GetReadStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::READ);
}

std::unordered_set<std::string> PkbReadFacade::GetPrintStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::PRINT);
}

std::unordered_set<std::string> PkbReadFacade::GetCallStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::CALL);
}

std::unordered_set<std::string> PkbReadFacade::GetWhileStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::WHILE);
}
std::unordered_set<std::string> PkbReadFacade::GetIfStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::IF);
}

std::unordered_set<std::string> PkbReadFacade::GetAssignStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::ASSIGN);
}

//!Ignore the rest below for the demo
std::vector<std::vector<std::string>> PkbReadFacade::GetVariablesModifiedByStatement(std::string stmt_num) {
  std::vector<std::vector<std::string>> result = {{"v"}, {"v1"}};
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetModifiesStatementVariablePairs() {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetModifiesProcedureVariablePairs() {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetVariablesModifiedByProcedure(std::string proc_name) {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetStatementsModifiesVariable(std::string var_name) {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  std::vector<std::vector<std::string>> result;
  return result;
}
