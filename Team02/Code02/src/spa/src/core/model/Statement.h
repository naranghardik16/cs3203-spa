#pragma once
#include<string>

class Statement {
 public:
  Statement(int stmt_number,
            std::string statement_type,
            std::string in_scope_of_proc);

  [[nodiscard]] std::string GetStatementType() const;
  [[nodiscard]] std::string GetInScopeOfPrc() const;

 private:
  const int statement_number_;
  std::string statement_type_;
  std::string in_scope_of_proc_;
};