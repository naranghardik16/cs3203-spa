#pragma once
#include<string>

class Expression {
 public:
  [[nodiscard]] std::string GetExpressionType();

 private:
  std::string expression_type_;

};