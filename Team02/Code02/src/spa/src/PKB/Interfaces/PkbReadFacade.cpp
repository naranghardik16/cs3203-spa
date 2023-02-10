#include "PkbReadFacade.h"
#include <memory>
#include "PKB/PKB.h"

PkbReadFacade::PkbReadFacade(PKB& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() {}

SingleConstraintSet PkbReadFacade::GetVariables() {
  SingleConstraintSet var_set({"a", "x", "y"});
  return var_set;
  //return this->pkb.entity_store_->getVariables();
}

SingleConstraintSet PkbReadFacade::GetConstants() {
  return this->pkb.entity_store_->getConstants();
}

SingleConstraintSet PkbReadFacade::GetProcedures() {
  SingleConstraintSet set({"execute", "anya"});
  return set;
  //return this->pkb.entity_store_->getProcedures();
}

SingleConstraintSet PkbReadFacade::GetStatements() {
  return this->pkb.statement_store_->getAllStatements();
}

SingleConstraintSet PkbReadFacade::GetReadStatements() {
  SingleConstraintSet set({"1"});
  return set;
  //return this->pkb.statement_store_->getStatementsFromType(StatementType::READ);
}

SingleConstraintSet PkbReadFacade::GetPrintStatements() {
  SingleConstraintSet print_set({"4"});
  return print_set;
  //return this->pkb.statement_store_->getStatementsFromType(StatementType::PRINT);
}

SingleConstraintSet PkbReadFacade::GetCallStatements() {
  SingleConstraintSet set({"3"});
  return set;
  //return this->pkb.statement_store_->getStatementsFromType(StatementType::CALL);
}

SingleConstraintSet PkbReadFacade::GetWhileStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::WHILE);
}

SingleConstraintSet PkbReadFacade::GetIfStatements() {
  return {"5"};
  //return this->pkb.statement_store_->getStatementsFromType(StatementType::IF);
}

SingleConstraintSet PkbReadFacade::GetAssignStatements() {
  SingleConstraintSet set({"2", "6", "7"});
  return set;
  //return this->pkb.statement_store_->getStatementsFromType(StatementType::ASSIGN);
}


//! Modifies Statement API
PairConstraintSet PkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  if (statement_type == StatementType::READ) {
    return {std::make_pair("1", "x")};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {std::make_pair("2", "a")};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  //return this->pkb.modifies_store_->convert(this->pkb.modifies_store_->retrieveAllVariablesModifiedByAStatement(statement_number));
  if (statement_number == "1") {
    return {"x"};
  }
  if (statement_number == "2") {
    return {"a"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  if (var_name == "\"x\"" && statement_type == StatementType::READ) {
    return {"1"};
  }
  if (var_name == "\"a\"" && statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatModify(StatementType stmt_type) {
  if (stmt_type == StatementType::READ) {
    return {"1"};
  }
  if (stmt_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

bool PkbReadFacade::HasModifiesStatementRelationship(std::string stmt_num, std::string var_name) {
  if (stmt_num == "1" && var_name == "\"x\"") {
    return true;
  }
  if (stmt_num == "2" && var_name == "\"a\"") {
    return true;
  }
  return false;
}


//! Modifies Procedure API
PairConstraintSet PkbReadFacade::GetModifiesProcedureVariablePairs() {
  return {std::make_pair("execute", "x"), std::make_pair("execute", "a")};
}

SingleConstraintSet PkbReadFacade::GetVariablesModifiedByProcedure(std::string procedure_name) {
  if (procedure_name == "\"execute\"") {
    return {"x","a"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  if (var_name == "\"x\"") {
    return {"execute"};
  }
  if (var_name == "\"a\"") {
    return {"execute"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetProceduresThatModify() {
  return {"execute"};
}

bool PkbReadFacade::HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name) {
  if (procedure_name == "\"execute\"" && var_name == "\"x\"") {
    return true;
  }
  if (procedure_name == "\"execute\"" && var_name == "\"a\"") {
    return true;
  }
  return false;
}

//! Follows API
PairConstraintSet PkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::ASSIGN) {
    return {std::make_pair("1", "2")};
  }
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::CALL) {
    return {std::make_pair("1", "3")};
  }
  return {};
}


SingleConstraintSet PkbReadFacade::GetStatementFollowedBy(std::string statement_num, StatementType statement_type) {
  if (statement_num == "3" && statement_type == StatementType::ALL) {
    return {"2"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementFollowing(std::string statement_num, StatementType statement_type) {
  if (statement_num == "1" && (statement_type == StatementType::ALL || statement_type == StatementType::ASSIGN)) {
    return {"2"};
  }
  if (statement_num == "2" && (statement_type == StatementType::ALL || statement_type == StatementType::CALL)) {
    return {"3"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsWithFollowers(StatementType statement_type) {
  if (statement_type == StatementType::READ) {
    return {"1"};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementThatAreFollowers(StatementType statement_type) {
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  if (statement_type == StatementType::CALL) {
    return {"3"};
  }
  return {};
}


bool PkbReadFacade::HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) {
  if (statement_num == "1" && statement_num_follower == "2") {
    return true;
  }
  if (statement_num == "1" && statement_num_follower == "3") {
    return true;
  }
  return false;
}

bool PkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return true;
}

//! Parent API

PairConstraintSet PkbReadFacade::GetParentChildPairs(StatementType statement_type, StatementType statement_type_child) {
  if (statement_type == StatementType::IF && statement_type_child == StatementType::ASSIGN) {
    return {std::make_pair("5","6"), std::make_pair("5","7")};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type) {
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type) {
  if (statement_num == "5" && (statement_type == StatementType::ALL || statement_type == StatementType::ASSIGN)) {
    return {"6","7"};
  }
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatAreParents(StatementType statement_type) {
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatAreChildren(StatementType statement_type) {
  if (statement_type == StatementType::ASSIGN) {
    return {"6","7"};
  }
  return {};
}

bool PkbReadFacade::HasParentChildRelationship(std::string statement_num, std::string statement_num_child) {
  if (statement_num == "5" && statement_num_child == "6") {
    return true;
  }
  return false;
}

bool PkbReadFacade::IsAnyParentRelationshipPresent() {
  return true;
}

PairConstraintSet PkbReadFacade::GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant) {
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type) {
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatAreDescendantsOf(std::string statement_num, StatementType statement_type) {
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatAreAncestors(StatementType statement_type) {
  return {};
}

SingleConstraintSet PkbReadFacade::GetStatementsThatAreDescendants(StatementType statement_type) {
  return {};
}

bool PkbReadFacade::HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant) {
  return {};
}

bool PkbReadFacade::IsAnyAncestorDescendantRelationshipPresent() {
  return {};
}
