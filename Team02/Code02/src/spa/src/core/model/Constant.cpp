#include "Constant.h"

Constant::Constant(std::string name) : Expression(std::move(name),
                                                  "constant") {}

void Constant::Accept(shared_ptr<ParserVisitor> visitor) {
  visitor->VisitConstant(shared_from_this());
}

bool Constant::IsLeafNodeExpression() {
  return true;
}