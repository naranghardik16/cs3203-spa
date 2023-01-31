#pragma once
#include "Program.h"

Program::Program() : procedure_list_({}) {}

void Program::AddToProcedureList(Procedure *proc) {
  this->procedure_list_.push_back(proc);
}

Program::ProcListContainer Program::GetProcedureList() {
  return this->procedure_list_;
}