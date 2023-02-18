#pragma once

#include<string>
#include <optional>
#include "Entity.h"
#include <optional>

class Expression : public Entity {
 public:
  typedef std::pair<shared_ptr<Expression>, shared_ptr<Expression>> PairOfArguments;
  Expression() = default;
  explicit Expression(std::string name, std::string expression_type);
  virtual ~Expression() = default;
  virtual void Accept(shared_ptr<ParserVisitor> visitor) = 0;
  [[nodiscard]] std::optional<PairOfArguments> GetArguments() const;
  virtual inline bool IsLeafNodeExpression();
  [[nodiscard]] std::string GetExpressionType() const;
  [[nodiscard]] std::string GetName() const;
  virtual bool operator==(const Expression &other) const;
 protected:
  std::optional<PairOfArguments> arguments_;

 private:
  std::string expression_type_;
  std::string name_;
};