#include <utility>

#include "General/StatementTypeEnum.h"
#include "PkbWriteFacade.h"
#include "PKB/PKB.h"


PkbWriteFacade::PkbWriteFacade(PKB& pkb): pkb(pkb) {}

PkbWriteFacade::~PkbWriteFacade() = default;

PkbTypes::INDEX PkbWriteFacade::AddVariable(PkbTypes::VARIABLE variable) const {
  return pkb.entity_store_->addVariable(std::move(variable));
}

PkbTypes::INDEX PkbWriteFacade::AddProcedure(PkbTypes::PROCEDURE procedure) const {
  return pkb.entity_store_->addProcedure(std::move(procedure));
}

PkbTypes::INDEX PkbWriteFacade::AddConstant(PkbTypes::CONSTANT constant) const {
  return pkb.entity_store_->addConstant(std::move(constant));
}

void PkbWriteFacade::AddStatementUsingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                               PkbTypes::VARIABLE variable) const {
  this->pkb.uses_store_->addStatementUsingVariable(statement_number, variable);

  for (const auto& p: this->pkb.parent_store_->retrieveAllAncestors(statement_number)) {
    this->pkb.uses_store_->addStatementUsingVariable(p, variable);
  }
}

void PkbWriteFacade::AddStatementOfAType(PkbTypes::STATEMENT_NUMBER statement_number,
                                         StatementType statement_type) const {
  this->pkb.statement_store_->addStatementForAType(statement_type, statement_number);
}

void PkbWriteFacade::AddProcedureUsingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) const {
  this->pkb.uses_store_->addProcedureUsingVariable(std::move(procedure), std::move(variable));
}

void PkbWriteFacade::AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                   PkbTypes::VARIABLE variable) const {
  this->pkb.modifies_store_->addStatementModifyingVariable(statement_number, variable);

  for (const auto& p: this->pkb.parent_store_->retrieveAllAncestors(statement_number)) {
    this->pkb.modifies_store_->addStatementModifyingVariable(p, variable);
  }
}

void PkbWriteFacade::AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) const {
  this->pkb.modifies_store_->addProcedureModifyingVariable(std::move(procedure), std::move(variable));
}

void PkbWriteFacade::AddFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                        PkbTypes::STATEMENT_NUMBER second_statement) const {
  this->pkb.follows_store_->addFollowsRelation(std::move(first_statement),
                                               std::move(second_statement));
}

void PkbWriteFacade::AddParentRelation(PkbTypes::STATEMENT_NUMBER statement_number_1,
                                       PkbTypes::STATEMENT_NUMBER statement_number_2) const {
  this->pkb.parent_store_->addParentRelation(std::move(statement_number_1),
                                             std::move(statement_number_2));
}

void PkbWriteFacade::AddAssignmentStatementAndExpression(PkbTypes::STATEMENT_NUMBER statement_number,
                                                         Expression* expression) {
  this->pkb.assignment_store_->addAssignmentExpression(std::move(statement_number), expression);
  this->pkb.expression_store_->addExpression(expression);

  for (const auto& p: this->pkb.expression_store_->retrieveVariablesOfTheExpression(expression)) {
    this->pkb.uses_store_->addStatementUsingVariable(statement_number, p);
    this->pkb.entity_store_->addVariable(p);
  }

  for (const auto& p: this->pkb.expression_store_->retrieveConstantsOfTheExpression(expression)) {
    this->pkb.entity_store_->addConstant(p);
  }
}

void PkbWriteFacade::AddIfStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                                Expression *expression) {
  this->pkb.control_flow_store_->addIfStatementAndCondition(std::move(statement_number), expression);
  this->pkb.expression_store_->addExpression(expression);

  for (const auto& p: this->pkb.expression_store_->retrieveVariablesOfTheExpression(expression)) {
    this->pkb.uses_store_->addStatementUsingVariable(statement_number, p);
    this->pkb.entity_store_->addVariable(p);
  }

  for (const auto& p: this->pkb.expression_store_->retrieveConstantsOfTheExpression(expression)) {
    this->pkb.entity_store_->addConstant(p);
  }
}

void PkbWriteFacade::AddWhileStatementAndCondition(PkbTypes::STATEMENT_NUMBER statement_number,
                                                   Expression *expression) {
  this->pkb.control_flow_store_->addWhileStatementAndCondition(std::move(statement_number), expression);
  this->pkb.expression_store_->addExpression(expression);

  for (const auto& p: this->pkb.expression_store_->retrieveVariablesOfTheExpression(expression)) {
    this->pkb.uses_store_->addStatementUsingVariable(statement_number, p);
    this->pkb.entity_store_->addVariable(p);
  }

  for (const auto& p: this->pkb.expression_store_->retrieveConstantsOfTheExpression(expression)) {
    this->pkb.entity_store_->addConstant(p);
  }
}

