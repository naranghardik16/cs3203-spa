#pragma once
#include "Expression.h"

Expression::Expression(std::string expression_type)
    : expression_type_(std::move(expression_type)) {}

std::string Expression::GetExpressionType() const {
  return this->expression_type_;
}