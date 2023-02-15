#pragma once
#include "AbstractionExtractor.h"

AbstractionExtractor::AbstractionExtractor(PKB *pkb) : pkb_(pkb) {
  pkb_write_facade_ = new PkbWriteFacade(*pkb);
}

void AbstractionExtractor::VisitAssignStatement(AssignStatement *assign_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(assign_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   assign_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitPrintStatement(PrintStatement *print_statement) {
  // TODO: Abstractions other than Modifies
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(print_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, PRINT);
}

void AbstractionExtractor::VisitReadStatement(ReadStatement *read_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(read_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, READ);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   read_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitIfStatement(IfStatement *if_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(if_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, IF);
  IfStatement::StmtListContainer then_stmts = if_statement->GetThenStatements();
  ProcessStatements(then_stmts);
  IfStatement::StmtListContainer else_stmts = if_statement->GetElseStatements();
  ProcessStatements(else_stmts);
}

void AbstractionExtractor::ProcessStatements(vector<Statement*> statements) {
  Statement *prev_stmt = nullptr;
  for (Statement *s : statements) {
    if (prev_stmt != nullptr) {
      this->ExtractFollows(prev_stmt, s);
    }
    s->Accept(this);
    prev_stmt = s;
  }
}

void AbstractionExtractor::VisitWhileStatement(WhileStatement *while_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(while_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, WHILE);
  WhileStatement::StmtListContainer statements = while_statement->GetLoopStatements();
  ProcessStatements(statements);
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

void AbstractionExtractor::ExtractFollows(Statement* prev_stmt, Statement* curr_stmt) {
  PkbTypes::STATEMENT_NUMBER
      prev_stmt_no = std::to_string(prev_stmt->GetStatementNumber());
  PkbTypes::STATEMENT_NUMBER
      curr_stmt_no = std::to_string(curr_stmt->GetStatementNumber());
  pkb_write_facade_->AddFollowsRelation(prev_stmt_no, curr_stmt_no);
}