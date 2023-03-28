#include "AbstractionExtractor.h"

AbstractionExtractor::AbstractionExtractor(shared_ptr<Pkb> pkb) : pkb_(pkb) {
  pkb_write_facade_ = make_shared<PkbWriteFacade>(*pkb);
  pkb_read_facade_ = make_shared<PkbReadFacade>(*pkb);
  is_extract_indirect_modifies_and_uses_ = make_shared<bool>(false);
}

void AbstractionExtractor::VisitArithmeticalOperation(shared_ptr<
    ArithmeticOperation> arith_operation) {
  // TODO(xxx): xxx:
}

void AbstractionExtractor::VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) {
  auto expression = assign_statement->GetExpression();

  if (*is_extract_indirect_modifies_and_uses_) {
    ExtractIndirectModifies(assign_statement->GetVariable().GetName(), assign_statement->GetInScopeOfPrc());
    for (auto variable : pkb_read_facade_->RetrieveAllVariablesOfExpression(expression)) {
      // for direct uses
      pkb_write_facade_->AddProcedureUsingVariable(assign_statement->GetInScopeOfPrc(), variable);
      ExtractIndirectUses(variable, assign_statement->GetInScopeOfPrc());
    }
    return;
  }

  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(assign_statement->GetStatementNumber());

  pkb_write_facade_->AddStatementOfAType(stmt_number, ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   assign_statement->GetVariable().GetName());
  pkb_write_facade_->AddAssignmentStatementAndExpression(stmt_number,
                                                         expression);
  pkb_write_facade_->AddProcedureModifyingVariable(assign_statement->GetInScopeOfPrc(),
                                                   assign_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitConditionalOperation(shared_ptr<
    ConditionalOperation> cond_operation) {
  // TODO(xxx): xxx:
  if (*is_extract_indirect_modifies_and_uses_) {
    return;
  }
}

void AbstractionExtractor::VisitPrintStatement(shared_ptr<PrintStatement> print_statement) {
  if (*is_extract_indirect_modifies_and_uses_) {
    // for direct uses
    pkb_write_facade_->AddProcedureUsingVariable(print_statement->GetInScopeOfPrc(),
                                                 print_statement->GetVariable().GetName());
    ExtractIndirectUses(print_statement->GetVariable().GetName(), print_statement->GetInScopeOfPrc());
    return;
  }

  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(print_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, PRINT);
  pkb_write_facade_->AddStatementUsingVariable(stmt_number,
                                               print_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitReadStatement(shared_ptr<ReadStatement> read_statement) {
  if (*is_extract_indirect_modifies_and_uses_) {
    ExtractIndirectModifies(read_statement->GetVariable().GetName(), read_statement->GetInScopeOfPrc());
    return;
  }

  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(read_statement->GetStatementNumber());

  pkb_write_facade_->AddStatementOfAType(stmt_number, READ);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   read_statement->GetVariable().GetName());
  pkb_write_facade_->AddProcedureModifyingVariable(read_statement->GetInScopeOfPrc(),
                                                   read_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitCallStatement(shared_ptr<CallStatement> call_statement) {
  if (*is_extract_indirect_modifies_and_uses_) {
    return;
  }
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(call_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, CALL);
  pkb_write_facade_->AddCallStatementToProcedureName(stmt_number, call_statement->GetProcedureName());
  pkb_write_facade_->AddCallsRelation(call_statement->GetInScopeOfPrc(), call_statement->GetProcedureName());
}

void AbstractionExtractor::VisitRelationalOperation(shared_ptr<
    RelationalOperation> rel_operation) {
  if (*is_extract_indirect_modifies_and_uses_) {
    return;
  }
}

void AbstractionExtractor::VisitIfStatement(shared_ptr<IfStatement> if_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(if_statement->GetStatementNumber());
  auto condition = if_statement->GetCondition();
  if (!*is_extract_indirect_modifies_and_uses_) {
    pkb_write_facade_->AddStatementOfAType(stmt_number, IF);
    pkb_write_facade_->AddIfStatementAndCondition(stmt_number, condition);
  }

  for (auto variable : pkb_read_facade_->RetrieveAllVariablesOfExpression(condition)) {
    if (*is_extract_indirect_modifies_and_uses_) {
      ExtractIndirectUses(variable, if_statement->GetInScopeOfPrc());
    } else {
      // for direct uses
      pkb_write_facade_->AddProcedureUsingVariable(if_statement->GetInScopeOfPrc(), variable);
    }
  }
  IfStatement::StmtListContainer then_stmts = if_statement->GetThenStatements();
  ProcessStatements(then_stmts, stmt_number);
  IfStatement::StmtListContainer else_stmts = if_statement->GetElseStatements();
  ProcessStatements(else_stmts, stmt_number);
}

void AbstractionExtractor::ProcessStatements(const vector<shared_ptr<Statement>> &statements,
                                             PkbTypes::STATEMENT_NUMBER parent) {
  if (*is_extract_indirect_modifies_and_uses_) {
    for (shared_ptr<Statement> s : statements) {
      s->Accept(make_shared<AbstractionExtractor>(*this));
    }
    return;
  }

  shared_ptr<Statement> prev_stmt = nullptr;
  for (shared_ptr<Statement> s : statements) {
    if (prev_stmt != nullptr) {
      this->ExtractFollows(prev_stmt, s);
    }
    this->ExtractParent(parent, s);
    s->Accept(make_shared<AbstractionExtractor>(*this));
    prev_stmt = s;
  }
}

void AbstractionExtractor::VisitWhileStatement(shared_ptr<WhileStatement> while_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(while_statement->GetStatementNumber());
  auto condition = while_statement->GetCondition();
  if (!*is_extract_indirect_modifies_and_uses_) {
    pkb_write_facade_->AddStatementOfAType(stmt_number, WHILE);
    pkb_write_facade_->AddWhileStatementAndCondition(stmt_number, condition);
  }

  for (auto variable : pkb_read_facade_->RetrieveAllVariablesOfExpression(condition)) {
    if (*is_extract_indirect_modifies_and_uses_) {
      ExtractIndirectUses(variable, while_statement->GetInScopeOfPrc());
    } else {
      // for direct uses
      pkb_write_facade_->AddProcedureUsingVariable(while_statement->GetInScopeOfPrc(), variable);
    }
  }
  WhileStatement::StmtListContainer
      statements = while_statement->GetLoopStatements();
  ProcessStatements(statements, stmt_number);
}

void AbstractionExtractor::VisitProcedure(shared_ptr<Procedure> procedure) {
  // TODO(xxx): xxx:
}

void AbstractionExtractor::VisitConstant(shared_ptr<Constant> constant) {
  // TODO(xxx): xxx:
}

void AbstractionExtractor::VisitVariable(shared_ptr<Variable> variable) {
  // TODO(xxx): xxx:
}

void AbstractionExtractor::ExtractFollows(shared_ptr<Statement> prev_stmt,
                                          shared_ptr<Statement> curr_stmt) {
  PkbTypes::STATEMENT_NUMBER
      prev_stmt_no = std::to_string(prev_stmt->GetStatementNumber());
  PkbTypes::STATEMENT_NUMBER
      curr_stmt_no = std::to_string(curr_stmt->GetStatementNumber());
  pkb_write_facade_->AddFollowsRelation(prev_stmt_no, curr_stmt_no);
}

void AbstractionExtractor::ExtractParent(PkbTypes::STATEMENT_NUMBER parent,
                                         shared_ptr<Statement> child_stmt
) {
  PkbTypes::STATEMENT_NUMBER
      child_stmt_no = std::to_string(child_stmt->GetStatementNumber());
  pkb_write_facade_->AddParentRelation(parent, child_stmt_no);
}

void AbstractionExtractor::ExtractIndirectModifies(PkbTypes::VARIABLE variable, PkbTypes::PROCEDURE stmt_proc) {
  auto callers = pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee(stmt_proc);
  for (pair<string, string> c : callers) {
    pkb_write_facade_->AddProcedureModifyingVariable(c.first, variable);
    ExtractIndirectModifiesFromCallStatements(c.first, variable);
  }
  ExtractIndirectModifiesFromCallStatements(stmt_proc, variable);
}

void AbstractionExtractor::ExtractIndirectModifiesFromCallStatements(PkbTypes::PROCEDURE curr_proc,
                                                                     PkbTypes::VARIABLE variable) {
  // gets all the call statements that called the procedure where procedure = curr_proc
  auto call_stmts = pkb_read_facade_->GetAllCallStatementsFromAProcedure(curr_proc);
  for (auto call_stmt_no : call_stmts) {
    pkb_write_facade_->AddStatementModifyingVariable(call_stmt_no, variable);
  }
}

void AbstractionExtractor::ExtractIndirectUses(PkbTypes::VARIABLE variable, PkbTypes::PROCEDURE stmt_proc) {
  auto callers = pkb_read_facade_->GetAllCallsStarPairsWithSpecifiedCallee(stmt_proc);
  for (pair<string, string> c : callers) {
    pkb_write_facade_->AddProcedureUsingVariable(c.first, variable);
    ExtractIndirectUsesFromCallStatements(c.first, variable);
  }
  ExtractIndirectUsesFromCallStatements(stmt_proc, variable);
}

void AbstractionExtractor::ExtractIndirectUsesFromCallStatements(PkbTypes::PROCEDURE curr_proc,
                                                                 PkbTypes::VARIABLE variable) {
  // gets all the call statements that called the procedure where procedure = curr_proc
  auto call_stmts = pkb_read_facade_->GetAllCallStatementsFromAProcedure(curr_proc);
  for (auto call_stmt_no : call_stmts) {
    pkb_write_facade_->AddStatementUsingVariable(call_stmt_no, variable);
  }
}

void AbstractionExtractor::SetIsExtractIndirectModifiesAndUsesTrue() {
  is_extract_indirect_modifies_and_uses_ = make_shared<bool>(true);
}
