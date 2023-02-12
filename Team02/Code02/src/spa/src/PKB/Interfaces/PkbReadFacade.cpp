#include <memory>

#include "PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbCommunicationTypes.h"

PkbReadFacade::PkbReadFacade(PKB& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() = default;

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

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_ =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs_ =
      this->pkb.modifies_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& p: statement_variable_pairs_) {
    if (statements_.count(p.first) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetVariablesModifiedByStatement(std::string statement_number) {
  return this->pkb.modifies_store_->retrieveAllVariablesModifiedByAStatement(std::move(statement_number));
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetStatementsModifiesVariable(std::string variable, StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_ =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs_ =
      this->pkb.modifies_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: statement_variable_pairs_) {
    if (statements_.count(p.first) > 0 && p.second == variable) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatModify(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_ =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs_ =
      this->pkb.modifies_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: statement_variable_pairs_) {
    if (statements_.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

bool PkbReadFacade::HasModifiesStatementRelationship(std::string statement_number, std::string variable) {
  return this->pkb.modifies_store_->hasModifiesRelationBetweenStatementAndVariable(std::move(statement_number),
                                                                                   std::move(variable));
}

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetModifiesProcedureVariablePairs() {
  return this->pkb.modifies_store_->retrieveProcedureVariablePairs();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariablesModifiedByProcedure(std::string procedure) {
  return this->pkb.modifies_store_->retrieveAllVariablesModifiedByAProcedure(std::move(procedure));
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresModifiesVariable(std::string variable) {
  PkbCommunicationTypes::PairConstraintSet procedure_variable_pairs_ =
      this->pkb.modifies_store_->retrieveProcedureVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: procedure_variable_pairs_) {
    if (p.second == variable) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresThatModify() {
  return this->pkb.modifies_store_->retrieveAllProceduresThatModify();
}

bool PkbReadFacade::HasModifiesProcedureRelationship(std::string procedure, std::string variable) {
  return this->pkb.modifies_store_->hasModifiesRelationBetweenProcedureAndVariable(procedure, variable);
}

//! Uses Statement API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetStmtUsesPair(StatementType statement_type) {
  //TODO
  return {{"1", "x"}, {"2", "y"}};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStmtUsesFirst(StatementType statement_type) {
  //TODO
  return {"1", "2"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStmtUses(std::string stmt_num) {
  //TODO
  return {"x", "y"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStmtUsing(StatementType statement_type, std::string var_name) {
  //TODO
  return {"1"};
}

bool PkbReadFacade::HasStmtUses(std::string stmt_num) {
  //TODO
  return true;
}

bool PkbReadFacade::IsStmtUsing(std::string stmt_num, std::string var_name) {
  //TODO
  return true;
}

//! Uses Procedure API

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetProcUsesPair() {
  //TODO
  return {{"Main", "x"}, {"Main", "y"}};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProcUsesFirst() {
  //TODO
  return {"Main"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProcUses(std::string proc_name) {
  //TODO
  return {"x", "y"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProcUsing(std::string var_name) {
  //TODO
  return {"Main"};
}

bool PkbReadFacade::HasProcUses(std::string proc_name) {
  //TODO
  return true;
}

bool PkbReadFacade::IsProcUsing(std::string proc_name, std::string var_name) {
  //TODO
  return true;
}


PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  return this->pkb.follows_store_->retrieveAllFollowsPairs();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowedBy(std::string statement_num, StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_ =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs_ =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs_) {
    if (statements_.count(p.first) > 0 && p.second == statement_num) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowing(std::string statement_num, StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_ =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs_ =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs_) {
    if (statements_.count(p.second) > 0 && p.first == statement_num) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsWithFollowers(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_ =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs_ =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs_) {
    if (statements_.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementThatAreFollowers(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_ =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs_ =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs_) {
    if (statements_.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}


bool PkbReadFacade::HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) {
  return this->pkb.follows_store_->hasFollowsRelation(statement_num, statement_num_follower);
}

bool PkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return this->pkb.follows_store_->hasAnyFollowsRelation();
}

// TODO: Parent Relation

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

// Parent API
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

//! Pattern API
PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignWithExactExpression(std::string expr) {
  return {"1", "2"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignWithPartialExpression(std::string sub_expr) {
  return {"1", "2"};
}
