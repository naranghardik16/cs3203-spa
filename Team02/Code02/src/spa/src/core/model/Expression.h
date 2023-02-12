#pragma once

#include<string>
#include "Entity.h"

class Expression : public Entity {
 public:
  Expression() = default;
  explicit Expression(std::string name, std::string expression_type);
  virtual void Accept(ParserVisitor *visitor) = 0;
  [[nodiscard]] std::string GetExpressionType() const;
  [[nodiscard]] std::string GetName() const;
  virtual bool operator==(const Expression &other) const;
 private:
  std::string expression_type_;
  std::string name_;
};