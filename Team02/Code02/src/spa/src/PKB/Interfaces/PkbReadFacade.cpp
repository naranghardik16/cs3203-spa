#include <memory>

#include "PkbReadFacade.h"
#include "PKB/Pkb.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "PKB/Util/ExpressionUtil.h"

PkbReadFacade::PkbReadFacade(Pkb& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() = default;

PkbReadFacade::SingleSet PkbReadFacade::GetVariables() {
  return this->pkb.entity_store_->GetVariables();
}

PkbReadFacade::SingleSet PkbReadFacade::GetConstants() {
  return this->pkb.entity_store_->GetConstants();
}

PkbReadFacade::SingleSet PkbReadFacade::GetProcedures() {
  return this->pkb.entity_store_->GetProcedures();
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatements() {
  return this->pkb.statement_store_->GetStatements();
}

PkbReadFacade::SingleSet PkbReadFacade::GetReadStatements() {
  return this->pkb.statement_store_->GetStatements(StatementType::READ);
}

PkbReadFacade::SingleSet PkbReadFacade::GetPrintStatements() {
  return this->pkb.statement_store_->GetStatements(StatementType::PRINT);
}

PkbReadFacade::SingleSet PkbReadFacade::GetCallStatements() {
  return this->pkb.statement_store_->GetStatements(StatementType::CALL);
}

PkbReadFacade::SingleSet PkbReadFacade::GetWhileStatements() {
  return this->pkb.statement_store_->GetStatements(StatementType::WHILE);
}

PkbReadFacade::SingleSet PkbReadFacade::GetIfStatements() {
  return this->pkb.statement_store_->GetStatements(StatementType::IF);
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignStatements() {
  return this->pkb.statement_store_->GetStatements(StatementType::ASSIGN);
}

PkbReadFacade::PairSet
PkbReadFacade::GetModifiesStatementVariablePairs(const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet statement_variable_pairs =
      this->pkb.modifies_store_->GetStatementVariablePairs();

  PairSet result;
  for (const auto& p: statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet
PkbReadFacade::GetVariablesModifiedByStatement(const StatementNumber& statement_number) {
  return this->pkb.modifies_store_->GetVariablesModifiedByStatement(statement_number);
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsModifiesVariable(const Variable& variable, const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet statement_variable_pairs =
      this->pkb.modifies_store_->GetStatementVariablePairs();

  SingleSet result;
  for (const auto& p: statement_variable_pairs) {
    if (statements.count(p.first) > 0 && p.second == variable) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatModify(const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet statement_variable_pairs =
      this->pkb.modifies_store_->GetStatementVariablePairs();

  SingleSet result;
  for (const auto& p: statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

bool PkbReadFacade::HasModifiesStatementRelationship(const StatementNumber& statement_number, const Variable& variable) {
  return this->pkb.modifies_store_->HasModifiesStatementVariableRelation(statement_number, variable);
}

PkbReadFacade::PairSet PkbReadFacade::GetModifiesProcedureVariablePairs() {
  return this->pkb.modifies_store_->GetProcedureVariablePairs();
}

PkbReadFacade::SingleSet PkbReadFacade::GetVariablesModifiedByProcedure(const Procedure& procedure) {
  return this->pkb.modifies_store_->GetVariablesModifiedByProcedure(procedure);
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresModifiesVariable(const Variable& variable) {
  PairSet procedure_variable_pairs =
      this->pkb.modifies_store_->GetProcedureVariablePairs();

  SingleSet result;
  for (const auto& p: procedure_variable_pairs) {
    if (p.second == variable) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresThatModify() {
  return this->pkb.modifies_store_->GetProceduresThatModify();
}

bool PkbReadFacade::HasModifiesProcedureRelationship(const Procedure& procedure, const Variable& variable) {
  return this->pkb.modifies_store_->HasModifiesProcedureVariableRelation(procedure, variable);
}

// Uses Statement API
PkbReadFacade::PairSet PkbReadFacade::GetUsesStatementVariablePairs(const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet statement_variable_pairs =
      this->pkb.uses_store_->GetStatementVariablePairs();

  PairSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatUses(const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet statement_variable_pairs =
      this->pkb.uses_store_->GetStatementVariablePairs();

  SingleSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }
  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetVariablesUsedByStatement(const StatementNumber& statement_number) {
  return this->pkb.uses_store_->retrieveAllVariablesUsedByAStatement(statement_number);
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsUsesVariable(const StatementType& statement_type,
                                                                                    const Variable& variable) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet statement_variable_pairs =
      this->pkb.uses_store_->GetStatementVariablePairs();

  SingleSet result;
  for (const auto& p : statement_variable_pairs) {
    if (statements.count(p.first) > 0 && p.second == variable) {
      result.insert(p.first);
    }
  }
  return result;
}

bool PkbReadFacade::HasUsesStatementRelationship(const StatementNumber& statement_number, const Variable& variable) {
  return this->pkb.uses_store_->HasUsesStatementVariableRelation(statement_number, variable);
}

// Uses Procedure API
PkbReadFacade::PairSet PkbReadFacade::GetUsesProcedureVariablePairs() {
  return this->pkb.uses_store_->GetProcedureVariablePairs();
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresThatUse() {
  return this->pkb.uses_store_->retrieveAllProceduresThatUse();
}

PkbReadFacade::SingleSet PkbReadFacade::GetVariablesUsedByProcedure(const Procedure& procedure) {
  return this->pkb.uses_store_->GetVariablesUsedByProcedure(procedure);
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresUsesVariable(const Variable& variable) {
  PairSet procedure_variable_pairs =
      this->pkb.uses_store_->GetProcedureVariablePairs();

  SingleSet result;
  for (const auto& p : procedure_variable_pairs) {
    if (p.second == variable) {
      result.insert(p.first);
    }
  }
  return result;
}

bool PkbReadFacade::HasUsesProcedureRelationship(const Procedure& procedure, const Variable& variable) {
  return this->pkb.uses_store_->HasUsesProcedureVariableRelation(procedure, variable);
}

// Follows API
PkbReadFacade::PairSet PkbReadFacade::GetFollowPairs(const StatementType& statement_type,
                                                                       const StatementType& statement_type_follower) {
  StatementNumberSet statements_of_type_1 =
      this->pkb.statement_store_->GetStatements(statement_type);

  StatementNumberSet statements_of_type_2 =
      this->pkb.statement_store_->GetStatements(statement_type_follower);

  PairSet follows_pairs =
      this->pkb.follows_store_->GetFollowsPairs();

  PairSet result;

  for (const auto& p: follows_pairs) {
    if (statements_of_type_1.count(p.first) > 0 && statements_of_type_2.count(p.second) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementFollowedBy(const StatementNumber& statement_number,
                                                                                 const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_pairs =
      this->pkb.follows_store_->GetFollowsPairs();

  SingleSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.first) > 0 && p.second == statement_number) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementFollowing(const StatementNumber& statement_number,
                                                                                const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_pairs =
      this->pkb.follows_store_->GetFollowsPairs();

  SingleSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.second) > 0 && p.first == statement_number) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsWithFollowers(const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_pairs =
      this->pkb.follows_store_->GetFollowsPairs();

  SingleSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementThatAreFollowers(const StatementType& statement_type) {
  StatementNumberSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_pairs =
      this->pkb.follows_store_->GetFollowsPairs();

  SingleSet result;

  for (const auto& p: follows_pairs) {
    if (statements.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

bool PkbReadFacade::HasFollowsRelationship(const StatementNumber& statement_number, const StatementNumber& statement_number_follower) {
  return this->pkb.follows_store_->HasFollowsRelation(statement_number, statement_number_follower);
}

bool PkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return this->pkb.follows_store_->HasFollowsRelation();
}

// Follows* API
PkbReadFacade::PairSet PkbReadFacade::GetFollowsStarPairs(const StatementType& statement_type_1,
                                                                            const StatementType& statement_type_2) {
  SingleSet
  statements_of_type_1 = this->pkb.statement_store_->GetStatements(statement_type_1);

  SingleSet
      statements_of_type_2 = this->pkb.statement_store_->GetStatements(statement_type_2);

  PairSet follows_star_pairs =
      this->pkb.follows_store_->GetFollowsStarPairs();

  PairSet result;

  for (const auto& p: follows_star_pairs) {
    if (statements_of_type_1.count(p.first) > 0 && statements_of_type_2.count(p.second) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStar(const StatementNumber& statement_number,
                                                                         const StatementType& statement_type) {
  SingleSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_star_pairs =
      this->pkb.follows_store_->GetFollowsStarPairs();

  SingleSet result;

  for (const auto& p: follows_star_pairs) {
    if (statement_number == p.first && statements.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStarBy(const StatementNumber& statement_number,
                                                                           const StatementType& statement_type) {
  SingleSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_star_pairs =
      this->pkb.follows_store_->GetFollowsStarPairs();

  SingleSet result;

  for (const auto& p: follows_star_pairs) {
    if (statement_number == p.second && statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStarFirst(const StatementType& statement_type) {
  SingleSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_star_pairs =
      this->pkb.follows_store_->GetFollowsStarPairs();

  SingleSet result;

  for (const auto& p: follows_star_pairs) {
    if (statements.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}


PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStarSecond(const StatementType& statement_type) {
  SingleSet statements =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet follows_star_pairs =
      this->pkb.follows_store_->GetFollowsStarPairs();

  SingleSet result;

  for (const auto& p: follows_star_pairs) {
    if (statements.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

bool PkbReadFacade::HasFollowsStarRelationship() {
  return this->pkb.follows_store_->HasFollowsStarRelation();
}

bool PkbReadFacade::HasFollowsStar(const StatementNumber& statement_number) {
  return this->pkb.follows_store_->HasFollowsStarRelation(statement_number);
}

bool PkbReadFacade::HasFollowsStarBy(const StatementNumber& statement_number) {
  return this->pkb.follows_store_->HasFollowsStarRelationBy(statement_number);
}

bool PkbReadFacade::IsFollowsStar(const StatementNumber& statement_number_1, const StatementNumber& statement_number_2) {
  return this->pkb.follows_store_->HasFollowsStarRelation(statement_number_1,
                                                          statement_number_2);
}

// Parent API
PkbReadFacade::PairSet PkbReadFacade::GetParentChildPairs(const StatementType& statement_type,
                                                                            const StatementType& statement_type_child) {
  SingleSet statement_of_type_for_parent =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet statement_of_type_for_child =
      this->pkb.statement_store_->GetStatements(statement_type_child);

  PairSet parent_child_pairs =
      this->pkb.parent_store_->GetParentPairs();

  PairSet result;
  for (const auto& p: parent_child_pairs) {
    if (statement_of_type_for_parent.count(p.first) > 0 &&
    statement_of_type_for_child.count(p.second) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementThatIsParentOf(const StatementNumber& statement_number,
                                                                                     const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  auto parent = this->pkb.parent_store_->GetParents(statement_number);

  if (!parent.empty() && statements_of_type.count(parent)) {
    result.insert(parent);
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreChildrenOf(const StatementNumber& statement_number,
                                                                                         const StatementType& statement_type) {
  SingleSet statement_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet parents_of_specified_statement =
      this->pkb.parent_store_->GetChildren(statement_number);

  SingleSet result;
  for (const auto& p: parents_of_specified_statement) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreParents(const StatementType& statement_type) {
  SingleSet statement_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.parent_store_->GetParents()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreChildren(const StatementType& statement_type) {
  SingleSet statement_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.parent_store_->GetChildren()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

bool PkbReadFacade::HasParentChildRelationship(const StatementNumber& statement_number,
                                               const StatementNumber& statement_number_child) {
  return this->pkb.parent_store_->HasParentRelation(statement_number,
                                                    statement_number_child);
}

bool PkbReadFacade::IsAnyParentRelationshipPresent() {
  return this->pkb.parent_store_->HasParentRelation();
}

// Parent* API
PkbReadFacade::PairSet
PkbReadFacade::GetAncestorDescendantPairs(const StatementType& statement_type, const StatementType& statement_type_descendant) {
  SingleSet statement_of_type_for_parent =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet statement_of_type_for_child =
      this->pkb.statement_store_->GetStatements(statement_type_descendant);

  PairSet parent_child_pairs =
      this->pkb.parent_store_->GetParentStarPairs();

  PairSet result;
  for (const auto& p: parent_child_pairs) {
    if (statement_of_type_for_parent.count(p.first) > 0 &&
        statement_of_type_for_child.count(p.second)) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsThatAreAncestorOf(const StatementNumber& statement_number, const StatementType& statement_type) {
  SingleSet statement_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet parents_of_specified_statement =
      this->pkb.parent_store_->GetAncestors(statement_number);

  SingleSet result;
  for (const auto& p: parents_of_specified_statement) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsThatAreDescendantsOf(const StatementNumber& statement_number, const StatementType& statement_type) {
  SingleSet statement_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet parents_of_specified_statement =
      this->pkb.parent_store_->GetDescendants(statement_number);

  SingleSet result;
  for (const auto& p: parents_of_specified_statement) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreAncestors(const StatementType& statement_type) {
  SingleSet statement_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.parent_store_->GetAncestors()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsThatAreDescendants(const StatementType& statement_type) {
  SingleSet statement_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.parent_store_->GetDescendants()) {
    if (statement_of_type.count(p) > 0) {
      result.insert(p);
    }
  }

  return result;
}

bool PkbReadFacade::HasAncestorDescendantRelationship(const StatementNumber& statement_number,
                                                      const StatementNumber& statement_number_descendant) {
  return this->pkb.parent_store_->HasParentStarRelation(statement_number, statement_number_descendant);
}

bool PkbReadFacade::IsAnyAncestorDescendantRelationshipPresent() {
  return this->pkb.parent_store_->HasParentStarRelation();
}

// Pattern API
PkbReadFacade::SingleSet
PkbReadFacade::GetAssignWithExactExpression(const ExpressionPtr& expr) {
  SingleSet result;

  for (const auto& s: this->GetAssignStatements()) {
    if (this->pkb.assignment_store_->GetExpressionFromStatementNumber(s)->operator==(*expr)) {
      result.insert(s);
    }
  }

  return result;
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAssignWithPartialExpression(const ExpressionPtr& sub_expression) {
  SingleSet result;

  for (const auto& s: this->GetAssignStatements()) {
    ExpressionPtr e = this->pkb.assignment_store_->GetExpressionFromStatementNumber(s);
    if (ExpressionUtil::HasSubExpression(e, sub_expression)) {
      result.insert(s);
    }
  }

  return result;
}

PkbReadFacade::PairSet PkbReadFacade::GetIfConditionVariablePair() {
  SingleSet if_statements = this->GetIfStatements();

  PairSet result;
  for (const auto& i: if_statements) {
    ExpressionPtr e = this->pkb.control_flow_store_->GetExpressionFromIfStatement(i);
    for (const auto& v: ExpressionUtil::GetAllVariablesFromExpression(e)) {
      result.insert(std::make_pair(i, v));
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetIfWithConditionVariable(const std::string &variable) {
  SingleSet if_statements = this->GetIfStatements();

  SingleSet result;
  for (const auto& i: if_statements) {
    ExpressionPtr e = this->pkb.control_flow_store_->GetExpressionFromIfStatement(i);
    if (ExpressionUtil::GetAllVariablesFromExpression(e).count(variable) > 0) {
        result.insert(i);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetIfThatHasConditionVariable() {
  SingleSet if_statements = this->GetIfStatements();

  SingleSet result;
  for (const auto& i: if_statements) {
    ExpressionPtr e = this->pkb.control_flow_store_->GetExpressionFromIfStatement(i);
    if (!ExpressionUtil::GetAllVariablesFromExpression(e).empty()) {
      result.insert(i);
    }
  }

  return result;
}

PkbReadFacade::PairSet PkbReadFacade::GetWhileConditionVariablePair() {
  SingleSet while_statements = this->GetWhileStatements();

  PairSet result;
  for (const auto& w: while_statements) {
    ExpressionPtr e = this->pkb.control_flow_store_->GetExpressionFromWhileStatement(w);
    for (const auto& v: ExpressionUtil::GetAllVariablesFromExpression(e)) {
      result.insert(std::make_pair(w, v));
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetWhileWithConditionVariable(const std::string &variable) {
  SingleSet while_statements = this->GetWhileStatements();

  PairSet uses_pairs =
      this->pkb.uses_store_->GetStatementVariablePairs();

  SingleSet result;
  for (const auto& w: while_statements) {
    ExpressionPtr e = this->pkb.control_flow_store_->GetExpressionFromWhileStatement(w);
    if (ExpressionUtil::GetAllVariablesFromExpression(e).count(variable) > 0) {
      result.insert(w);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetWhileThatHasConditionVariable() {
  SingleSet while_statements = this->GetWhileStatements();

  PairSet uses_pairs =
      this->pkb.uses_store_->GetStatementVariablePairs();

  SingleSet result;
  for (const auto& w: while_statements) {
    ExpressionPtr e = this->pkb.control_flow_store_->GetExpressionFromWhileStatement(w);
    if (!ExpressionUtil::GetAllVariablesFromExpression(e).empty()) {
      result.insert(w);
    }
  }

  return result;
}


PkbReadFacade::SingleSet
PkbReadFacade::RetrieveAllVariablesOfExpression(const ExpressionPtr& expression) {
  return this->pkb.expression_store_->GetVariablesFromExpression(expression);
}

// Calls API
PkbReadFacade::PairSet PkbReadFacade::GetCallProcedurePair() {
  return this->pkb.calls_store_->GetCallStatementToProcedurePairs();
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsPairsWithSpecifiedCaller(const Procedure& procedure) {
  PairSet calls_pairs =
      this->pkb.calls_store_->GetCallsPairs();

  PairSet result;

  for (const auto& p: calls_pairs) {
    if (p.first == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsStarPairsWithSpecifiedCaller(const Procedure& procedure) {
  PairSet calls_star_pairs =
      this->pkb.calls_store_->GetCallsStarPairs();

  PairSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.first == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsPairsWithSpecifiedCallee(const Procedure& procedure) {
  PairSet calls_pairs =
      this->pkb.calls_store_->GetCallsPairs();

  PairSet result;

  for (const auto& p: calls_pairs) {
    if (p.second == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsStarPairsWithSpecifiedCallee(const Procedure& procedure) {
  PairSet calls_star_pairs =
      this->pkb.calls_store_->GetCallsStarPairs();

  PairSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.second == procedure) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::PairSet PkbReadFacade::GetAllCallsPairs() {
  return this->pkb.calls_store_->GetCallsPairs();
}

PkbReadFacade::PairSet PkbReadFacade::GetAllCallsStarPairs() {
  return this->pkb.calls_store_->GetCallsStarPairs();
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllCallStatementsFromAProcedure(const Procedure& procedure) {
  return this->pkb.calls_store_->GetCallStatementsFromProcedure(procedure);
}

bool PkbReadFacade::HasCallsRelation(Procedure caller_procedure, Procedure callee_procedure) {
  return this->pkb.calls_store_->HasCallsRelation(caller_procedure, callee_procedure);
}

bool PkbReadFacade::HasCallsStarRelation(Procedure caller_procedure, Procedure callee_procedure) {
  return this->pkb.calls_store_->HasCallsStarRelation(caller_procedure, callee_procedure);
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCaller(const Procedure& procedure) {
  PairSet calls_pairs =
      this->pkb.calls_store_->GetCallsPairs();

  SingleSet result;

  for (const auto& p: calls_pairs) {
    if (p.first == procedure) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCallee(const Procedure& procedure) {
  PairSet calls_pairs =
      this->pkb.calls_store_->GetCallsPairs();

  SingleSet result;

  for (const auto& p: calls_pairs) {
    if (p.second == procedure) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCallers() {
  PairSet calls_pairs =
      this->pkb.calls_store_->GetCallsPairs();

  SingleSet result;

  for (const auto& p: calls_pairs) {
    result.insert(p.first);
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCallees() {
  PairSet calls_pairs =
      this->pkb.calls_store_->GetCallsPairs();

  SingleSet result;

  for (const auto& p: calls_pairs) {
    result.insert(p.second);
  }

  return result;
}

bool PkbReadFacade::IsThereAnyCallsRelationship() {
  return this->pkb.calls_store_->HasCallsRelation();
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCallerStar(const Procedure& procedure) {
  PairSet calls_star_pairs =
      this->pkb.calls_store_->GetCallsStarPairs();

  SingleSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.first == procedure) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCalleeStar(const Procedure& procedure) {
  PairSet calls_star_pairs =
      this->pkb.calls_store_->GetCallsStarPairs();

  SingleSet result;

  for (const auto& p: calls_star_pairs) {
    if (p.second == procedure) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCallersStar() {
  PairSet calls_star_pairs =
      this->pkb.calls_store_->GetCallsStarPairs();

  SingleSet result;

  for (const auto& p: calls_star_pairs) {
    result.insert(p.first);
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCalleesStar() {
  PairSet calls_star_pairs =
      this->pkb.calls_store_->GetCallsStarPairs();

  SingleSet result;

  for (const auto& p: calls_star_pairs) {
    result.insert(p.second);
  }

  return result;
}

bool PkbReadFacade::IsThereAnyCallsStarRelationship() {
  return this->pkb.calls_store_->HasCallsStarRelation();
}

// Affects API
PkbReadFacade::PairSet  PkbReadFacade::GetAffectsPairs() {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffectedBy(const StatementNumber& statement_number) {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffecting(const StatementNumber& statement_number) {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAreAffected() {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAffect() {
  // todo
  return {};
}

bool PkbReadFacade::HasAffectsRelationship(const StatementNumber& statement_number,
                                           const StatementNumber& statement_number_being_affected) {
  // todo
  return true;
}

bool PkbReadFacade::IsThereAnyAffectsRelationship() {
  // todo
  return true;
}


PkbReadFacade::PairSet PkbReadFacade::GetAffectsStarPairs() {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffectedStarBy(const StatementNumber& statement_number) {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffectingStar(const StatementNumber& statement_number) {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAreAffectedStar() {
  // todo
  return {};
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAffectStar() {
  // todo
  return {};
}

bool PkbReadFacade::HasAffectsStarRelationship(const StatementNumber& statement_number,
                                               const StatementNumber& statement_number_being_affected) {
  // todo
  return true;
}

bool PkbReadFacade::IsThereAnyAffectsStarRelationship() {
  // todo
  return true;
}

// Next API
PkbReadFacade::PairSet PkbReadFacade::GetNextPairs(const StatementType& statement_type_1, 
                                                   const StatementType& statement_type_2) {
  SingleSet statements_of_type_1 =
      this->pkb.statement_store_->GetStatements(statement_type_1);

  SingleSet statements_of_type_2 =
      this->pkb.statement_store_->GetStatements(statement_type_2);

  PairSet result;
  for (const auto& p: this->pkb.next_store_->GetNextPairs()) {
    if (statements_of_type_1.count(p.first) > 0 && statements_of_type_2.count(p.second)) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNext(const StatementNumber& statement_number,
                                                                      const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet next_pairs =
      this->pkb.next_store_->GetNextPairs();

  SingleSet result;

  for (const auto& p: next_pairs) {
    if (p.first == statement_number && statements_of_type.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextBy(const StatementNumber& statement_number,
                                                                        const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet next_pairs =
      this->pkb.next_store_->GetNextPairs();

  SingleSet result;

  for (const auto& p: next_pairs) {
    if (p.second == statement_number && statements_of_type.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextFirst(const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet next_pairs =
      this->pkb.next_store_->GetNextPairs();

  SingleSet result;
  for (const auto& p: next_pairs) {
    if (statements_of_type.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextSecond(const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  PairSet next_pairs =
      this->pkb.next_store_->GetNextPairs();

  SingleSet result;
  for (const auto& p: next_pairs) {
    if (statements_of_type.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

bool PkbReadFacade::HasNextRelationship() {
  return this->pkb.next_store_->HasNextRelation();
}

bool PkbReadFacade::HasNext(const StatementNumber& statement_number) {
  return this->pkb.next_store_->HasNextRelation(statement_number);
}

bool PkbReadFacade::HasNextBy(const StatementNumber& statement_number) {
  return this->pkb.next_store_->HasNextRelationBy(statement_number);
}

bool PkbReadFacade::IsNext(const StatementNumber& statement_number_1, const StatementNumber& statement_number_2) {
  return this->pkb.next_store_->HasNextRelation(statement_number_1, statement_number_2);
}

// Next* API
PkbReadFacade::PairSet PkbReadFacade::GetNextStarPairs(const StatementType& statement_type_1,
                                                                         const StatementType& statement_type_2) {
  SingleSet statements_of_type_1 =
      this->pkb.statement_store_->GetStatements(statement_type_1);

  SingleSet statements_of_type_2 =
      this->pkb.statement_store_->GetStatements(statement_type_2);

  PairSet result;
  for (const auto& p: this->pkb.next_store_->GetNextStarPairs()) {
    if (statements_of_type_1.count(p.first) > 0 && statements_of_type_2.count(p.second)) {
      result.insert(p);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStar(const StatementNumber& statement_number,
                                                                      const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.next_store_->GetNextStarPairs()) {
    if (statements_of_type.count(p.second) > 0 && p.first == statement_number) {
      result.insert(p.second);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStarBy(const StatementNumber& statement_number,
                                                                        const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.next_store_->GetNextStarPairs()) {
    if (statements_of_type.count(p.first) > 0 && p.second == statement_number) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStarFirst(const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.next_store_->GetNextStarPairs()) {
    if (statements_of_type.count(p.first) > 0) {
      result.insert(p.first);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStarSecond(const StatementType& statement_type) {
  SingleSet statements_of_type =
      this->pkb.statement_store_->GetStatements(statement_type);

  SingleSet result;
  for (const auto& p: this->pkb.next_store_->GetNextStarPairs()) {
    if (statements_of_type.count(p.second) > 0) {
      result.insert(p.second);
    }
  }

  return result;
}

bool PkbReadFacade::HasNextStarRelationship() {
  return this->HasNextRelationship();
}

bool PkbReadFacade::HasNextStar(const StatementNumber& statement_number) {
  return this->pkb.next_store_->HasNextStarRelation(statement_number);
}

bool PkbReadFacade::HasNextStarBy(const StatementNumber& statement_number) {
  return this->pkb.next_store_->HasNextStarRelationBy(statement_number);
}

bool PkbReadFacade::IsNextStar(const StatementNumber& statement_number_1, const StatementNumber& statement_number_2) {
  return this->pkb.next_store_->HasNextStarRelation(statement_number_1, statement_number_2);
}
