#pragma once
#include<string>

class Expression {
 public:
  Expression() = default;
  explicit Expression(std::string_view name, std::string expression_type);
  [[nodiscard]] std::string GetExpressionType() const;
  [[nodiscard]] std::string GetName() const;
  bool operator==(const Expression &other) const;
 private:
  std::string expression_type_;
  std::string name_;
};