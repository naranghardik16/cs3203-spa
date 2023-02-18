#pragma once
#include "Operation.h"

Operation::Operation(string name,
                     string type,
                     pair<Expression *, Expression *> arguments) : Expression(
    move(name),
    type) {
  arguments_ = arguments;
}

pair<Expression *, Expression *> Operation::GetArguments() const {
  return arguments_;
}

//bool Operation::operator==(const Expression &other) const {
//  if (!Expression::operator==(other)) {
//    return false;
//  }
//  auto casted_other = dynamic_cast<const Operation&>(other);
//  return Expression::operator==(other) && arguments_ == other.GetArguments();
//}