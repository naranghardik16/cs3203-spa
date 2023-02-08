//! Preserving the stub written previously
/*
#pragma once
#include "StubPKBReadFacade.h"

#include <memory>
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

StubPkbReadFacade::~StubPkbReadFacade() {}

SingleConstraintSet StubPkbReadFacade::GetVariables() {
  SingleConstraintSet var_set({"a", "b", "c"});
  return var_set;
}

SingleConstraintSet StubPkbReadFacade::GetConstants() {
  SingleConstraintSet set({"22", "23", "24"});
  return set;
}

SingleConstraintSet StubPkbReadFacade::GetProcedures() {
  SingleConstraintSet set({"eval", "parse", "validate"});
  return set;
}

SingleConstraint StubPkbReadFacade::GetStatements() {
  SingleConstraintSet statement_set({"1", "2", "3"});
  return statement_set;
}

SingleConstraintSet StubPkbReadFacade::GetReadStatements() {
  SingleConstraintSet read_set({"4", "5", "6"});
  return read_set;
}

SingleConstraintSet StubPkbReadFacade::GetPrintStatements() {
  SingleConstraintSet print_set({"6", "7", "8"});
  return print_set;
}

SingleConstraintSet StubPkbReadFacade::GetCallStatements() {
  SingleConstraintSet call_set({"9", "10", "11"});
  return call_set;
}

SingleConstraintSet StubPkbReadFacade::GetWhileStatements() {
  SingleConstraintSet while_set({"12", "13", "14"});
  return while_set;
}

SingleConstraintSet StubPkbReadFacade::GetIfStatements() {
  SingleConstraintSet if_set({"15", "16", "18"});
  return if_set;
}

SingleConstraintSet StubPkbReadFacade::GetAssignStatements() {
  SingleConstraintSet assign_set({"19", "20", "21"});
  return assign_set;
}


SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByStatement(std::string stmt_num) {
  SingleConstraintSet result = {{"v"}, {"v1"}};
  return result;
}

//!Ignore the rest below for the demo

PairConstraintSet StubPkbReadFacade::GetModifiesStatementVariablePairs() {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet StubPkbReadFacade::GetModifiesProcedureVariablePairs() {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByProcedure(std::string proc_name) {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet StubPkbReadFacade::GetStatementsModifiesVariable(std::string var_name) {
  SingleConstraintSet result;
  return result;
}

SingleConstraintSet StubPkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  SingleConstraintSet result;
  return result;
}
*/