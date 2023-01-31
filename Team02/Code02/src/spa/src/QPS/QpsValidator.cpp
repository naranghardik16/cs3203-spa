#include "QpsValidator.h"

void QpsValidator::Validate(Map &declaration, Map &such_that_clause, Map &pattern_clause) {
  ValidateSuchThat(declaration, such_that_clause);
  ValidatePattern(declaration, pattern_clause);
}

void QpsValidator::ValidateSuchThat(Map &declaration, Map &clause) {
  std::shared_ptr<SuchThatBaseHandler> handler_1 = std::make_shared<SuchThatBaseHandler>();
  std::shared_ptr<StmtToStmtHandler> handler_2 = std::make_shared<StmtToStmtHandler>();
  std::shared_ptr<StmtProcToVarHandler> handler_3 = std::make_shared<StmtProcToVarHandler>();

  handler_1->SetNext(handler_2)->SetNext(handler_3);

  handler_1->Handle(declaration, clause);
}

void QpsValidator::ValidatePattern(Map &declaration, Map &clause) {
  std::shared_ptr<PatternHandler> handler = std::make_shared<PatternHandler>();

  handler->Handle(declaration, clause);
}
