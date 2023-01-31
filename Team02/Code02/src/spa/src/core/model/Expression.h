#pragma once
#include<string>

class Expression {
 public:
  explicit Expression(std::string expression_type);
  [[nodiscard]] std::string GetExpressionType() const;

 private:
  std::string expression_type_;
};