#include "PkbReadFacade.h"

#include <memory>
#include "PKB/PKB.h"

PkbReadFacade::PkbReadFacade(PKB& pkb): pkb(pkb) {}

PkbReadFacade::~PkbReadFacade() {}

KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX>  &PkbReadFacade::GetVariableStore() {
  return pkb.entity_store_->getVariableStore();
}

KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> &PkbReadFacade::GetProcedureStore() {
  return pkb.entity_store_->getProcedureStore();
}

std::unordered_set<PkbTypes::CONSTANT> &PkbReadFacade::GetConstantStore() {
  return pkb.entity_store_->getConstantStore();
}

std::unordered_set<std::string> PkbReadFacade::GetVariables() {
  std::unordered_set<std::string> variable_set({"a", "b", "c"});
  return variable_set;
}

std::unordered_set<std::string> PkbReadFacade::GetStatements() {
  std::unordered_set<std::string> statement_set({"1", "2", "3"});
  return statement_set;
}

std::unordered_set<std::string> PkbReadFacade::GetReadStatements() {
  std::unordered_set<std::string> read_set({"4", "5", "6"});
  return read_set;
}

std::unordered_set<std::string> PkbReadFacade::GetPrintStatements() {
  std::unordered_set<std::string> print_set({"6", "7", "8"});
  return print_set;
}

std::unordered_set<std::string> PkbReadFacade::GetCallStatements() {
  std::unordered_set<std::string> call_set({"9", "10", "11"});
  return call_set;
}

std::unordered_set<std::string> PkbReadFacade::GetWhileStatements() {
  std::unordered_set<std::string> while_set({"12", "13", "14"});
  return while_set;
}
std::unordered_set<std::string> PkbReadFacade::GetIfStatements() {
  std::unordered_set<std::string> if_set({"15", "16", "18"});
  return if_set;
}

std::unordered_set<std::string> PkbReadFacade::GetAssignStatements() {
  std::unordered_set<std::string> assign_set({"19", "20", "21"});
  return assign_set;
}

std::unordered_set<std::string> PkbReadFacade::GetConstants() {
  std::unordered_set<std::string> constant_set({"22", "23", "24"});
  return constant_set;
}

std::unordered_set<std::string> PkbReadFacade::GetProcedures() {
  std::unordered_set<std::string> p_set({"eval", "parse", "validate"});
  return p_set;
}