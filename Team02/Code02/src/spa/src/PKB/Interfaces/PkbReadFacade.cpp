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
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs =
      this->pkb.modifies_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& p: statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
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
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs =
      this->pkb.modifies_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: statement_variable_pairs) {
    if (statements.count(p.first) > 0 && p.second == variable) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatModify(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs =
      this->pkb.modifies_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
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
  PkbCommunicationTypes::PairConstraintSet procedure_variable_pairs =
      this->pkb.modifies_store_->retrieveProcedureVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: procedure_variable_pairs) {
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
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetUsesStatementVariablePairs(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements = this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs = this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p);
    }
  }

  return result;
//  return {{"1", "x"}, {"2", "y"}};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatUses(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements = this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs = this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }
  return result;
//  return {"1", "2"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariablesUsedByStatement(std::string statement_number) {
  return this->pkb.uses_store_->retrieveAllVariablesUsedByAStatement(std::move(statement_number));
//  return {"x", "y"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsUsesVariable(StatementType statement_type, std::string variable) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements = this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs = this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto&p : statement_variable_pairs) {
    if (statements.count(p.first) > 0 && p.second == variable) {
      result.insert(p.first);
    }
  }
  return result;
//  return {"1"};
}

bool PkbReadFacade::HasUsesStatementRelationship(std::string statement_number, std::string variable) {
  return this->pkb.uses_store_->hasUsesRelationBetweenStatementAndVariable(std::move(statement_number), std::move(variable));
}

//! Uses Procedure API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetUsesProcedureVariablePairs() {
  //TODO
  return this->pkb.uses_store_->retrieveProcedureVariablePairs();
//  return {{"Main", "x"}, {"Main", "y"}};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresThatUse() {
  return this->pkb.uses_store_->retrieveAllProceduresThatUse();
//  return {"Main"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariablesUsedByProcedure(std::string procedure) {
  return this->pkb.uses_store_->retrieveAllVariablesUsedByAProcedure(std::move(procedure));
//  return {"x", "y"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresUsesVariable(std::string variable) {
  PkbCommunicationTypes::PairConstraintSet procedure_variable_pairs = this->pkb.uses_store_->retrieveProcedureVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p : procedure_variable_pairs) {
    if (p.second == variable) {
      result.insert(p.first);
    }
  }
  return result;
//  return {"Main"};
}

bool PkbReadFacade::HasUsesProcedureRelationship(std::string procedure, std::string variable) {
  return this->pkb.uses_store_->hasUsesRelationBetweenProcedureAndVariable(procedure, variable);

}

// Follows API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) {
  return this->pkb.follows_store_->retrieveAllFollowsPairs();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowedBy(std::string statement_num, StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.first) > 0 && p.second == statement_num) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowing(std::string statement_num, StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.second) > 0 && p.first == statement_num) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsWithFollowers(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementThatAreFollowers(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_pairs =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.second) > 0) {
      result.insert(p.second);
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

// Follows* API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetFollowsStarPairs(StatementType statement_type_1,
                                                                            StatementType statement_type_2) {
  PkbCommunicationTypes::SingleConstraintSet
  statements_of_type_1 = this->pkb.statement_store_->getStatementsFromType(statement_type_1);

  PkbCommunicationTypes::SingleConstraintSet
      statements_of_type_2 = this->pkb.statement_store_->getStatementsFromType(statement_type_2);

  PkbCommunicationTypes::PairConstraintSet follows_star_pairs =
      this->pkb.follows_store_->retrieveAllFollowsStarPairs();

  PkbCommunicationTypes::PairConstraintSet result;

  for (const auto& p: follows_star_pairs) {
    if (statements_of_type_1.count(p.first) > 0 && statements_of_type_2.count(p.second) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStar(std::string statement_number,
                                                                         StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_star_pairs =
      this->pkb.follows_store_->retrieveAllFollowsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_star_pairs) {
    if (statement_number == p.first && statements.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStarBy(std::string statement_number,
                                                                           StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_star_pairs =
      this->pkb.follows_store_->retrieveAllFollowsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_star_pairs) {
    if (statement_number == p.second && statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStarFirst(StatementType statement_type){
  PkbCommunicationTypes::SingleConstraintSet statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_star_pairs =
      this->pkb.follows_store_->retrieveAllFollowsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_star_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}


PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStarSecond(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet follows_star_pairs =
      this->pkb.follows_store_->retrieveAllFollowsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: follows_star_pairs) {
    if (statements.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

bool PkbReadFacade::HasFollowsStarRelationship(){
  return this->pkb.follows_store_->hasAnyFollowsStarRelation();
}

bool PkbReadFacade::HasFollowsStar(std::string statement_number) {
  return this->pkb.follows_store_->hasFollowsStar(statement_number);
}

bool PkbReadFacade::HasFollowsStarBy(std::string statement_number) {
  return this->pkb.follows_store_->hasFollowsStarBy(statement_number);
}

bool PkbReadFacade::IsFollowsStar(std::string statement_number_1, std::string statement_number_2) {
  return this->pkb.follows_store_->hasFollowsStarRelation(std::move(statement_number_1),
                                                          std::move(statement_number_2));
}

// Parent API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetParentChildPairs(StatementType statement_type,
                                                                            StatementType statement_type_child) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type_for_parent =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet statement_of_type_for_child =
      this->pkb.statement_store_->getStatementsFromType(statement_type_child);

  PkbCommunicationTypes::PairConstraintSet parent_child_pairs =
      this->pkb.parent_store_->retrieveAllParentPairs();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& p: parent_child_pairs) {
    if (statement_of_type_for_parent.count(p.first) > 0 &&
    statement_of_type_for_child.count(p.second)) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementThatIsParentOf(std::string statement_number,
                                                                                     StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet parents_of_specified_statement =
      this->pkb.parent_store_->retrieveAllChildren(statement_number);

  PkbCommunicationTypes::SingleConstraintSet result;
  result.insert(this->pkb.parent_store_->retrieveAllParents(statement_number));
  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreChildrenOf(std::string statement_number,
                                                                                         StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet parents_of_specified_statement =
      this->pkb.parent_store_->retrieveAllChildren(statement_number);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: parents_of_specified_statement) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreParents(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.parent_store_->retrieveAllParents()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreChildren(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.parent_store_->retrieveAllChildren()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

bool PkbReadFacade::HasParentChildRelationship(std::string statement_number,
                                               std::string statement_number_child) {
  return this->pkb.parent_store_->hasParentRelation(statement_number,
                                                    statement_number_child);
}

bool PkbReadFacade::IsAnyParentRelationshipPresent() {
  return this->pkb.parent_store_->hasAnyParentRelation();
}

//!API for ParentStar
PkbCommunicationTypes::PairConstraintSet
PkbReadFacade::GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type_for_parent =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet statement_of_type_for_child =
      this->pkb.statement_store_->getStatementsFromType(statement_type_descendant);

  PkbCommunicationTypes::PairConstraintSet parent_child_pairs =
      this->pkb.parent_store_->retrieveAllParentStarPairs();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& p: parent_child_pairs) {
    if (statement_of_type_for_parent.count(p.first) > 0 &&
        statement_of_type_for_child.count(p.second)) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetStatementsThatAreAncestorOf(std::string statement_number, StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet parents_of_specified_statement =
      this->pkb.parent_store_->retrieveAllAncestors(statement_number);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: parents_of_specified_statement) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetStatementsThatAreDescendantsOf(std::string statement_number, StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet parents_of_specified_statement =
      this->pkb.parent_store_->retrieveAllDescendants(statement_number);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: parents_of_specified_statement) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatAreAncestors(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.parent_store_->retrieveAllAncestors()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetStatementsThatAreDescendants(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statement_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.parent_store_->retrieveAllDescendants()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

bool PkbReadFacade::HasAncestorDescendantRelationship(std::string statement_number,
                                                      std::string statement_number_descendant) {
  return this->pkb.parent_store_->hasParentStarRelation(statement_number, statement_number_descendant);
}

bool PkbReadFacade::IsAnyAncestorDescendantRelationshipPresent() {
  return this->pkb.parent_store_->hasAnyParentStarRelation();
}

//! Pattern API
PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignWithExactExpression(std::string expr) {
  return {"1", "2"};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignWithPartialExpression(std::string sub_expr) {
  return {"1", "2"};
}
