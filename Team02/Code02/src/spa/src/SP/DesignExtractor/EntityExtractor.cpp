#pragma once
#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(PKB *pkb) {
  pkb_ = pkb;
  pkb_write_facade_ = new PkbWriteFacade(*pkb);
}

void EntityExtractor::VisitAssignStatement(AssignStatement *assign_statement) {
  PkbTypes::VARIABLE var_name = assign_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitPrintStatement(PrintStatement *print_statement) {
  PkbTypes::VARIABLE var_name = print_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitReadStatement(ReadStatement *read_statement) {
  PkbTypes::VARIABLE var_name = read_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

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