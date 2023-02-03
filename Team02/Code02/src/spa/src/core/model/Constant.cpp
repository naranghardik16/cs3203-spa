#include "Constant.h"

Constant::Constant(std::string name) : Expression(std::move(name),
                                                  "constant") {}