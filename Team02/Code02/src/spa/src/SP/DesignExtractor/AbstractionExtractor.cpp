#pragma once
#include "AbstractionExtractor.h"

AbstractionExtractor::AbstractionExtractor(PKB *pkb) : pkb_(pkb) {
  pkb_write_facade_ = new PkbWriteFacade(*pkb);
}

void AbstractionExtractor::VisitArithmeticalOperation(ArithmeticOperation *arith_operation) {
  // TODO:
}

void AbstractionExtractor::VisitAssignStatement(AssignStatement *assign_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(assign_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   assign_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitConditionalOperation(ConditionalOperation *cond_operation) {
  // TODO:
}

void AbstractionExtractor::VisitPrintStatement(PrintStatement *print_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(print_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, PRINT);
  pkb_write_facade_->AddStatementUsingVariable(stmt_number,
                                               print_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitReadStatement(ReadStatement *read_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(read_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, READ);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   read_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitRelationalOperation(RelationalOperation *rel_operation) {
  
}

void AbstractionExtractor::VisitIfStatement(IfStatement *if_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(if_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, IF);
  IfStatement::StmtListContainer then_stmts = if_statement->GetThenStatements();
  ProcessStatements(then_stmts, stmt_number);
  IfStatement::StmtListContainer else_stmts = if_statement->GetElseStatements();
  ProcessStatements(else_stmts, stmt_number);
}

void AbstractionExtractor::ProcessStatements(const vector<Statement *> &statements,
                                             PkbTypes::STATEMENT_NUMBER parent) {
  Statement *prev_stmt = nullptr;
  for (Statement *s : statements) {
    if (prev_stmt != nullptr) {
      this->ExtractFollows(prev_stmt, s);
      this->ExtractParent(s, parent);
    }
    s->Accept(this);
    prev_stmt = s;
  }
}

void AbstractionExtractor::VisitWhileStatement(WhileStatement *while_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(while_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, WHILE);
  // TODO: Add uses for conditionOperation
  WhileStatement::StmtListContainer
      statements = while_statement->GetLoopStatements();
  ProcessStatements(statements, stmt_number);
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

void AbstractionExtractor::ExtractFollows(Statement *prev_stmt,
                                          Statement *curr_stmt) {
  PkbTypes::STATEMENT_NUMBER
      prev_stmt_no = std::to_string(prev_stmt->GetStatementNumber());
  PkbTypes::STATEMENT_NUMBER
      curr_stmt_no = std::to_string(curr_stmt->GetStatementNumber());
  pkb_write_facade_->AddFollowsRelation(prev_stmt_no, curr_stmt_no);
}

void AbstractionExtractor::ExtractParent(Statement *child_stmt,
                                         PkbTypes::STATEMENT_NUMBER parent) {
  PkbTypes::STATEMENT_NUMBER
      child_stmt_no = std::to_string(child_stmt->GetStatementNumber());
  pkb_write_facade_->AddParentRelation(parent, child_stmt_no);
}
