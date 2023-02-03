#pragma once
#include "PatternClauseSyntax.h"

PatternClauseSyntax::PatternClauseSyntax(SyntaxPair pair) : ClauseSyntax(pair) {}

void PatternClauseSyntax::Accept(std::shared_ptr<Visitor> visitor) {
  visitor->VisitPatternClause(this);
}

bool PatternClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  PatternClauseSyntax *pc = dynamic_cast<PatternClauseSyntax*>(&other);
  if (pc) {
    return (this->GetEntity() == pc->GetEntity()) && (this->GetFirstParameter() == pc->GetFirstParameter()) &&
        (this->GetSecondParameter() == pc->GetSecondParameter());
  }
  return false;
}

std::shared_ptr<ClauseEvaluator> PatternClauseSyntax::CreateClauseEvaluator(Synonym s, Map declaration_map) {
  std::shared_ptr<ClauseEvaluator> eval = std::make_shared<AssignPatternClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
  return eval;
}


