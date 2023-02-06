#pragma once
#include "AbstractionExtractor.h"

AbstractionExtractor::AbstractionExtractor(PKB *pkb) : pkb_(pkb) {
  pkb_write_facade_ = new PkbWriteFacade(*pkb);
}

void AbstractionExtractor::VisitAssignStatement(AssignStatement *assign_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(assign_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   assign_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitPrintStatement(PrintStatement *print_statement) {
  // TODO: Abstractions other than Modifies
}

void AbstractionExtractor::VisitReadStatement(ReadStatement *read_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(read_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   read_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitProcedure(Procedure *procedure) {
  // TODO:
}

void AbstractionExtractor::VisitConstant(Constant *constant) {
  // TODO:
}

void AbstractionExtractor::VisitVariable(Variable *variable) {
  // TODO:
}