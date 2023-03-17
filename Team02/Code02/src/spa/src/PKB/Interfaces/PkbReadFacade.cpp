#include <memory>

#include "PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "PKB/Util/ExpressionUtil.h"

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

PkbCommunicationTypes::PairConstraintSet
PkbReadFacade::GetModifiesStatementVariablePairs(StatementType statement_type) {
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

// Uses Statement API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetUsesStatementVariablePairs(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs =
      this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsThatUses(StatementType statement_type) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs =
      this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }
  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariablesUsedByStatement(std::string statement_number) {
  return this->pkb.uses_store_->retrieveAllVariablesUsedByAStatement(std::move(statement_number));
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementsUsesVariable(StatementType statement_type,
                                                                                    std::string variable) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet statement_variable_pairs =
      this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0 && p.second == variable) {
      result.insert(p.first);
    }
  }
  return result;
}

bool PkbReadFacade::HasUsesStatementRelationship(std::string statement_number, std::string variable) {
  return this->pkb.uses_store_->hasUsesRelationBetweenStatementAndVariable(std::move(statement_number),
                                                                           std::move(variable));
}

// Uses Procedure API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetUsesProcedureVariablePairs() {
  return this->pkb.uses_store_->retrieveProcedureVariablePairs();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresThatUse() {
  return this->pkb.uses_store_->retrieveAllProceduresThatUse();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetVariablesUsedByProcedure(std::string procedure) {
  return this->pkb.uses_store_->retrieveAllVariablesUsedByAProcedure(std::move(procedure));
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetProceduresUsesVariable(std::string variable) {
  PkbCommunicationTypes::PairConstraintSet procedure_variable_pairs =
      this->pkb.uses_store_->retrieveProcedureVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p : procedure_variable_pairs) {
    if (p.second == variable) {
      result.insert(p.first);
    }
  }
  return result;
}

bool PkbReadFacade::HasUsesProcedureRelationship(std::string procedure, std::string variable) {
  return this->pkb.uses_store_->hasUsesRelationBetweenProcedureAndVariable(procedure, variable);
}

// Follows API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetFollowPairs(StatementType statement_type,
                                                                       StatementType statement_type_follower) {
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_of_type_1 =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  std::unordered_set<PkbTypes::STATEMENT_NUMBER> statements_of_type_2 =
      this->pkb.statement_store_->getStatementsFromType(statement_type_follower);

  PkbCommunicationTypes::PairConstraintSet follows_pairs =
      this->pkb.follows_store_->retrieveAllFollowsPairs();

  PkbCommunicationTypes::PairConstraintSet result;

  for (const auto& p: follows_pairs) {
    if (statements_of_type_1.count(p.first) > 0 && statements_of_type_2.count(p.second) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowedBy(std::string statement_num,
                                                                                 StatementType statement_type) {
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

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementFollowing(std::string statement_num,
                                                                                StatementType statement_type) {
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
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
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

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetFollowsStarFirst(StatementType statement_type) {
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

bool PkbReadFacade::HasFollowsStarRelationship() {
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
    statement_of_type_for_child.count(p.second) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetStatementThatIsParentOf(std::string statement_number,
                                                                                     StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  auto parent = this->pkb.parent_store_->retrieveAllParents(statement_number);

  if (!parent.empty() && statements_of_type.count(parent)) {
    result.insert(parent);
  }

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

// Parent* API
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

// Pattern API
PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetAssignWithExactExpression(const std::shared_ptr<Expression>& expr) {
  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& s: this->GetAssignStatements()) {
    if (this->pkb.assignment_store_->retrieveAssignmentExpressionByStatementNumber(s)->operator==(*expr)) {
      result.insert(s);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetAssignWithPartialExpression(const std::shared_ptr<Expression>& sub_expression) {
  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& s: this->GetAssignStatements()) {
    std::shared_ptr<Expression> e = this->pkb.assignment_store_->retrieveAssignmentExpressionByStatementNumber(s);
    if (ExpressionUtil::hasSubExpression(e, sub_expression)) {
      result.insert(s);
    }
  }

  return result;
}

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetIfConditionVariablePair() {
  PkbCommunicationTypes::SingleConstraintSet if_statements = this->GetIfStatements();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& i: if_statements) {
    std::shared_ptr<Expression> e = this->pkb.control_flow_store_->retrieveIfStatementCondition(i);
    for (const auto& v: ExpressionUtil::retrieveAllVariablesFromExpression(e)) {
      result.insert(std::make_pair(i, v));
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetIfWithConditionVariable(const std::string &variable) {
  PkbCommunicationTypes::SingleConstraintSet if_statements = this->GetIfStatements();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& i: if_statements) {
    std::shared_ptr<Expression> e = this->pkb.control_flow_store_->retrieveIfStatementCondition(i);
    if (ExpressionUtil::retrieveAllVariablesFromExpression(e).count(variable) > 0) {
        result.insert(i);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetIfThatHasConditionVariable() {
  PkbCommunicationTypes::SingleConstraintSet if_statements = this->GetIfStatements();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& i: if_statements) {
    std::shared_ptr<Expression> e = this->pkb.control_flow_store_->retrieveIfStatementCondition(i);
    if (!ExpressionUtil::retrieveAllVariablesFromExpression(e).empty()) {
      result.insert(i);
    }
  }

  return result;
}

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetWhileConditionVariablePair() {
  PkbCommunicationTypes::SingleConstraintSet while_statements = this->GetWhileStatements();

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& w: while_statements) {
    std::shared_ptr<Expression> e = this->pkb.control_flow_store_->retrieveWhileStatementCondition(w);
    for (const auto& v: ExpressionUtil::retrieveAllVariablesFromExpression(e)) {
      result.insert(std::make_pair(w, v));
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetWhileWithConditionVariable(const std::string &variable) {
  PkbCommunicationTypes::SingleConstraintSet while_statements = this->GetWhileStatements();

  PkbCommunicationTypes::PairConstraintSet uses_pairs =
      this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& w: while_statements) {
    std::shared_ptr<Expression> e = this->pkb.control_flow_store_->retrieveWhileStatementCondition(w);
    if (ExpressionUtil::retrieveAllVariablesFromExpression(e).count(variable) > 0) {
      result.insert(w);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetWhileThatHasConditionVariable() {
  PkbCommunicationTypes::SingleConstraintSet while_statements = this->GetWhileStatements();

  PkbCommunicationTypes::PairConstraintSet uses_pairs =
      this->pkb.uses_store_->retrieveStatementVariablePairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& w: while_statements) {
    std::shared_ptr<Expression> e = this->pkb.control_flow_store_->retrieveWhileStatementCondition(w);
    if (!ExpressionUtil::retrieveAllVariablesFromExpression(e).empty()) {
      result.insert(w);
    }
  }

  return result;
}


PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::RetrieveAllVariablesOfExpression(std::shared_ptr<Expression> expression) {
  return this->pkb.expression_store_->retrieveVariablesOfTheExpression(expression);
}

// Calls API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetCallProcedurePair() {
  return this->pkb.calls_store_->retrieveAllCallStatementToProcedurePairs();
}

PkbCommunicationTypes::PairConstraintSet
PkbReadFacade::GetAllCallsPairsWithSpecifiedCaller(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_pairs =
      this->pkb.calls_store_->retrieveAllCallsPairs();

  PkbCommunicationTypes::PairConstraintSet result;

  for (const auto& p: calls_pairs) {
    if (p.first == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::PairConstraintSet
PkbReadFacade::GetAllCallsStarPairsWithSpecifiedCaller(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_star_pairs =
      this->pkb.calls_store_->retrieveAllCallsStarPairs();

  PkbCommunicationTypes::PairConstraintSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.first == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::PairConstraintSet
PkbReadFacade::GetAllCallsPairsWithSpecifiedCallee(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_pairs =
      this->pkb.calls_store_->retrieveAllCallsPairs();

  PkbCommunicationTypes::PairConstraintSet result;

  for (const auto& p: calls_pairs) {
    if (p.second == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::PairConstraintSet
PkbReadFacade::GetAllCallsStarPairsWithSpecifiedCallee(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_star_pairs =
      this->pkb.calls_store_->retrieveAllCallsStarPairs();

  PkbCommunicationTypes::PairConstraintSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.second == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetAllCallsPairs() {
  return this->pkb.calls_store_->retrieveAllCallsPairs();
}

PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetAllCallsStarPairs() {
  return this->pkb.calls_store_->retrieveAllCallsStarPairs();
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetAllCallStatementsFromAProcedure(PkbTypes::PROCEDURE procedure) {
  return this->pkb.calls_store_->retrieveCallStatementsFromAProcedure(procedure);
}

bool PkbReadFacade::HasCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  return this->pkb.calls_store_->hasCallsRelation(caller_procedure, callee_procedure);
}

bool PkbReadFacade::HasCallsStarRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  return this->pkb.calls_store_->hasCallsStarRelation(caller_procedure, callee_procedure);
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetAllProceduresWithSpecifiedCaller(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_pairs =
      this->pkb.calls_store_->retrieveAllCallsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_pairs) {
    if (p.first == procedure) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetAllProceduresWithSpecifiedCallee(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_pairs =
      this->pkb.calls_store_->retrieveAllCallsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_pairs) {
    if (p.second == procedure) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllProceduresThatAreCallers() {
  PkbCommunicationTypes::PairConstraintSet calls_pairs =
      this->pkb.calls_store_->retrieveAllCallsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_pairs) {
    result.insert(p.first);
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllProceduresThatAreCallees() {
  PkbCommunicationTypes::PairConstraintSet calls_pairs =
      this->pkb.calls_store_->retrieveAllCallsPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_pairs) {
    result.insert(p.second);
  }

  return result;
}

bool PkbReadFacade::IsThereAnyCallsRelationship() {
  return this->pkb.calls_store_->hasAnyCallsRelation();
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetAllProceduresWithSpecifiedCallerStar(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_star_pairs =
      this->pkb.calls_store_->retrieveAllCallsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.first == procedure) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet
PkbReadFacade::GetAllProceduresWithSpecifiedCalleeStar(PkbTypes::PROCEDURE procedure) {
  PkbCommunicationTypes::PairConstraintSet calls_star_pairs =
      this->pkb.calls_store_->retrieveAllCallsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.second == procedure) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllProceduresThatAreCallersStar() {
  PkbCommunicationTypes::PairConstraintSet calls_star_pairs =
      this->pkb.calls_store_->retrieveAllCallsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_star_pairs) {
    result.insert(p.first);
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllProceduresThatAreCalleesStar() {
  PkbCommunicationTypes::PairConstraintSet calls_star_pairs =
      this->pkb.calls_store_->retrieveAllCallsStarPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: calls_star_pairs) {
    result.insert(p.second);
  }

  return result;
}

bool PkbReadFacade::IsThereAnyCallsStarRelationship() {
  return this->pkb.calls_store_->hasAnyCallsStarRelation();
}

// Affects API
PkbCommunicationTypes::PairConstraintSet  PkbReadFacade::GetAffectsPairs() {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignsAffectedBy(std::string stmt_num) {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignsAffecting(std::string stmt_num) {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllAssignsThatAreAffected() {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllAssignsThatAffect() {
  // todo
  return {};
}

bool PkbReadFacade::HasAffectsRelationship(std::string stmt_num, std::string stmt_num_being_affected) {
  // todo
  return true;
}

bool PkbReadFacade::IsThereAnyAffectsRelationship() {
  // todo
  return true;
}


PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetAffectsStarPairs() {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignsAffectedStarBy(std::string stmt_num) {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAssignsAffectingStar(std::string stmt_num) {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllAssignsThatAreAffectedStar() {
  // todo
  return {};
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetAllAssignsThatAffectStar() {
  // todo
  return {};
}

bool PkbReadFacade::HasAffectsStarRelationship(std::string stmt_num, std::string stmt_num_being_affected) {
  // todo
  return true;
}

bool PkbReadFacade::IsThereAnyAffectsStarRelationship() {
  // todo
  return true;
}

// Next API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetNextPairs(StatementType statement_type_1,
                                                                         StatementType statement_type_2) {
  return this->pkb.next_store_->retrieveAllNextPairs();
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNext(std::string statement_number,
                                                                      StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet next_pairs =
      this->pkb.next_store_->retrieveAllNextPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: next_pairs) {
    if (p.first == statement_number && statements_of_type.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNextBy(std::string statement_number,
                                                                        StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet next_pairs =
      this->pkb.next_store_->retrieveAllNextPairs();

  PkbCommunicationTypes::SingleConstraintSet result;

  for (const auto& p: next_pairs) {
    if (p.second == statement_number && statements_of_type.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNextFirst(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet next_pairs =
      this->pkb.next_store_->retrieveAllNextPairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: next_pairs) {
    if (statements_of_type.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNextSecond(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::PairConstraintSet next_pairs =
      this->pkb.next_store_->retrieveAllNextPairs();

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: next_pairs) {
    if (statements_of_type.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

bool PkbReadFacade::HasNextRelationship() {
  return this->pkb.next_store_->hasAnyNextRelation();
}

bool PkbReadFacade::HasNext(std::string statement_number) {
  return this->pkb.next_store_->hasNext(statement_number);
}

bool PkbReadFacade::HasNextBy(std::string statement_number) {
  return this->pkb.next_store_->hasNextBy(statement_number);
}

bool PkbReadFacade::IsNext(std::string statement_number_1, std::string statement_number_2) {
  return this->pkb.next_store_->hasNextRelation(statement_number_1, statement_number_2);
}

// Next* API
PkbCommunicationTypes::PairConstraintSet PkbReadFacade::GetNextStarPairs(StatementType statement_type_1,
                                                                         StatementType statement_type_2) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type_1 =
      this->pkb.statement_store_->getStatementsFromType(statement_type_1);

  PkbCommunicationTypes::SingleConstraintSet statements_of_type_2 =
      this->pkb.statement_store_->getStatementsFromType(statement_type_2);

  PkbCommunicationTypes::PairConstraintSet result;
  for (const auto& p: this->pkb.next_store_->retrieveAllNextStarPairs()) {
    if (statements_of_type_1.count(p.first) > 0 && statements_of_type_2.count(p.second)) {
      result.insert(p);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNextStar(std::string statement_number,
                                                                      StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.next_store_->retrieveAllNextStarPairs()) {
    if (statements_of_type.count(p.second) > 0 && p.first == statement_number) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNextStarBy(std::string statement_number,
                                                                        StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.next_store_->retrieveAllNextStarPairs()) {
    if (statements_of_type.count(p.first) > 0 && p.second == statement_number) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNextStarFirst(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.next_store_->retrieveAllNextStarPairs()) {
    if (statements_of_type.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbCommunicationTypes::SingleConstraintSet PkbReadFacade::GetNextStarSecond(StatementType statement_type) {
  PkbCommunicationTypes::SingleConstraintSet statements_of_type =
      this->pkb.statement_store_->getStatementsFromType(statement_type);

  PkbCommunicationTypes::SingleConstraintSet result;
  for (const auto& p: this->pkb.next_store_->retrieveAllNextStarPairs()) {
    if (statements_of_type.count(p.first) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

bool PkbReadFacade::HasNextStarRelationship() {
  return this->HasNextRelationship();
}

bool PkbReadFacade::HasNextStar(std::string statement_number) {
  return this->pkb.next_store_->hasNextStar(statement_number);
}

bool PkbReadFacade::HasNextStarBy(std::string statement_number) {
  return this->pkb.next_store_->hasNextStarBy(statement_number);
}

bool PkbReadFacade::IsNextStar(std::string statement_number_1, std::string statement_number_2) {
  return this->pkb.next_store_->hasNextStarRelation(statement_number_1, statement_number_2);
}
