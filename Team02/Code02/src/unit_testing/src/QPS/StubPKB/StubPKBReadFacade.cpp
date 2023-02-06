//! Preserving the stub written previously
/*
#pragma once
#include "StubPKBReadFacade.h"

#include <memory>
#include "PKB/PKB.h"


StubPkbReadFacade::~StubPkbReadFacade() {}

std::unordered_set<std::string> StubPkbReadFacade::GetVariables() {
  std::unordered_set<std::string> var_set({"a", "b", "c"});
  return var_set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetConstants() {
  std::unordered_set<std::string> set({"22", "23", "24"});
  return set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetProcedures() {
  std::unordered_set<std::string> set({"eval", "parse", "validate"});
  return set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetStatements() {
  std::unordered_set<std::string> statement_set({"1", "2", "3"});
  return statement_set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetReadStatements() {
  std::unordered_set<std::string> read_set({"4", "5", "6"});
  return read_set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetPrintStatements() {
  std::unordered_set<std::string> print_set({"6", "7", "8"});
  return print_set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetCallStatements() {
  std::unordered_set<std::string> call_set({"9", "10", "11"});
  return call_set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetWhileStatements() {
  std::unordered_set<std::string> while_set({"12", "13", "14"});
  return while_set;
}
std::unordered_set<std::string> StubPkbReadFacade::GetIfStatements() {
  std::unordered_set<std::string> if_set({"15", "16", "18"});
  return if_set;
}

std::unordered_set<std::string> StubPkbReadFacade::GetAssignStatements() {
  std::unordered_set<std::string> assign_set({"19", "20", "21"});
  return assign_set;
}


std::vector<std::vector<std::string>> StubPkbReadFacade::GetVariablesModifiedByStatement(std::string stmt_num) {
  std::vector<std::vector<std::string>> result = {{"v"}, {"v1"}};
  return result;
}

//!Ignore the rest below for the demo

std::vector<std::vector<std::string>> StubPkbReadFacade::GetModifiesStatementVariablePairs() {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> StubPkbReadFacade::GetModifiesProcedureVariablePairs() {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> StubPkbReadFacade::GetVariablesModifiedByProcedure(std::string proc_name) {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> StubPkbReadFacade::GetStatementsModifiesVariable(std::string var_name) {
  std::vector<std::vector<std::string>> result;
  return result;
}

std::vector<std::vector<std::string>> StubPkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  std::vector<std::vector<std::string>> result;
  return result;
}
*/