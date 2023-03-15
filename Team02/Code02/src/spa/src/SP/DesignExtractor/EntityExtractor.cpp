#pragma once
#include "EntityExtractor.h"

EntityExtractor::EntityExtractor(shared_ptr<PKB> pkb) {
  pkb_ = pkb;
  pkb_write_facade_ = make_shared<PkbWriteFacade>(*pkb);
}

void EntityExtractor::ProcessStatements(const vector<shared_ptr<Statement>> &statements) {
  for (auto stmt : statements) {
    stmt->Accept(make_shared<EntityExtractor>(*this));
  }
}

void EntityExtractor::VisitArithmeticalOperation(shared_ptr<ArithmeticOperation> arith_operation) {
  auto arguments = arith_operation->GetArguments();
  auto &[lhs, rhs] = *arguments;
  if (lhs) {
    lhs->Accept(make_shared<EntityExtractor>(*this));
  }
  if (rhs) {
    rhs->Accept(make_shared<EntityExtractor>(*this));
  }
}

void EntityExtractor::VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) {
  PkbTypes::VARIABLE var_name = assign_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitConditionalOperation(shared_ptr<ConditionalOperation> cond_operation) {
  auto arguments = cond_operation->GetArguments();
  auto &[lhs, rhs] = *arguments;
  if (lhs) {
    lhs->Accept(make_shared<EntityExtractor>(*this));
  }
  if (rhs) {
    rhs->Accept(make_shared<EntityExtractor>(*this));
  }
}

void EntityExtractor::VisitPrintStatement(shared_ptr<PrintStatement> print_statement) {
  PkbTypes::VARIABLE var_name = print_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitRelationalOperation(shared_ptr<RelationalOperation> rel_operation) {
  auto arguments = rel_operation->GetArguments();
  auto &[lhs, rhs] = *arguments;
  if (lhs) {
    lhs->Accept(make_shared<EntityExtractor>(*this));
  }
  if (rhs) {
    rhs->Accept(make_shared<EntityExtractor>(*this));
  }
}

void EntityExtractor::VisitReadStatement(shared_ptr<ReadStatement> read_statement) {
  PkbTypes::VARIABLE var_name = read_statement->GetVariable().GetName();
  pkb_write_facade_->AddVariable(var_name);
}

void EntityExtractor::VisitCallStatement(shared_ptr<CallStatement> call_statement) {
  // TODO(xxx): xxx:
}

void EntityExtractor::VisitIfStatement(shared_ptr<IfStatement> if_statement) {
  auto condition = if_statement->GetCondition();
  condition.Accept(make_shared<EntityExtractor>(*this));
  auto then_stmt_list = if_statement->GetThenStatements();
  auto else_stmt_list = if_statement->GetElseStatements();
  ProcessStatements(then_stmt_list);
  ProcessStatements(else_stmt_list);
}

void EntityExtractor::VisitWhileStatement(shared_ptr<WhileStatement> while_statement) {
  auto condition = while_statement->GetCondition();
  condition.Accept(make_shared<EntityExtractor>(*this));
  auto loop_stmt_list = while_statement->GetLoopStatements();
  ProcessStatements(loop_stmt_list);
}

void EntityExtractor::VisitProcedure(shared_ptr<Procedure> procedure) {
  PkbTypes::PROCEDURE p = procedure->GetProcedureName();
  pkb_write_facade_->AddProcedure(p);
}

void EntityExtractor::VisitConstant(shared_ptr<Constant> constant) {
  PkbTypes::CONSTANT const_val = constant->GetName();
  pkb_write_facade_->AddConstant(const_val);
}

void EntityExtractor::VisitVariable(shared_ptr<Variable> variable) {
  PkbTypes::VARIABLE var_name = variable->GetName();
  pkb_write_facade_->AddVariable(var_name);
}
