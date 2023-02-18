#pragma once
#include <string>
#include "Entity.h"

class Statement : public Entity {
 public:
  Statement(
      int statement_number,
      std::string statement_type,
      std::string in_scope_of_proc);
  virtual ~Statement() = default;
  virtual void Accept(shared_ptr<ParserVisitor> visitor) = 0;
  [[nodiscard]] int GetStatementNumber() const;
  [[nodiscard]] std::string GetStatementType() const;
  [[nodiscard]] std::string GetInScopeOfPrc() const;

 private:
  const int statement_number_;
  std::string statement_type_;
  std::string in_scope_of_proc_;
};
