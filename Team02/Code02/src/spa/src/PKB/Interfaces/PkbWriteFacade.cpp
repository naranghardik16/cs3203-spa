#include "PkbWriteFacade.h"
#include "PKB/PKB.h"


PkbWriteFacade::PkbWriteFacade(PKB& pkb): pkb(pkb) {}

PkbWriteFacade::~PkbWriteFacade() {}

PkbTypes::VARIABLE_STORE_INDEX PkbWriteFacade::addVariable(PkbTypes::VARIABLE variable) {
  return pkb.entity_store_->addVariable(variable);
}

PkbTypes::PROCEDURE_STORE_INDEX PkbWriteFacade::addProcedure(PkbTypes::PROCEDURE procedure) {
  return pkb.entity_store_->addProcedure(procedure);
}

void PkbWriteFacade::addConstant(PkbTypes::CONSTANT constant) {
  pkb.entity_store_->addConstant(constant);
}



