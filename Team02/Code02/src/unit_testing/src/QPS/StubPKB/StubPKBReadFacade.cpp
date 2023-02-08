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
  SingleConstraintSet set({"eval", "parse", "validate"});
  return set;
}

SingleConstraintSet StubPkbReadFacade::GetStatements() {
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

//! API for Modifies - Statement
SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByStatement(std::string stmt_num) {
  SingleConstraintSet result = {"x"};
  return result;
}

PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type) {
  PairConstraintSet result;
  return result;
}

SingleConstraintSet GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  SingleConstraintSet result = {"x"};
  return result;
}

SingleConstraintSet GetStatementsThatModify(StatementType stmt_type) {
  SingleConstraintSet result = {"x"};
  return result;
}

bool HasModifiesStatementRelationship(std::string stmt_num, std::string var_name) {
  return false;
}

//! API for Modifies - Procedure
SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name) {
  SingleConstraintSet result = {"x"};
  return result;
}

PairConstraintSet GetModifiesProcedureVariablePairs() {
  PairConstraintSet result;
  return result;
}

SingleConstraintSet GetProceduresModifiesVariable(std::string var_name) {
  SingleConstraintSet result = {"x"};
  return result;
}

SingleConstraintSet GetProceduresThatModify() {
  SingleConstraintSet result = {"x"};
  return result;
}

bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name) {
  return false;
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

