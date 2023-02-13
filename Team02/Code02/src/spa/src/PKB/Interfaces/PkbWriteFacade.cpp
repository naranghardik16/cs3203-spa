#include <utility>

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
  this->pkb.uses_store_->addStatementUsingVariable(std::move(statement_number), std::move(variable));
}

void PkbWriteFacade::AddProcedureUsingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) const {
  this->pkb.uses_store_->addProcedureUsingVariable(std::move(procedure), std::move(variable));
}

void PkbWriteFacade::AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                   PkbTypes::VARIABLE variable) const {
  this->pkb.modifies_store_->addStatementModifyingVariable(std::move(statement_number), std::move(variable));
}

void PkbWriteFacade::AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) const {
  this->pkb.modifies_store_->addProcedureModifyingVariable(std::move(procedure), std::move(variable));
}

void PkbWriteFacade::AddFollowsRelation(PkbTypes::STATEMENT_NUMBER first_statement,
                                        PkbTypes::STATEMENT_NUMBER second_statement) const {
  this->pkb.follows_store_->addFollowsRelation(std::move(first_statement), std::move(second_statement));
}

