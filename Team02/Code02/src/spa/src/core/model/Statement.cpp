#pragma once
#include "Statement.h"

Statement::Statement(int stmt_number,
                     std::string statement_type,
                     std::string in_scope_of_proc)
    : statement_number_(stmt_number),
      statement_type_(std::move(statement_type)),
      in_scope_of_proc_(std::move(in_scope_of_proc)) {}

std::string Statement::GetStatementType() const {
  return statement_type_;
}

std::string Statement::GetInScopeOfPrc() const {
  return in_scope_of_proc_;
}