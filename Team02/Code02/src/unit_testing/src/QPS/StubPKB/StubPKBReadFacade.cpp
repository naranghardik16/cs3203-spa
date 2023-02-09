//! Preserving the stub written previously

#pragma once
#include "StubPKBReadFacade.h"

#include <memory>
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

StubPkbReadFacade::~StubPkbReadFacade() {}

SingleConstraintSet StubPkbReadFacade::GetVariables() {
  SingleConstraintSet var_set({"a", "b", "c", "x", "y"});
  return var_set;
}

SingleConstraintSet StubPkbReadFacade::GetConstants() {
  SingleConstraintSet set({"22", "23", "24"});
  return set;
}

SingleConstraintSet StubPkbReadFacade::GetProcedures() {
  SingleConstraintSet set({"execute", "anya"});
  return set;
}

SingleConstraintSet StubPkbReadFacade::GetStatements() {
  SingleConstraintSet statement_set({ "2", "3"});
  return statement_set;
}

SingleConstraintSet StubPkbReadFacade::GetReadStatements() {
  SingleConstraintSet read_set({"4", "5", "6"});
  return read_set;
}

SingleConstraintSet StubPkbReadFacade::GetPrintStatements() {
  SingleConstraintSet print_set({"1"});
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

//! API for Modifies - Statement
SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByStatement(std::string statement_num) {
  if (statement_num == "1") {
    return {"x"};
  }
  return {};
}

PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type) {
  if (statement_type == StatementType::PRINT) {
    return {std::make_pair("1", "x")};
  }
  return {};
}

SingleConstraintSet GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  if (var_name == "\"count\"" && statement_type == StatementType::PRINT) {
    return {};
  }
  return {};
}

SingleConstraintSet GetStatementsThatModify(StatementType stmt_type) {
  if (stmt_type == StatementType::PRINT) {
    return {"1"};
  }
  return {};
}

bool HasModifiesStatementRelationship(std::string stmt_num, std::string var_name) {
  if (stmt_num == "1" && var_name == "\"x\"") {
    return true;
  }
  return false;
}

//! API for Modifies - Procedure
SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name) {
  if (procedure_name == "\"anya\"") {
    return {};
  }
  return {"y"};
}

PairConstraintSet GetModifiesProcedureVariablePairs() {
  return {std::make_pair("execute", "y")};
}

SingleConstraintSet GetProceduresModifiesVariable(std::string var_name) {
  if (var_name == "\"y\"") {
    return {"execute"};
  }
  return {};
}

SingleConstraintSet GetProceduresThatModify() {
  return {"execute"};
}

bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name) {
  if (procedure_name == "\"anya\"" && var_name == "\"y\"") {
    return false;
  }
  return true;
}

//!API for Follows
PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  PairConstraintSet result;
  return result;
}

SingleConstraintSet GetStatementsFollowedBy(std::string statement_num, StatementType statement_type) {
  SingleConstraintSet result = {"x"};
  return result;
}

SingleConstraintSet GetStatementsFollowing(std::string statement_num, StatementType statement_type) {
  SingleConstraintSet result = {"x"};
  return result;
}

SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type) {
  SingleConstraintSet result = {"x"};
  return result;
}

SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type) {
  SingleConstraintSet result = {"x"};
  return result;
}

bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) {
  return false;
}

bool IsAnyFollowsRelationshipPresent() {
  return false;
}

