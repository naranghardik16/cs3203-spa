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
  std::unordered_set<std::string> statement_set({"1", "2", "3"});
  return statement_set;
}

std::unordered_set<std::string> PkbReadFacade::GetReadStatements() {
  std::unordered_set<std::string> read_set({"4", "5", "6"});
  return read_set;
}

std::unordered_set<std::string> PkbReadFacade::GetPrintStatements() {
  std::unordered_set<std::string> print_set({"6", "7", "8"});
  return print_set;
}

std::unordered_set<std::string> PkbReadFacade::GetCallStatements() {
  std::unordered_set<std::string> call_set({"9", "10", "11"});
  return call_set;
}

std::unordered_set<std::string> PkbReadFacade::GetWhileStatements() {
  std::unordered_set<std::string> while_set({"12", "13", "14"});
  return while_set;
}
std::unordered_set<std::string> PkbReadFacade::GetIfStatements() {
  std::unordered_set<std::string> if_set({"15", "16", "18"});
  return if_set;
}

std::unordered_set<std::string> PkbReadFacade::GetAssignStatements() {
  std::unordered_set<std::string> assign_set({"19", "20", "21"});
  return assign_set;
}


std::vector<std::vector<std::string>> PkbReadFacade::GetVariablesModifiedByStatement(std::string stmt_num) {
  std::vector<std::vector<std::string>> result = {{"v"}, {"v1"}};
  return result;
}

//!Ignore the rest below for the demo

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
