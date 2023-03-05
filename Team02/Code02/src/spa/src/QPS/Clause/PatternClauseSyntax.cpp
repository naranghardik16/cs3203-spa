#include "PatternClauseSyntax.h"

PatternClauseSyntax::PatternClauseSyntax(SyntaxPair pair) : ClauseSyntax(std::move(pair)) {}

bool PatternClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  PatternClauseSyntax *pc = dynamic_cast<PatternClauseSyntax*>(&other);
  if (pc) {
    return (this->GetEntity() == pc->GetEntity()) && (this->GetFirstParameter() == pc->GetFirstParameter()) &&
        (this->GetSecondParameter() == pc->GetSecondParameter());
  }
  return false;
}

bool PatternClauseSyntax::IsBooleanClause(Map &declaration_map) {
  return false;
}

std::shared_ptr<ClauseEvaluator> PatternClauseSyntax::CreateClauseEvaluator(Map &declaration_map) {
  std::shared_ptr<ClauseEvaluator> eval = std::make_shared<AssignPatternClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  return eval;
}


