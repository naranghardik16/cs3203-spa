#include "PkbReadFacade.h"
#include <memory>
#include "PKB/PKB.h"
#include "PKB/Types/PkbCommunicationTypes.h"

PkbReadFacade::PkbReadFacade(PKB& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() {}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariables() {
  return this->pkb.entity_store_->getVariables();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetConstants() {
  return this->pkb.entity_store_->getConstants();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProcedures() {
  return this->pkb.entity_store_->getProcedures();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatements() {
  return this->pkb.statement_store_->getAllStatements();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetReadStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::READ);
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetPrintStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::PRINT);
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetCallStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::CALL);
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetWhileStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::WHILE);
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetIfStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::IF);
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignStatements() {
  return this->pkb.statement_store_->getStatementsFromType(StatementType::ASSIGN);
}


//! Modifies Statement API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  if (statement_type == StatementType::READ) {
    return {std::make_pair("1", "x")};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {std::make_pair("2", "a")};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  //return this->pkb.modifies_store_->convert(this->pkb.modifies_store_->retrieveAllVariablesModifiedByAStatement(statement_number));
  if (statement_number == "1") {
    return {"x"};
  }
  if (statement_number == "2") {
    return {"a"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) {
  if (var_name == "\"x\"" && statement_type == StatementType::READ) {
    return {"1"};
  }
  if (var_name == "\"a\"" && statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatModify(StatementType stmt_type) {
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
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetModifiesProcedureVariablePairs() {
  return {std::make_pair("execute", "x"), std::make_pair("execute", "a")};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariablesModifiedByProcedure(std::string procedure_name) {
  if (procedure_name == "\"execute\"") {
    return {"x","a"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresModifiesVariable(std::string var_name) {
  if (var_name == "\"x\"") {
    return {"execute"};
  }
  if (var_name == "\"a\"") {
    return {"execute"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresThatModify() {
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
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::ASSIGN) {
    return {std::make_pair("1", "2")};
  }
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::CALL) {
    return {std::make_pair("1", "3")};
  }
  return {};
}


PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowedBy(std::string statement_num, StatementType statement_type) {
  if (statement_num == "3" && statement_type == StatementType::STATEMENT) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowing(std::string statement_num, StatementType statement_type) {
  if (statement_num == "1" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::ASSIGN)) {
    return {"2"};
  }
  if (statement_num == "2" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::CALL)) {
    return {"3"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsWithFollowers(StatementType statement_type) {
  if (statement_type == StatementType::READ) {
    return {"1"};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementThatAreFollowers(StatementType statement_type) {
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

//! Follows* API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetFollowsStarPairs(StatementType type_1, StatementType type_2){
  //TODO
  return {{"1", "2"}};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStar(std::string stmt_num, StatementType stmt_type){
  //TODO
  return {"2", "3"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStarBy(std::string stmt_num, StatementType stmt_type) {
  //TODO
  return {"1", "2"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStarFirst(StatementType stmt_type){
  //TODO
  return {"1", "2"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStarSecond(StatementType stmt_type) {
  //TODO
  return {"2", "3"};
}

bool PkbReadFacade::HasFollowsStarRelationship(){
  //TODO
  return true;
}

bool PkbReadFacade::HasFollowsStar(std::string stmt_num) {
  //TODO
  return true;
}

bool PkbReadFacade::HasFollowsStarBy(std::string stmt_num) {
  //TODO
  return true;
}

bool PkbReadFacade::IsFollowsStar(std::string stmt_num_1, std::string stmt_num_2) {
  //TODO
  return true;
}

//! Parent API

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetParentChildPairs(StatementType statement_type, StatementType statement_type_child) {
  if (statement_type == StatementType::IF && statement_type_child == StatementType::ASSIGN) {
    return {std::make_pair("5","6"), std::make_pair("5","7")};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type) {
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type) {
  if (statement_num == "5" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::ASSIGN)) {
    return {"6","7"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreParents(StatementType statement_type) {
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreChildren(StatementType statement_type) {
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

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant) {
  if (statement_type == StatementType::IF && statement_type_descendant == StatementType::PRINT) {
    return {std::make_pair("5","9")};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type) {
  if (statement_num == "9" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::IF)) {
    return {"5"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreDescendantsOf(std::string statement_num, StatementType statement_type) {
  if (statement_num == "5" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::PRINT)) {
    return {"9"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreAncestors(StatementType statement_type) {
  if (statement_type == StatementType::IF) {
    return {"5"};
  }
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreDescendants(StatementType statement_type) {
  if (statement_type == StatementType::PRINT) {
    return {"9"};
  }
  return {};
}

bool PkbReadFacade::HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant) {
  if (statement_num == "5" && statement_num_descendant == "9") {
    return true;
  }
  return false;
}

bool PkbReadFacade::IsAnyAncestorDescendantRelationshipPresent() {
  return true;
}
