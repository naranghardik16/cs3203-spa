#pragma once
#include "Expression.h"

Expression::Expression(std::string name, std::string expression_type)
    : name_(name), expression_type_(std::move(expression_type)) {}

std::string Expression::GetExpressionType() const {
  return expression_type_;
}

std::string Expression::GetName() const {
  return name_;
}

bool Expression::operator==(const Expression &other) const {
  return expression_type_ == other.expression_type_ && name_ == other.name_;
}