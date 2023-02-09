#pragma once

#include "Statement.h"
#include "ConditionalOperation.h"

class IfStatement : public Statement {
 public:
  typedef std::vector<Statement *> StmtListContainer;
  IfStatement(int statement_number,
              ConditionalOperation condition,
              std::string in_scope_of_proc);
  void AddThenStmtList(Statement *statement);
  void AddElseStmtList(Statement *statement);
  void Accept(ParserVisitor *visitor) override;
  [[nodiscard]] ConditionalOperation GetCondition() const;
  [[nodiscard]] StmtListContainer GetThenStatements() const;
  [[nodiscard]] StmtListContainer GetElseStatements() const;

 private:
  ConditionalOperation condition_;
  StmtListContainer then_statements_;
  StmtListContainer else_statements_;
};