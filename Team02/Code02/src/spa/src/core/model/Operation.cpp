#include "Operation.h"

Operation::Operation(string name,
                     string type,
                     pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments) : Expression(
    move(name),
    type) {
  arguments_ = arguments;
}

