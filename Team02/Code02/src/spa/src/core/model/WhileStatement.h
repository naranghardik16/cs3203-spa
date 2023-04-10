#pragma once

#include "Statement.h"
#include "ConditionalOperation.h"

class WhileStatement : public Statement {
 public:
  typedef std::vector<shared_ptr<Statement>> StmtListContainer;
  WhileStatement(int statement_number,
                 shared_ptr<ConditionalOperation> condition,
                 std::string in_scope_of_proc);
  ~WhileStatement() noexcept override;
  void AddStatement(shared_ptr<Statement> stmt);
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  [[nodiscard]] shared_ptr<ConditionalOperation> GetCondition() const;
  [[nodiscard]] StmtListContainer GetLoopStatements() const;

 private:
  shared_ptr<ConditionalOperation> condition_;
  StmtListContainer loop_statements_;
};