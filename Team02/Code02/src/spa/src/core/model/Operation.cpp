#pragma once
#include "Operation.h"

Operation::Operation(string name,
                     string type,
                     pair<Expression *, Expression *> arguments) : Expression(
    move(name),
    type) {
  arguments_ = arguments;
}

