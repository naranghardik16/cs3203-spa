#include "AbstractionExtractor.h"

AbstractionExtractor::AbstractionExtractor(shared_ptr<PKB> pkb) : pkb_(pkb) {
  pkb_write_facade_ = make_shared<PkbWriteFacade>(*pkb);
}

void AbstractionExtractor::VisitArithmeticalOperation(shared_ptr<ArithmeticOperation> arith_operation) {
  // TODO:
}

void AbstractionExtractor::VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(assign_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   assign_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitConditionalOperation(shared_ptr<ConditionalOperation> cond_operation) {
  // TODO:
}

void AbstractionExtractor::VisitPrintStatement(shared_ptr<PrintStatement> print_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(print_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, PRINT);
  pkb_write_facade_->AddStatementUsingVariable(stmt_number,
                                               print_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitReadStatement(shared_ptr<ReadStatement> read_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(read_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, READ);
  pkb_write_facade_->AddStatementModifyingVariable(stmt_number,
                                                   read_statement->GetVariable().GetName());
}

void AbstractionExtractor::VisitRelationalOperation(shared_ptr<RelationalOperation> rel_operation) {

}

void AbstractionExtractor::VisitIfStatement(shared_ptr<IfStatement> if_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(if_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, IF);
  IfStatement::StmtListContainer then_stmts = if_statement->GetThenStatements();
  ProcessStatements(then_stmts, stmt_number);
  IfStatement::StmtListContainer else_stmts = if_statement->GetElseStatements();
  ProcessStatements(else_stmts, stmt_number);
}

void AbstractionExtractor::ProcessStatements(const vector<shared_ptr<Statement>> &statements,
                                             PkbTypes::STATEMENT_NUMBER parent) {
  shared_ptr<Statement> prev_stmt = nullptr;
  for (shared_ptr<Statement> s : statements) {
    if (prev_stmt != nullptr) {
      this->ExtractFollows(prev_stmt, s);
    }
    this->ExtractParent(parent, s);
    s->Accept(shared_from_this());
    prev_stmt = s;
  }
}

void AbstractionExtractor::VisitWhileStatement(shared_ptr<WhileStatement> while_statement) {
  PkbTypes::STATEMENT_NUMBER
      stmt_number = std::to_string(while_statement->GetStatementNumber());
  pkb_write_facade_->AddStatementOfAType(stmt_number, WHILE);
  // TODO: Add uses for conditionOperation
  WhileStatement::StmtListContainer
      statements = while_statement->GetLoopStatements();
  ProcessStatements(statements, stmt_number);
}

void AbstractionExtractor::VisitProcedure(shared_ptr<Procedure> procedure) {
  // TODO:
}

void AbstractionExtractor::VisitConstant(shared_ptr<Constant> constant) {
  // TODO:
}

void AbstractionExtractor::VisitVariable(shared_ptr<Variable> variable) {
  // TODO:
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
