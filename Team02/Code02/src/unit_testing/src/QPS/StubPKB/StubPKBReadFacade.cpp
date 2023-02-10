//! Preserving the stub written previously

#pragma once
#include "StubPKBReadFacade.h"

#include <memory>
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

StubPkbReadFacade::StubPkbReadFacade(PKB &pkb): PkbReadFacade(pkb) {}

StubPkbReadFacade::~StubPkbReadFacade() {}

PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariables() {
  return PkbReadFacade::GetVariables();
}

PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetConstants() {
  return PkbReadFacade::GetConstants();
}

PkbCommunicationTypes::PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProcedures() {
  return PkbReadFacade::GetProcedures();
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatements() {
  return PkbReadFacade::GetStatements();
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetReadStatements() {
  return PkbReadFacade::GetReadStatements();
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetPrintStatements() {
  return PkbReadFacade::GetPrintStatements();
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetCallStatements() {
  return PkbReadFacade::GetCallStatements();
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetWhileStatements() {
  return PkbReadFacade::GetWhileStatements();
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetIfStatements() {
  return PkbReadFacade::GetIfStatements();
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetAssignStatements() {
  return PkbReadFacade::GetAssignStatements();
}


//! Modifies Statement API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  if (statement_type == StatementType::PRINT) {
    return {std::make_pair("1", "x")};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {std::make_pair("2", "a")};
  }
  return {};
}


PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  return PkbReadFacade::GetVariablesModifiedByProcedure(statement_number);
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  if (var_name == "\"x\"" && statement_type == StatementType::PRINT) {
    return {"1"};
  }
  if (var_name == "\"a\"" && statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsThatModify(StatementType stmt_type) {
  if (stmt_type == StatementType::PRINT) {
    return {"1"};
  }
  if (stmt_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

bool StubPkbReadFacade::HasModifiesStatementRelationship(std::string stmt_num, std::string var_name) {
  if (stmt_num == "1" && var_name == "\"x\"") {
    return true;
  }
  if (stmt_num == "2" && var_name == "\"a\"") {
    return true;
  }
  return false;
}


//! Modifies Procedure API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetModifiesProcedureVariablePairs() {
  return {std::make_pair("execute", "x"), std::make_pair("execute", "a")};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetVariablesModifiedByProcedure(std::string procedure_name) {
  if (procedure_name == "\"execute\"") {
    return {"x","a"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  if (var_name == "\"x\"") {
    return {"execute"};
  }
  if (var_name == "\"a\"") {
    return {"execute"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetProceduresThatModify() {
  return {"execute"};
}

bool StubPkbReadFacade::HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name) {
  if (procedure_name == "\"execute\"" && var_name == "\"x\"") {
    return true;
  }
  if (procedure_name == "\"execute\"" && var_name == "\"a\"") {
    return true;
  }
  return false;
}

//! Follows API
PkbCommunicationTypes::PairConstraintSet StubPkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  if (statement_type == StatementType::PRINT && statement_type_follower == StatementType::ASSIGN) {
    return {std::make_pair("1", "2")};
  }
  if (statement_type == StatementType::PRINT && statement_type_follower == StatementType::CALL) {
    return {std::make_pair("1", "3")};
  }
  return {};
}


PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsFollowedBy(std::string statement_num, StatementType statement_type) {
  if (statement_num == "3" && statement_type == StatementType::ALL) {
    return {"1","2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsFollowing(std::string statement_num, StatementType statement_type) {
  if (statement_num == "1" && statement_type == StatementType::ALL) {
    return {"2","3"};
  }
  if (statement_num == "1" && statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementsWithFollowers(StatementType statement_type) {
  if (statement_type == StatementType::PRINT) {
    return {"1"};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet StubPkbReadFacade::GetStatementThatAreFollowers(StatementType statement_type) {
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  if (statement_type == StatementType::READ) {
    return {"3"};
  }
  return {};
}


bool StubPkbReadFacade::HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) {
  if (statement_num == "1" && statement_num_follower == "2") {
    return true;
  }
  if (statement_num == "1" && statement_num_follower == "3") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return true;
}

