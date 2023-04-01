#include "PkbReadFacade.h"
#include "PKB/Pkb.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "PKB/Util/ExpressionUtil.h"
#include "PKB/Util/FunctionalUtil.h"

PkbReadFacade::PkbReadFacade(Pkb &pkb) : pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() = default;

// Entity Store API
PkbReadFacade::SingleSet PkbReadFacade::GetVariables() {
  return this->pkb.entity_store_->GetVariables();
}

PkbReadFacade::SingleSet PkbReadFacade::GetConstants() {
  return this->pkb.entity_store_->GetConstants();
}

PkbReadFacade::SingleSet PkbReadFacade::GetProcedures() {
  return this->pkb.entity_store_->GetProcedures();
}

// Statement API
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

// Modifies API
PkbReadFacade::SingleSet
PkbReadFacade::GetVariablesModifiedByStatement(const StatementNumber &statement_number) {
  return this->pkb.modifies_store_->GetVariablesModifiedByStatement(statement_number);
}

PkbReadFacade::PairSet
PkbReadFacade::GetModifiesStatementVariablePairs(const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.modifies_store_->GetStatementVariablePairs());
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsModifiesVariable(const Variable &variable, const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0 && p.second == variable;
  }, this->pkb.modifies_store_->GetStatementVariablePairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatModify(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.modifies_store_->GetStatementVariablePairs()));
}

bool PkbReadFacade::HasModifiesStatementRelationship(const StatementNumber &statement_number,
                                                     const Variable &variable) {
  return this->pkb.modifies_store_->HasModifiesStatementVariableRelation(statement_number, variable);
}

PkbReadFacade::SingleSet PkbReadFacade::GetVariablesModifiedByProcedure(const Procedure &procedure) {
  return this->pkb.modifies_store_->GetVariablesModifiedByProcedure(procedure);
}

PkbReadFacade::PairSet PkbReadFacade::GetModifiesProcedureVariablePairs() {
  return this->pkb.modifies_store_->GetProcedureVariablePairs();
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresModifiesVariable(const Variable &variable) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == variable;
  }, this->pkb.modifies_store_->GetProcedureVariablePairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresThatModify() {
  return this->pkb.modifies_store_->GetProceduresThatModify();
}

bool PkbReadFacade::HasModifiesProcedureRelationship(const Procedure &procedure, const Variable &variable) {
  return this->pkb.modifies_store_->HasModifiesProcedureVariableRelation(procedure, variable);
}

// Uses Statement API
PkbReadFacade::PairSet
PkbReadFacade::GetUsesStatementVariablePairs(const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.uses_store_->GetStatementVariablePairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatUses(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.uses_store_->GetStatementVariablePairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetVariablesUsedByStatement(const StatementNumber &statement_number) {
  return this->pkb.uses_store_->retrieveAllVariablesUsedByAStatement(statement_number);
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsUsesVariable(const StatementType &statement_type,
                                                                  const Variable &variable) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0 && p.second == variable;
  }, this->pkb.uses_store_->GetStatementVariablePairs()));
}

bool PkbReadFacade::HasUsesStatementRelationship(const StatementNumber &statement_number, const Variable &variable) {
  return this->pkb.uses_store_->HasUsesStatementVariableRelation(statement_number, variable);
}

// Uses Procedure API
PkbReadFacade::PairSet PkbReadFacade::GetUsesProcedureVariablePairs() {
  return this->pkb.uses_store_->GetProcedureVariablePairs();
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresThatUse() {
  return this->pkb.uses_store_->retrieveAllProceduresThatUse();
}

PkbReadFacade::SingleSet PkbReadFacade::GetVariablesUsedByProcedure(const Procedure &procedure) {
  return this->pkb.uses_store_->GetVariablesUsedByProcedure(procedure);
}

PkbReadFacade::SingleSet PkbReadFacade::GetProceduresUsesVariable(const Variable &variable) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == variable;
  }, this->pkb.uses_store_->GetProcedureVariablePairs()));
}

bool PkbReadFacade::HasUsesProcedureRelationship(const Procedure &procedure, const Variable &variable) {
  return this->pkb.uses_store_->HasUsesProcedureVariableRelation(procedure, variable);
}

// Follows API
PkbReadFacade::PairSet PkbReadFacade::GetFollowPairs(const StatementType &statement_type,
                                                     const StatementType &statement_type_follower) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0 &&
        this->pkb.statement_store_->GetStatements(statement_type_follower).count(p.second) > 0;
  }, this->pkb.follows_store_->GetFollowsPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementFollowedBy(const StatementNumber &statement_number,
                                                               const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0
        && p.second == statement_number;
  }, this->pkb.follows_store_->GetFollowsPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementFollowing(const StatementNumber &statement_number,
                                                              const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0
        && p.first == statement_number;
  }, this->pkb.follows_store_->GetFollowsPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsWithFollowers(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.follows_store_->GetFollowsPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementThatAreFollowers(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0;
  }, this->pkb.follows_store_->GetFollowsPairs()));
}

bool PkbReadFacade::HasFollowsRelationship(const StatementNumber &statement_number,
                                           const StatementNumber &statement_number_follower) {
  return this->pkb.follows_store_->HasFollowsRelation(statement_number, statement_number_follower);
}

bool PkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return this->pkb.follows_store_->HasFollowsRelation();
}

// Follows* API
PkbReadFacade::PairSet PkbReadFacade::GetFollowsStarPairs(const StatementType &statement_type_1,
                                                          const StatementType &statement_type_2) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type_1).count(p.first) > 0 &&
        this->pkb.statement_store_->GetStatements(statement_type_2).count(p.second) > 0;
  }, this->pkb.follows_store_->GetFollowsStarPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStar(const StatementNumber &statement_number,
                                                       const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0
        && p.first == statement_number;
  }, this->pkb.follows_store_->GetFollowsStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStarBy(const StatementNumber &statement_number,
                                                         const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0
        && p.second == statement_number;
  }, this->pkb.follows_store_->GetFollowsStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStarFirst(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.follows_store_->GetFollowsStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetFollowsStarSecond(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0;
  }, this->pkb.follows_store_->GetFollowsStarPairs()));
}

bool PkbReadFacade::HasFollowsStarRelationship() {
  return this->pkb.follows_store_->HasFollowsStarRelation();
}

bool PkbReadFacade::HasFollowsStar(const StatementNumber &statement_number) {
  return this->pkb.follows_store_->HasFollowsStarRelation(statement_number);
}

bool PkbReadFacade::HasFollowsStarBy(const StatementNumber &statement_number) {
  return this->pkb.follows_store_->HasFollowsStarRelationBy(statement_number);
}

bool PkbReadFacade::IsFollowsStar(const StatementNumber &statement_number_1,
                                  const StatementNumber &statement_number_2) {
  return this->pkb.follows_store_->HasFollowsStarRelation(statement_number_1,
                                                          statement_number_2);
}

// Parent API
PkbReadFacade::PairSet PkbReadFacade::GetParentChildPairs(const StatementType &statement_type,
                                                          const StatementType &statement_type_child) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0 &&
        this->pkb.statement_store_->GetStatements(statement_type_child).count(p.second) > 0;
  }, this->pkb.parent_store_->GetParentPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementThatIsParentOf(const StatementNumber &statement_number,
                                                                   const StatementType &statement_type) {
  SingleSet result;
  auto parent = this->pkb.parent_store_->GetParents(statement_number);
  if (!parent.empty() && this->pkb.statement_store_->GetStatements(statement_type).count(parent)) {
    result.insert(parent);
  }
  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreChildrenOf(const StatementNumber &statement_number,
                                                                       const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(s) > 0;
  }, this->pkb.parent_store_->GetChildren(statement_number));
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreParents(const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(s) > 0;
  }, this->pkb.parent_store_->GetParents());
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreChildren(const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(s) > 0;
  }, this->pkb.parent_store_->GetChildren());
}

bool PkbReadFacade::HasParentChildRelationship(const StatementNumber &statement_number,
                                               const StatementNumber &statement_number_child) {
  return this->pkb.parent_store_->HasParentRelation(statement_number,
                                                    statement_number_child);
}

bool PkbReadFacade::IsAnyParentRelationshipPresent() {
  return this->pkb.parent_store_->HasParentRelation();
}

// Parent* API
PkbReadFacade::PairSet
PkbReadFacade::GetAncestorDescendantPairs(const StatementType &statement_type,
                                          const StatementType &statement_type_descendant) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0 &&
        this->pkb.statement_store_->GetStatements(statement_type_descendant).count(p.second) > 0;
  }, this->pkb.parent_store_->GetParentStarPairs());
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsThatAreAncestorOf(const StatementNumber &statement_number,
                                              const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(s) > 0;
  }, this->pkb.parent_store_->GetAncestors(statement_number));
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsThatAreDescendantsOf(const StatementNumber &statement_number,
                                                 const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(s) > 0;
  }, this->pkb.parent_store_->GetDescendants(statement_number));
}

PkbReadFacade::SingleSet PkbReadFacade::GetStatementsThatAreAncestors(const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(s) > 0;
  }, this->pkb.parent_store_->GetAncestors());
}

PkbReadFacade::SingleSet
PkbReadFacade::GetStatementsThatAreDescendants(const StatementType &statement_type) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(s) > 0;
  }, this->pkb.parent_store_->GetDescendants());
}

bool PkbReadFacade::HasAncestorDescendantRelationship(const StatementNumber &statement_number,
                                                      const StatementNumber &statement_number_descendant) {
  return this->pkb.parent_store_->HasParentStarRelation(statement_number, statement_number_descendant);
}

bool PkbReadFacade::IsAnyAncestorDescendantRelationshipPresent() {
  return this->pkb.parent_store_->HasParentStarRelation();
}

// Pattern API
PkbReadFacade::SingleSet
PkbReadFacade::GetAssignWithExactExpression(const ExpressionPtr &expr) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return this->pkb.assignment_store_->GetExpressionFromStatementNumber(s)->operator==(*expr);
  }, this->GetAssignStatements());
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAssignWithPartialExpression(const ExpressionPtr &sub_expression) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return ExpressionUtil::HasSubExpression(this->pkb.assignment_store_->GetExpressionFromStatementNumber(s),
                                            sub_expression);
  }, this->GetAssignStatements());
}

PkbReadFacade::PairSet PkbReadFacade::GetIfConditionVariablePair() {
  return FunctionalUtil::Collect([&](const Single &s) {
    return
        ExpressionUtil::GetAllVariablesFromExpression(this->pkb.control_flow_store_->GetExpressionFromIfStatement(s));
  }, this->GetIfStatements());
}

PkbReadFacade::SingleSet PkbReadFacade::GetIfWithConditionVariable(const std::string &variable) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return
        ExpressionUtil::GetAllVariablesFromExpression(this->pkb.control_flow_store_->GetExpressionFromIfStatement(s))
            .count(variable) > 0;
  }, this->GetIfStatements());
}

PkbReadFacade::SingleSet PkbReadFacade::GetIfThatHasConditionVariable() {
  return FunctionalUtil::Filter([&](const Single &s) {
    return
        !ExpressionUtil::GetAllVariablesFromExpression(this->pkb.control_flow_store_->GetExpressionFromIfStatement(s))
            .empty();
  }, this->GetIfStatements());
}

PkbReadFacade::PairSet PkbReadFacade::GetWhileConditionVariablePair() {
  return FunctionalUtil::Collect([&](const Single &s) {
    return
        ExpressionUtil::GetAllVariablesFromExpression(
            this->pkb.control_flow_store_->GetExpressionFromWhileStatement(s));
  }, this->GetWhileStatements());
}

PkbReadFacade::SingleSet PkbReadFacade::GetWhileWithConditionVariable(const std::string &variable) {
  return FunctionalUtil::Filter([&](const Single &s) {
    return
        ExpressionUtil::GetAllVariablesFromExpression(
            this->pkb.control_flow_store_->GetExpressionFromWhileStatement(s))
            .count(variable) > 0;
  }, this->GetWhileStatements());
}

PkbReadFacade::SingleSet PkbReadFacade::GetWhileThatHasConditionVariable() {
  return FunctionalUtil::Filter([&](const Single &s) {
    return
        !ExpressionUtil::GetAllVariablesFromExpression(
            this->pkb.control_flow_store_->GetExpressionFromWhileStatement(s))
            .empty();
  }, this->GetWhileStatements());
}

PkbReadFacade::SingleSet
PkbReadFacade::RetrieveAllVariablesOfExpression(const ExpressionPtr &expression) {
  return this->pkb.expression_store_->GetVariablesFromExpression(expression);
}

// Calls API
PkbReadFacade::PairSet PkbReadFacade::GetCallProcedurePair() {
  return this->pkb.calls_store_->GetCallStatementToProcedurePairs();
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsPairsWithSpecifiedCaller(const Procedure &procedure) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == procedure;
  }, this->pkb.calls_store_->GetCallsPairs());
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsStarPairsWithSpecifiedCaller(const Procedure &procedure) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == procedure;
  }, this->pkb.calls_store_->GetCallsStarPairs());
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsPairsWithSpecifiedCallee(const Procedure &procedure) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == procedure;
  }, this->pkb.calls_store_->GetCallsPairs());
}

PkbReadFacade::PairSet
PkbReadFacade::GetAllCallsStarPairsWithSpecifiedCallee(const Procedure &procedure) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == procedure;
  }, this->pkb.calls_store_->GetCallsStarPairs());
}

PkbReadFacade::PairSet PkbReadFacade::GetAllCallsPairs() {
  return this->pkb.calls_store_->GetCallsPairs();
}

PkbReadFacade::PairSet PkbReadFacade::GetAllCallsStarPairs() {
  return this->pkb.calls_store_->GetCallsStarPairs();
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllCallStatementsFromAProcedure(const Procedure &procedure) {
  return this->pkb.calls_store_->GetCallStatementsFromProcedure(procedure);
}

bool PkbReadFacade::HasCallsRelation(const Procedure &caller_procedure, const Procedure &callee_procedure) {
  return this->pkb.calls_store_->HasCallsRelation(caller_procedure, callee_procedure);
}

bool PkbReadFacade::HasCallsStarRelation(const Procedure &caller_procedure, const Procedure &callee_procedure) {
  return this->pkb.calls_store_->HasCallsStarRelation(caller_procedure, callee_procedure);
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCaller(const Procedure &procedure) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == procedure;
  }, this->pkb.calls_store_->GetCallsPairs()));
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCallee(const Procedure &procedure) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == procedure;
  }, this->pkb.calls_store_->GetCallsPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCallers() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, this->pkb.calls_store_->GetCallsPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCallees() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, this->pkb.calls_store_->GetCallsPairs());
}

bool PkbReadFacade::IsThereAnyCallsRelationship() {
  return this->pkb.calls_store_->HasCallsRelation();
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCallerStar(const Procedure &procedure) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == procedure;
  }, this->pkb.calls_store_->GetCallsStarPairs()));
}

PkbReadFacade::SingleSet
PkbReadFacade::GetAllProceduresWithSpecifiedCalleeStar(const Procedure &procedure) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == procedure;
  }, this->pkb.calls_store_->GetCallsStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCallersStar() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, this->pkb.calls_store_->GetCallsStarPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllProceduresThatAreCalleesStar() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, this->pkb.calls_store_->GetCallsStarPairs());
}

bool PkbReadFacade::IsThereAnyCallsStarRelationship() {
  return this->pkb.calls_store_->HasCallsStarRelation();
}

PkbReadFacade::Procedure PkbReadFacade::GetProcedureFromCallStatement(const StatementNumber &statement_number) {
  return this->pkb.calls_store_->GetProcedureFromStatement(statement_number);
}

// Affects API
PkbReadFacade::PairSet PkbReadFacade::GetAffectsPairs() {
  PairSet result;
  const auto asses = this->GetAssignStatements();
  for (const auto &a : this->GetAssignStatements()) {
    std::stack<std::string> s;
    std::unordered_set<std::string> visited;

    s.push(a);

    std::string v = *this->GetVariablesModifiedByStatement(a).begin();
    while (!s.empty()) {
      auto current = s.top();
      s.pop();
      if (visited.count(current) > 0) {
        if (current == a && this->HasUsesStatementRelationship(current, v)) result.insert(std::make_pair(a, current));
        continue;
      }

      if (this->GetIfStatements().count(current) > 0 ||
          this->GetWhileStatements().count(current) > 0) {
        for (auto &child : this->GetNext(current, STATEMENT)) s.push(child);
        continue;
      }

      if (current != a && this->HasUsesStatementRelationship(current, v) &&
          this->GetAssignStatements().count(current) > 0)
        result.insert(std::make_pair(a, current));

      if (current != a
          && this->HasModifiesStatementRelationship(current, v))
        continue;

      if (this->GetReadStatements().count(current) > 0
          && this->HasModifiesStatementRelationship(current, v))
        continue;

      if (this->GetCallStatements().count(current) > 0 &&
          this->HasModifiesProcedureRelationship(this->GetProcedureFromCallStatement(
              current), v))
        continue;

      for (auto &child : this->GetNext(current, STATEMENT)) s.push(child);

      visited.insert(current);
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffectedBy(const StatementNumber &statement_number) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == statement_number;
  }, this->GetAffectsPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffecting(const StatementNumber &statement_number) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == statement_number;
  }, this->GetAffectsPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAreAffected() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, this->GetAffectsPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAffect() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, this->GetAffectsPairs());
}

bool PkbReadFacade::HasAffectsRelationship(const StatementNumber &statement_number,
                                           const StatementNumber &statement_number_being_affected) {
  return std::any_of(this->GetAffectsPairs().begin(), this->GetAffectsPairs().end(), [&](const Pair &p) {
    return p.first == statement_number
        && p.second == statement_number_being_affected;
  });
}

bool PkbReadFacade::IsThereAnyAffectsRelationship() {
  return !this->GetAffectsPairs().empty();
}

PkbReadFacade::PairSet PkbReadFacade::GetAffectsStarPairs() {
  std::unordered_map<std::string, std::unordered_set<std::string>> affects_map;
  std::unordered_set<std::string> keys;
  for (const auto &p : this->GetAffectsPairs()) {
    keys.insert(p.first);
    if (affects_map.count(p.first) > 0) {
      affects_map[p.first].insert(p.second);
    } else {
      affects_map[p.first] = {p.second};
    }
  }

  PairSet result;
  for (const auto &k : keys) {
    StatementNumberStack s;
    PairSet visited;
    s.push(k);

    while (!s.empty()) {
      StatementNumber current = s.top();
      s.pop();

      for (const auto &c : affects_map[current]) {
        if (!(visited.count(std::make_pair(k, c)) > 0)) {
          result.insert(std::make_pair(k, c));
          s.push(c);
          visited.insert(std::make_pair(k, c));
        }
      }
    }
  }

  return result;
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffectedStarBy(const StatementNumber &statement_number) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == statement_number;
  }, this->GetAffectsStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetAssignsAffectingStar(const StatementNumber &statement_number) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == statement_number;
  }, this->GetAffectsStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAreAffectedStar() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, this->GetAffectsStarPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetAllAssignsThatAffectStar() {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, this->GetAffectsStarPairs());
}

bool PkbReadFacade::HasAffectsStarRelationship(const StatementNumber &statement_number,
                                               const StatementNumber &statement_number_being_affected) {
  return std::any_of(this->GetAffectsStarPairs().begin(), this->GetAffectsStarPairs().end(), [&](const Pair &p) {
    return p.first == statement_number
        && p.second == statement_number_being_affected;
  });
}

bool PkbReadFacade::IsThereAnyAffectsStarRelationship() {
  return !this->GetAffectsStarPairs().empty();
}

// Next API
PkbReadFacade::PairSet PkbReadFacade::GetNextPairs(const StatementType &statement_type_1,
                                                   const StatementType &statement_type_2) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type_1).count(p.first) > 0
        && this->pkb.statement_store_->GetStatements(statement_type_2).count(p.second) > 0;
  }, this->pkb.next_store_->GetNextPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetNext(const StatementNumber &statement_number,
                                                const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == statement_number
        && this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0;
  }, this->pkb.next_store_->GetNextPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextBy(const StatementNumber &statement_number,
                                                  const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == statement_number
        && this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.next_store_->GetNextPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextFirst(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.next_store_->GetNextPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextSecond(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0;
  }, this->pkb.next_store_->GetNextPairs()));
}

bool PkbReadFacade::HasNextRelationship() {
  return this->pkb.next_store_->HasNextRelation();
}

bool PkbReadFacade::HasNext(const StatementNumber &statement_number) {
  return this->pkb.next_store_->HasNextRelation(statement_number);
}

bool PkbReadFacade::HasNextBy(const StatementNumber &statement_number) {
  return this->pkb.next_store_->HasNextRelationBy(statement_number);
}

bool PkbReadFacade::IsNext(const StatementNumber &statement_number_1, const StatementNumber &statement_number_2) {
  return this->pkb.next_store_->HasNextRelation(statement_number_1, statement_number_2);
}

// Next* API
PkbReadFacade::PairSet PkbReadFacade::GetNextStarPairs(const StatementType &statement_type_1,
                                                       const StatementType &statement_type_2) {
  return FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type_1).count(p.first) > 0
        && this->pkb.statement_store_->GetStatements(statement_type_2).count(p.second) > 0;
  }, this->pkb.next_store_->GetNextStarPairs());
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStar(const StatementNumber &statement_number,
                                                    const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.first == statement_number
        && this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0;
  }, this->pkb.next_store_->GetNextStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStarBy(const StatementNumber &statement_number,
                                                      const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return p.second == statement_number
        && this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.next_store_->GetNextStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStarFirst(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.first; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.first) > 0;
  }, this->pkb.next_store_->GetNextStarPairs()));
}

PkbReadFacade::SingleSet PkbReadFacade::GetNextStarSecond(const StatementType &statement_type) {
  return FunctionalUtil::Map([&](const Pair &p) { return p.second; }, FunctionalUtil::Filter([&](const Pair &p) {
    return this->pkb.statement_store_->GetStatements(statement_type).count(p.second) > 0;
  }, this->pkb.next_store_->GetNextStarPairs()));
}

bool PkbReadFacade::HasNextStarRelationship() {
  return this->HasNextRelationship();
}

bool PkbReadFacade::HasNextStar(const StatementNumber &statement_number) {
  return this->pkb.next_store_->HasNextStarRelation(statement_number);
}

bool PkbReadFacade::HasNextStarBy(const StatementNumber &statement_number) {
  return this->pkb.next_store_->HasNextStarRelationBy(statement_number);
}

bool PkbReadFacade::IsNextStar(const StatementNumber &statement_number_1, const StatementNumber &statement_number_2) {
  return this->pkb.next_store_->HasNextStarRelation(statement_number_1, statement_number_2);
}