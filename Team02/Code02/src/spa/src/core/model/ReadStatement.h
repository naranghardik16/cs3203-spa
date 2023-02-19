#pragma once

#include "Statement.h"
#include "Variable.h"

class ReadStatement : public Statement {
 public:
  ReadStatement(int statement_number, Variable var, std::string in_scope_proc);
  ~ReadStatement() = default;
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  [[nodiscard]] Variable GetVariable() const;

 private:
  Variable variable_;
};