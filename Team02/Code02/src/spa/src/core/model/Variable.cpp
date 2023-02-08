#include "Variable.h"

Variable::Variable(std::string name) : Expression(name,
                                                  "variable") {}

void Variable::Accept(ParserVisitor *visitor) {
  visitor->VisitVariable(this);
}