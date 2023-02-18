#pragma once
#include "Program.h"

int Program::statement_number_ = 1;

Program::Program() : procedure_list_({}) { statement_number_ = 1; }

Program::~Program() {
  for (auto proc : procedure_list_) {
    delete proc;
  }
  procedure_list_.clear();
}

void Program::AddToProcedureList(Procedure *proc) {
  procedure_list_.push_back(proc);
}

Program::ProcListContainer Program::GetProcedureList() {
  return procedure_list_;
}

int Program::GetAndIncreaseStatementNumber() {
  return statement_number_++;
}