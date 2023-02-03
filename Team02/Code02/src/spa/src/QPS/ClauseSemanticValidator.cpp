#include "ClauseSemanticValidator.h"

ClauseSemanticValidator::ClauseSemanticValidator(Map &declaration) : declaration_(declaration) {
  has_semantic_error_ = false;
}

void ClauseSemanticValidator::ValidateSuchThatClauseSemantic(std::shared_ptr<ClauseSyntax> clause) {
  std::shared_ptr<SuchThatBaseHandler> handler_1 = std::make_shared<SuchThatBaseHandler>();
  std::shared_ptr<StmtToStmtHandler> handler_2 = std::make_shared<StmtToStmtHandler>();
  std::shared_ptr<StmtProcToVarHandler> handler_3 = std::make_shared<StmtProcToVarHandler>();

  handler_1->SetNext(handler_2)->SetNext(handler_3);

  handler_1->HandleSemantic(clause, declaration_);
}

void ClauseSemanticValidator::ValidatePatternClauseSemantic(std::shared_ptr<ClauseSyntax> clause) {
  std::shared_ptr<PatternHandler> handler = std::make_shared<PatternHandler>();

  handler->HandleSemantic(clause, declaration_);
}
