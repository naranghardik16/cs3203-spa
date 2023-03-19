#include "EntityStore.h"

EntityStore::EntityStore() = default;

EntityStore::~EntityStore() = default;

EntityStore::Index EntityStore::AddVariable(const Variable& variable) {
  this->variable_store_.insert(variable, this->variable_store_.length() + 1);
  return this->variable_store_.length();
}

EntityStore::Index EntityStore::AddProcedure(const Procedure& procedure) {
  this->procedure_store_.insert(procedure, this->procedure_store_.length() + 1);
  return this->procedure_store_.length();
}

EntityStore::Index EntityStore::AddConstant(const Constant& constant) {
  this->constant_store_.insert(constant, this->constant_store_.length() + 1);
  return this->constant_store_.length();
}

EntityStore::VariableSet EntityStore::GetVariables() {
  return this->variable_store_.retrieveAllKeys();
}

EntityStore::ProcedureSet EntityStore::GetProcedures() {
  return this->procedure_store_.retrieveAllKeys();
}

EntityStore::ConstantSet EntityStore::GetConstants() {
  return this->constant_store_.retrieveAllKeys();
}

