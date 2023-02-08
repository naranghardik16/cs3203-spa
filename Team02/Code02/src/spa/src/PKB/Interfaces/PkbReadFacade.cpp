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

std::vector<std::vector<std::string>> PkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  return this->pkb.modifies_store_->convert(this->pkb.modifies_store_->retrieveAllVariablesModifiedByAStatement(statement_number));
}



// TODO: All these functions for demo
std::vector<std::vector<std::string>> PkbReadFacade::GetModifiesStatementVariablePairs(std::string statement_type) {
  std::vector<std::vector<std::string>> result;
  return result;
}

/*
 * If is call is true then return the procedures that are called in call statements only
 */
std::vector<std::vector<std::string>> PkbReadFacade::GetModifiesProcedureVariablePairs(bool is_call) {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetVariablesModifiedByProcedure(std::string proc_name) {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetStatementsModifiesVariable(std::string var_name, std::string statement_type) {
  std::vector<std::vector<std::string>> result;
  return result;
}

/*
 * If is call is true then return the procedures that are called in call statements only
 */
std::vector<std::vector<std::string>> PkbReadFacade::GetProceduresModifiesVariable(std::string var_name, bool is_call) {
  std::vector<std::vector<std::string>> result;
  return result;
}

bool PkbReadFacade::IsModifiesStatement(std::string stmt_num, std::string ident) {
  return false;
}

bool PkbReadFacade::IsModifiesProcedure(std::string proc_name, std::string ident) {
  return true;
}



std::vector<std::vector<std::string>> PkbReadFacade::GetFollowPairs(std::string statement_type, std::string statement_type_followee) {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> PkbReadFacade::GetStatementsFollowedBy(std::string stmt_reference, std::string statement_type) {
  std::vector<std::vector<std::string>> result;
  return result;
}
std::vector<std::vector<std::string>> PkbReadFacade::GetStatementsFollowing(std::string stmt_reference, std::string statement_type) {
  std::vector<std::vector<std::string>> result;
  return result;
}

bool PkbReadFacade::IsFollows(std::string stmt_reference, std::string stmt_reference_followee) {
  return true;
}