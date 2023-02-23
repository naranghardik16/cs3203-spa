#pragma once
#include "WithClauseSyntax.h"
#include "QPS/Evaluator/WithClauseEvaluator/WithClauseEvaluator.h"

WithClauseSyntax::WithClauseSyntax(SyntaxPair pair) : ClauseSyntax(pair) {}

bool WithClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  WithClauseSyntax *pc = dynamic_cast<WithClauseSyntax*>(&other);
  if (pc) {
    return (this->GetEntity() == pc->GetEntity()) && (this->GetFirstParameter() == pc->GetFirstParameter()) &&
        (this->GetSecondParameter() == pc->GetSecondParameter());
  }
  return false;
}

bool WithClauseSyntax::IsBooleanClause(Map &declaration_map) {
  return false;
}

std::shared_ptr<ClauseEvaluator> WithClauseSyntax::CreateClauseEvaluator(Map &declaration_map) {
  std::shared_ptr<ClauseEvaluator> eval = std::make_shared<WithClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  return eval;
}