#pragma once
#include "Procedure.h"

Procedure::Procedure(std::string proc_name) : procedure_name_(std::move(
    proc_name)), statement_list_({}) {}

void Procedure::AddToStatementList(Statement *stmt) {
  this->statement_list_.push_back(stmt);
}

Procedure::StmtListContainer Procedure::GetStatementList() const {
  return this->statement_list_;
}

std::string Procedure::GetProcedureName() const {
  return this->procedure_name_;
}