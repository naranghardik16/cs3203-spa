#pragma once
#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(PKB *pkb) {
  pkb_ = pkb;
  pkb_write_facade_ = new PkbWriteFacade(*pkb);
}

void EntityExtractor::ProcessStatements(const vector<Statement *> &statements) {
  for (auto *stmt : statements) {
    stmt->Accept(this);
  }
}

void EntityExtractor::VisitArithmeticalOperation(ArithmeticOperation *arith_operation) {
  auto arguments = arith_operation->GetArguments();
  auto &[lhs, rhs] = arguments;
  if (lhs) {
    lhs->Accept(this);
  }
  if (rhs) {
    rhs->Accept(this);
  }
}

void EntityExtractor::VisitAssignStatement(AssignStatement *assign_statement) {
  PkbTypes::VARIABLE var_name = assign_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitConditionalOperation(ConditionalOperation *cond_operation) {
  auto arguments = cond_operation->GetArguments();
  auto &[lhs, rhs] = arguments;
  if (lhs) {
    lhs->Accept(this);
  }
  if (rhs) {
    rhs->Accept(this);
  }
}

void EntityExtractor::VisitPrintStatement(PrintStatement *print_statement) {
  PkbTypes::VARIABLE var_name = print_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitRelationalOperation(RelationalOperation *rel_operation) {
  auto arguments = rel_operation->GetArguments();
  auto &[lhs, rhs] = arguments;
  if (lhs) {
    lhs->Accept(this);
  }
  if (rhs) {
    rhs->Accept(this);
  }
}

void EntityExtractor::VisitReadStatement(ReadStatement *read_statement) {
  PkbTypes::VARIABLE var_name = read_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitIfStatement(IfStatement *if_statement) {
  // TODO?
  auto condition = if_statement->GetCondition();
  condition.Accept(this);
  auto then_stmt_list = if_statement->GetThenStatements();
  auto else_stmt_list = if_statement->GetElseStatements();
  ProcessStatements(then_stmt_list);
  ProcessStatements(else_stmt_list);
}

void EntityExtractor::VisitWhileStatement(WhileStatement *while_statement) {
  // TODO?
  auto condition = while_statement->GetCondition();
  condition.Accept(this);
  auto loop_stmt_list = while_statement->GetLoopStatements();
  ProcessStatements(loop_stmt_list);
}

void EntityExtractor::VisitProcedure(Procedure *procedure) {
  PkbTypes::PROCEDURE p = procedure->GetProcedureName();
  pkb_write_facade_->AddProcedure(p);
}

void EntityExtractor::VisitConstant(Constant *constant) {
  PkbTypes::CONSTANT const_val = constant->GetName();
  pkb_write_facade_->AddConstant(const_val);
}

void EntityExtractor::VisitVariable(Variable *variable) {
  PkbTypes::VARIABLE var_name = variable->GetName();
  pkb_write_facade_->AddVariable(var_name);
}