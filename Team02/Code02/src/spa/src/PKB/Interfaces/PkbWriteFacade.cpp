#include <utility>

#include "General/StatementTypeEnum.h"
#include "PkbWriteFacade.h"
#include "PKB/Pkb.h"

PkbWriteFacade::PkbWriteFacade(Pkb &pkb) : pkb(pkb) {}

PkbWriteFacade::~PkbWriteFacade() = default;

PkbTypes::INDEX PkbWriteFacade::AddVariable(PkbTypes::VARIABLE variable) const {
  return pkb.entity_store_->AddVariable(std::move(variable));
}

PkbTypes::INDEX PkbWriteFacade::AddProcedure(PkbTypes::PROCEDURE procedure) const {
  return pkb.entity_store_->AddProcedure(std::move(procedure));
}

PkbTypes::INDEX PkbWriteFacade::AddConstant(PkbTypes::CONSTANT constant) const {
  return pkb.entity_store_->AddConstant(std::move(constant));
}

void PkbWriteFacade::AddStatementUsingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                               PkbTypes::VARIABLE variable) const {
  this->pkb.uses_store_->addStatementUsingVariable(statement_number, variable);

  for (const auto &p : this->pkb.parent_store_->retrieveAllAncestors(
      statement_number)) {
    this->pkb.uses_store_->addStatementUsingVariable(p, variable);
  }
}

void PkbWriteFacade::AddStatementOfAType(PkbTypes::STATEMENT_NUMBER statement_number,
                                         StatementType statement_type) const {
  this->pkb.statement_store_->addStatementForAType(statement_type,
                                                   statement_number);
}

void PkbWriteFacade::AddProcedureUsingVariable(PkbTypes::PROCEDURE procedure,
                                               PkbTypes::VARIABLE variable) const {
  this->pkb.uses_store_->addProcedureUsingVariable(std::move(procedure),
                                                   std::move(variable));
}

void PkbWriteFacade::AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                   PkbTypes::VARIABLE variable) const {
  this->pkb.modifies_store_->addStatementModifyingVariable(statement_number,
                                                           variable);

  for (const auto &p : this->pkb.parent_store_->retrieveAllAncestors(
      statement_number)) {
    this->pkb.modifies_store_->addStatementModifyingVariable(p, variable);
  }
}

void PkbWriteFacade::AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure,
                                                   PkbTypes::VARIABLE variable) const {
  this->pkb.modifies_store_->addProcedureModifyingVariable(std::move(procedure),
                                                           std::move(variable));
}

void PkbWriteFacade::AddFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                        PkbTypes::STATEMENT_NUMBER second_statement) const {
  this->pkb.follows_store_->AddFollowsRelation(std::move(first_statement),
                                               std::move(second_statement));
}

void PkbWriteFacade::AddParentRelation(PkbTypes::STATEMENT_NUMBER statement_number_1,
                                       PkbTypes::STATEMENT_NUMBER statement_number_2) const {
  this->pkb.parent_store_->addParentRelation(std::move(statement_number_1),
                                             std::move(statement_number_2));
}

void PkbWriteFacade::AddAssignmentStatementAndExpression(PkbTypes::STATEMENT_NUMBER statement_number,
                                                         std::shared_ptr<
                                                             Expression> expression) {
  this->pkb.assignment_store_->AddAssignmentExpression(statement_number,
                                                       expression);
  this->pkb.expression_store_->AddExpression(expression);

  for (const auto
        &p : this->pkb.expression_store_->GetVariablesFromExpression(
      expression)) {
    this->AddStatementUsingVariable(statement_number, p);
    this->pkb.entity_store_->AddVariable(p);
  }

  for (const auto
        &p : this->pkb.expression_store_->GetConstantsFromExpression(
      expression)) {
    this->pkb.entity_store_->AddConstant(p);
  }
}

void PkbWriteFacade::AddIfStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                                std::shared_ptr<Expression> expression) {
  this->pkb.control_flow_store_->AddIfStatementAndExpression(statement_number,
                                                             expression);
  this->pkb.expression_store_->AddExpression(expression);

  for (const auto
        &p : this->pkb.expression_store_->GetVariablesFromExpression(
      expression)) {
    this->AddStatementUsingVariable(statement_number, p);
    this->pkb.entity_store_->AddVariable(p);
  }

  for (const auto
        &p : this->pkb.expression_store_->GetConstantsFromExpression(
      expression)) {
    this->pkb.entity_store_->AddConstant(p);
  }
}

void PkbWriteFacade::AddWhileStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                                   std::shared_ptr<Expression> expression) {
  this->pkb.control_flow_store_->AddWhileStatementAndExpression(
      statement_number, expression);
  this->pkb.expression_store_->AddExpression(expression);

  for (const auto
        &p : this->pkb.expression_store_->GetVariablesFromExpression(
      expression)) {
    this->AddStatementUsingVariable(statement_number, p);
    this->pkb.entity_store_->AddVariable(p);
  }

  for (const auto
        &p : this->pkb.expression_store_->GetConstantsFromExpression(
      expression)) {
    this->pkb.entity_store_->AddConstant(p);
  }
}

void PkbWriteFacade::AddCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  this->pkb.calls_store_->AddCallsRelation(caller_procedure, callee_procedure);
}

void PkbWriteFacade::AddCallsStarRelation() {
  this->pkb.calls_store_->AddCallsStarRelation();
}

void PkbWriteFacade::AddCallStatementToProcedureName(PkbTypes::STATEMENT_NUMBER statement_number,
                                                      PkbTypes::PROCEDURE procedure) {
  this->pkb.calls_store_->AddCallStatementToProcedure(statement_number, procedure);
}

void PkbWriteFacade::AddCfg(std::shared_ptr<Cfg>& cfg) {
  this->pkb.cfg_store_->AddCfg(cfg);
  this->pkb.next_store_->setProcedureToCfgRootNodeMap(this->pkb.cfg_store_->GetProcedureToCfgNodeMap());
  this->pkb.next_store_->setStatementNumberToCfgRootNodeMap(this->pkb.cfg_store_->GetStatementNumberToCfgNodeMap());
  this->pkb.next_store_->extractNextRelations();
}

