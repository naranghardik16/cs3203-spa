#include "EntityStore.h"

EntityStore::EntityStore() = default;

EntityStore::~EntityStore() = default;

PkbTypes::INDEX EntityStore::addVariable(PkbTypes::VARIABLE variable) {
  variable_store_.insert(std::move(variable), variable_store_.length() + 1);
  return 1;
}

PkbTypes::INDEX EntityStore::addProcedure(PkbTypes::PROCEDURE procedure) {
  procedure_store_.insert(std::move(procedure), procedure_store_.length() + 1);
  return 1;
}

PkbTypes::INDEX EntityStore::addConstant(PkbTypes::CONSTANT constant) {
  constant_store_.insert(std::move(constant), constant_store_.length() + 1);
  return 1;
}

std::unordered_set<PkbTypes::VARIABLE> EntityStore::getVariables() {
  return variable_store_.retrieveAllKeys();
}

std::unordered_set<PkbTypes::PROCEDURE> EntityStore::getProcedures() {
  return procedure_store_.retrieveAllKeys();
}

std::unordered_set<PkbTypes::CONSTANT> EntityStore::getConstants() {
  return constant_store_.retrieveAllKeys();
}

