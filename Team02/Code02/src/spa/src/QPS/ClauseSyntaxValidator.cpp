#include "ClauseSyntaxValidator.h"

void ClauseSyntaxValidator::ValidateSuchThatClauseSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::shared_ptr<SuchThatBaseHandler> handler_1 = std::make_shared<SuchThatBaseHandler>();
  std::shared_ptr<StmtToStmtHandler> handler_2 = std::make_shared<StmtToStmtHandler>();
  std::shared_ptr<StmtProcToVarHandler> handler_3 = std::make_shared<StmtProcToVarHandler>();

  handler_1->SetNext(handler_2)->SetNext(handler_3);

  handler_1->HandleSyntax(clause);
}

void ClauseSyntaxValidator::ValidatePatternClauseSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::shared_ptr<PatternHandler> handler = std::make_shared<PatternHandler>();

  handler->HandleSyntax(clause);
}
