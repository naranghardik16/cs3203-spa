#pragma once
#include "Statement.h"

Statement::Statement(int line_number,
                     std::string statement_type,
                     std::string in_scope_of_proc)
    : line_number_(line_number),
      statement_type_(std::move(statement_type)),
      in_scope_of_proc_(std::move(in_scope_of_proc)) {}

std::string Statement::GetStatementType() const {
  return this->statement_type_;
}

std::string Statement::GetInScopeOfPrc() const {
  return this->in_scope_of_proc_;
}