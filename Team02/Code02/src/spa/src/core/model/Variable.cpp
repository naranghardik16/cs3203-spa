#include "Variable.h"

Variable::Variable(std::string name) : Expression(std::move(name),
                                                  "variable") {}

void Variable::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitVariable(shared_from_this());
}

bool Variable::IsLeafNodeExpression() {
  return true;
}