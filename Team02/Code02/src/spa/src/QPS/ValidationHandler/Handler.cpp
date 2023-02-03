#include "Handler.h"

Handler::Handler() : next_handler_(nullptr) {}

std::shared_ptr<Handler> Handler::SetNext(std::shared_ptr<Handler> handler) {
  this->next_handler_ = handler;
  return handler;
}

void Handler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  if (this->next_handler_) {
    return this->next_handler_->HandleSyntax(clause);
  }
  throw SyntaxErrorException();
}

void Handler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  if (this->next_handler_) {
    return this->next_handler_->HandleSemantic(clause, declaration);
  }
  throw SemanticErrorException();
}
