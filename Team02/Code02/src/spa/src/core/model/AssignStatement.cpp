#include "AssignStatement.h"

AssignStatement::AssignStatement(std::string var_name,
                                 int stmt_number,
                                 std::string in_scope_of_proc)
    : var_name_(std::move(var_name)),
      Statement(stmt_number, "assign", std::move(in_scope_of_proc)) {}
