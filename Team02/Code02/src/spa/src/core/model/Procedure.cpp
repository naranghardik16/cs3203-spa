#pragma once
#include "Procedure.h"

Procedure::Procedure(std::string proc_name) : procedure_name_(std::move(
    proc_name)), statement_list_({}) {}

Procedure::~Procedure() noexcept {
  statement_list_.clear();
}

void Procedure::AddToStatementList(shared_ptr<Statement> stmt) {
  statement_list_.push_back(stmt);
}

Procedure::StmtListContainer Procedure::GetStatementList() const {
  return statement_list_;
}

std::string Procedure::GetProcedureName() const {
  return procedure_name_;
}

void Procedure::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitProcedure(make_shared<Procedure>(*this));
}