#pragma once

#include "Statement.h"
#include "Variable.h"

class PrintStatement : public Statement, public enable_shared_from_this<PrintStatement> {
 public:
  PrintStatement(int statement_number, Variable var, std::string in_scope_proc);
  ~PrintStatement() = default;
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  [[nodiscard]] Variable GetVariable() const;

 private:
  Variable variable_;
};