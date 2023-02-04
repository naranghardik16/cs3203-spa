#pragma once
#include "EntityExtractor.h"

EntityExtractor::EntityExtractor() {}

void EntityExtractor::VisitProcedure(Procedure *procedure) {
  PkbTypes::PROCEDURE p = procedure->GetProcedureName();
  pkb_write_facade_->AddProcedure(p);
}

void EntityExtractor::VisitConstant(Constant *constant) {
  PkbTypes::CONSTANT const_val = constant->GetName();
  pkb_write_facade_->AddConstant(const_val);
}

void EntityExtractor::VisitVariable(Variable *variable) {
  PkbTypes::VARIABLE var_name = variable->GetName();
  pkb_write_facade_->AddVariable(var_name);
}