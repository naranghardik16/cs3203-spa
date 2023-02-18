#pragma once

#include "Statement.h"
#include "ConditionalOperation.h"

class WhileStatement : public Statement {
 public:
  typedef std::vector<Statement *> StmtListContainer;
  WhileStatement(int statement_number,
                 ConditionalOperation condition,
                 std::string in_scope_of_proc);
  ~WhileStatement() noexcept override;
  void AddStatement(Statement *stmt);
  void Accept(ParserVisitor *visitor);
  [[nodiscard]] ConditionalOperation GetCondition() const;
  [[nodiscard]] StmtListContainer GetLoopStatements() const;

 private:
  ConditionalOperation condition_;
  StmtListContainer loop_statements_;
};