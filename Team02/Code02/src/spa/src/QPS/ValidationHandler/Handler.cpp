#include "Handler.h"

Handler::Handler() : next_handler_(nullptr) {}

std::shared_ptr<Handler> Handler::SetNext(std::shared_ptr<Handler> handler) {
  this->next_handler_ = handler;
  return handler;
}

void Handler::Handle(Map &declaration, Map &clause) {
  if (this->next_handler_) {
    return this->next_handler_->Handle(declaration, clause);
  }
}
