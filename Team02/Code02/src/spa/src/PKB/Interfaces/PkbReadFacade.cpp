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

PairConstraintSet PkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  PairConstraintSet result;
  return result;
}

//TODO to put back the proper PKB implementation after type of return value is change to set
std::unordered_set<std::string> PkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  //return this->pkb.modifies_store_->convert(this->pkb.modifies_store_->retrieveAllVariablesModifiedByAStatement(statement_number));
  std::unordered_set<std::string> result = {"x"};
  return result;
}

std::unordered_set<std::string> PkbReadFacade::GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  std::unordered_set<std::string> result;
  return result;
}

std::unordered_set<std::string> PkbReadFacade::GetModifiers(StatementType stmt_type) {
  std::unordered_set<std::string> result;
  return result;
}

bool PkbReadFacade::IsModifiesStatement(std::string stmt_num, std::string var_name) {
  return true;
}