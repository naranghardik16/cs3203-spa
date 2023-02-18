#include "Variable.h"

Variable::Variable(std::string name) : Expression(std::move(name),
                                                  "variable") {}

void Variable::Accept(ParserVisitor *visitor) {
  visitor->VisitVariable(this);
}

bool Variable::IsLeafNodeExpression() {
  return true;
}