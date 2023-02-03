#include "Variable.h"

Variable::Variable(std::string_view name) : Expression(name,
                                                       "variable") {}

void Variable::Accept(ParserVisitor *visitor) {
  visitor->VisitVariable(this);
}