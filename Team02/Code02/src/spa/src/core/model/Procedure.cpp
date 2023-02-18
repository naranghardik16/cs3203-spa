#pragma once
#include "Procedure.h"

Procedure::Procedure(std::string proc_name) : procedure_name_(std::move(
    proc_name)), statement_list_({}) {}

Procedure::~Procedure() noexcept {
  for (auto stmt : statement_list_) {
    delete stmt;
  }
  statement_list_.clear();
}

void Procedure::AddToStatementList(Statement *stmt) {
  statement_list_.push_back(stmt);
}

Procedure::StmtListContainer Procedure::GetStatementList() const {
  return statement_list_;
}

std::string Procedure::GetProcedureName() const {
  return procedure_name_;
}

void Procedure::Accept(ParserVisitor *visitor) {
  visitor->VisitProcedure(this);
}