#pragma once

#include "Statement.h"
#include "ConditionalOperation.h"

class IfStatement : public Statement, public enable_shared_from_this<IfStatement> {
 public:
  typedef std::vector<shared_ptr<Statement>> StmtListContainer;
  IfStatement(int statement_number,
              ConditionalOperation condition,
              std::string in_scope_of_proc);
  ~IfStatement() noexcept override;
  void AddThenStmtList(shared_ptr<Statement> statement);
  void AddElseStmtList(shared_ptr<Statement> statement);
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  [[nodiscard]] ConditionalOperation GetCondition() const;
  [[nodiscard]] StmtListContainer GetThenStatements() const;
  [[nodiscard]] StmtListContainer GetElseStatements() const;

 private:
  ConditionalOperation condition_;
  StmtListContainer then_statements_;
  StmtListContainer else_statements_;
};