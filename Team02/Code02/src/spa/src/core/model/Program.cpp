#pragma once
#include "Program.h"

Program::Program() : procedure_list_({}) {}

void Program::AddToProcedureList(Procedure *proc) {
  procedure_list_.push_back(proc);
}

Program::ProcListContainer Program::GetProcedureList() {
  return procedure_list_;
}