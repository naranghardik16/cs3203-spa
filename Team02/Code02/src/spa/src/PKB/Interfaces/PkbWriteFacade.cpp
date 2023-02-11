#include "PkbWriteFacade.h"

#include <utility>
#include "PKB/PKB.h"


PkbWriteFacade::PkbWriteFacade(PKB& pkb): pkb(pkb) {}

PkbWriteFacade::~PkbWriteFacade() {}

PkbTypes::INDEX PkbWriteFacade::AddVariable(PkbTypes::VARIABLE variable) {
  return pkb.entity_store_->addVariable(std::move(variable));
}

PkbTypes::INDEX PkbWriteFacade::AddProcedure(PkbTypes::PROCEDURE procedure) {
  return pkb.entity_store_->addProcedure(std::move(procedure));
}

PkbTypes::INDEX PkbWriteFacade::AddConstant(PkbTypes::CONSTANT constant) {
  return pkb.entity_store_->addConstant(std::move(constant));
}

void PkbWriteFacade::AddStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                   PkbTypes::VARIABLE variable) {
  this->pkb.modifies_store_->addStatementModifyingVariable(statement_number, variable);
}

void PkbWriteFacade::AddProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable) {
  this->pkb.modifies_store_->addProcedureModifyingVariable(procedure, variable);
}

void PkbWriteFacade::AddFollowsRelation(PkbTypes::STATEMENT_NUMBER statement_number_1,
                                        PkbTypes::STATEMENT_NUMBER statement_number_2) {
  this->pkb.follows_store_->addFollowsRelation(statement_number_1, statement_number_2);
}



