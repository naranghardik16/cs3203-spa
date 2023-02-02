#include "PkbReadFacade.h"
#include "PKB/PKB.h"

PkbReadFacade::PkbReadFacade(PKB& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() {}

KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX>  &PkbReadFacade::getVariableStore() {
  return PKB::entity_store_->getVariableStore();
}

KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> &PkbReadFacade::getProcedureStore() {
  return PKB::entity_store_->getProcedureStore();
}

std::unordered_set<PkbTypes::CONSTANT> &PkbReadFacade::getConstantStore() {
  return PKB::entity_store_->getConstantStore();
}

