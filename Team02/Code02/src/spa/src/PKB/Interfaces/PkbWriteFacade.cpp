#include "PkbWriteFacade.h"

PkbWriteFacade::PkbWriteFacade(Pkb &pkb) : pkb(pkb) {}

PkbWriteFacade::~PkbWriteFacade() = default;

PkbTypes::INDEX PkbWriteFacade::AddVariable(const Variable &variable) const {
  return pkb.entity_store_->AddVariable(variable);
}

PkbTypes::INDEX PkbWriteFacade::AddProcedure(const Procedure &procedure) const {
  return pkb.entity_store_->AddProcedure(procedure);
}

PkbTypes::INDEX PkbWriteFacade::AddConstant(const Constant &constant) const {
  return pkb.entity_store_->AddConstant(constant);
}

void PkbWriteFacade::AddUsesSideEffects(const StatementNumber &statement_number,
                                        const Variable &variable) const {
  StatementNumberSet ancestors = this->pkb.parent_store_->GetAncestors(statement_number);
  std::for_each(ancestors.begin(), ancestors.end(), [&](auto &p) {
    this->pkb.uses_store_->AddStatementUsesVariable(p, variable);
  });
}

void PkbWriteFacade::AddModifiesSideEffects(const StatementNumber &statement_number,
                                            const Variable &variable) const {
  StatementNumberSet ancestors = this->pkb.parent_store_->GetAncestors(statement_number);
  std::for_each(ancestors.begin(), ancestors.end(), [&](auto &p) {
    this->pkb.modifies_store_->AddStatementModifiesVariable(p, variable);
  });
}

void PkbWriteFacade::AddStatementUsingVariable(const StatementNumber &statement_number,
                                               const Variable &variable) const {
  this->pkb.uses_store_->AddStatementUsesVariable(statement_number, variable);
  this->AddUsesSideEffects(statement_number, variable);
}

void PkbWriteFacade::AddStatementOfAType(const StatementNumber &statement_number,
                                         const StatementType &statement_type) const {
  this->pkb.statement_store_->AddStatementAndType(statement_type, statement_number);
}

void PkbWriteFacade::AddProcedureUsingVariable(const Procedure &procedure,
                                               const Variable &variable) const {
  this->pkb.uses_store_->AddProcedureUsesVariable(procedure, variable);
}

void PkbWriteFacade::AddStatementModifyingVariable(const StatementNumber &statement_number,
                                                   const Variable &variable) const {
  this->pkb.modifies_store_->AddStatementModifiesVariable(statement_number, variable);
  this->AddModifiesSideEffects(statement_number, variable);
}

void PkbWriteFacade::AddProcedureModifyingVariable(const Procedure &procedure,
                                                   const Variable &variable) const {
  this->pkb.modifies_store_->AddProcedureModifiesVariable(procedure, variable);
}

void PkbWriteFacade::AddFollowsRelation(const StatementNumber &first_statement,
                                        const StatementNumber &second_statement) const {
  this->pkb.follows_store_->AddFollowsRelation(first_statement, second_statement);
}

void PkbWriteFacade::AddFollowsStarRelation() const {
  this->pkb.follows_store_->AddFollowsStarRelation();
}

void PkbWriteFacade::AddParentRelation(const StatementNumber &statement_number_1,
                                       const StatementNumber &statement_number_2) const {
  this->pkb.parent_store_->AddParentRelation(statement_number_1, statement_number_2);
}

void PkbWriteFacade::AddParentStarRelation() const {
  this->pkb.parent_store_->AddParentStarRelation();

  for (const auto &p : this->pkb.modifies_store_->GetStatementVariablePairs()) {
    this->AddModifiesSideEffects(p.first, p.second);
  }

  for (const auto &p : this->pkb.uses_store_->GetStatementVariablePairs()) {
    this->AddUsesSideEffects(p.first, p.second);
  }
}

void PkbWriteFacade::AddExpressionSideEffects(const StatementNumber &statement_number,
                                              const ExpressionPtr &expression) const {
  VariableSet variables = this->pkb.expression_store_->GetVariablesFromExpression(expression);
  std::for_each(variables.begin(), variables.end(), [&](auto &p) {
    this->AddStatementUsingVariable(statement_number, p);
    this->pkb.entity_store_->AddVariable(p);
  });

  ConstantSet constants = this->pkb.expression_store_->GetConstantsFromExpression(expression);
  std::for_each(constants.begin(), constants.end(), [&](auto &p) {
    this->pkb.entity_store_->AddConstant(p);
  });
}

void PkbWriteFacade::AddAssignmentStatementAndExpression(const StatementNumber &statement_number,
                                                         const ExpressionPtr &expression) {
  this->pkb.assignment_store_->AddAssignmentExpression(statement_number, expression);
  this->pkb.expression_store_->AddExpression(expression);
  this->AddExpressionSideEffects(statement_number, expression);
}

void PkbWriteFacade::AddIfStatementAndCondition(const StatementNumber &statement_number,
                                                const ExpressionPtr &expression) {
  this->pkb.control_flow_store_->AddIfStatementAndExpression(statement_number, expression);
  this->pkb.expression_store_->AddExpression(expression);
  this->AddExpressionSideEffects(statement_number, expression);
}

void PkbWriteFacade::AddWhileStatementAndCondition(const StatementNumber &statement_number,
                                                   const ExpressionPtr &expression) {
  this->pkb.control_flow_store_->AddWhileStatementAndExpression(
      statement_number, expression);
  this->pkb.expression_store_->AddExpression(expression);
  this->AddExpressionSideEffects(statement_number, expression);
}

void PkbWriteFacade::AddCallsRelation(const Procedure &caller_procedure, const Procedure &callee_procedure) {
  this->pkb.calls_store_->AddCallsRelation(caller_procedure, callee_procedure);
}

void PkbWriteFacade::AddCallsStarRelation() {
  this->pkb.calls_store_->AddCallsStarRelation();
}

void PkbWriteFacade::AddCallStatementToProcedureName(const StatementNumber &statement_number,
                                                     const Procedure &procedure) {
  this->pkb.calls_store_->AddCallStatementToProcedure(statement_number, procedure);
}

void PkbWriteFacade::AddCfg(const CfgPtr &cfg) {
  this->pkb.cfg_store_->AddCfg(cfg);
  this->pkb.next_store_->SetProcedureToCfgNodeMap(this->pkb.cfg_store_->GetProcedureToCfgNodeMap());
  this->pkb.next_store_->SetStatementNumberToCfgNodeMap(this->pkb.cfg_store_->GetStatementNumberToCfgNodeMap());
  this->pkb.next_store_->AddNextRelations();
}

