#include "Variable.h"

Variable::Variable(std::string name) : Expression(std::move(name),
                                                  "variable") {}