#include "Variable.h"

Variable::Variable(std::string_view name) : Expression(name,
                                                       "variable") {}