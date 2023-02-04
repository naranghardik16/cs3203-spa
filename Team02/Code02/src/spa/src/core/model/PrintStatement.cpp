#include "PrintStatement.h"

PrintStatement::PrintStatement(int statement_number,
                               Variable var,
                               std::string in_scope_proc) : variable_(std::move(
    var)),
                                                            Statement(
                                                                statement_number,
                                                                "print",
                                                                in_scope_proc) {}

Variable PrintStatement::GetVariable() const {
  return variable_;
}