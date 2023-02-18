#include "Variable.h"

Variable::Variable(std::string name) : Expression(std::move(name),
                                                  "variable") {}

void Variable::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitVariable(make_shared<Variable>(*this));
}

bool Variable::IsLeafNodeExpression() {
  return true;
}