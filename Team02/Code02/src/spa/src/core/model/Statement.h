#pragma once
#include<string>

class Statement {
 public:
  Statement(int line_number, std::string statement_type, std::string in_scope_of_proc);

  [[nodiscard]] std::string GetStatementType();
  [[nodiscard]] std::string GetInScopeOfPrc();

 private:
  int line_number_;
  std::string statement_type_;
  std::string in_scope_of_proc_;
};