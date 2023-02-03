#pragma once
#include "SuchThatClauseSyntax.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ModifiesClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/UsesClauseEvaluator.h"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsClauseEvaluator.h"

SuchThatClauseSyntax::SuchThatClauseSyntax(SyntaxPair pair) : ClauseSyntax(pair) {}

bool SuchThatClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  SuchThatClauseSyntax *sc = dynamic_cast<SuchThatClauseSyntax*>(&other);
  if (sc) {
    return (this->GetEntity() == sc->GetEntity()) && (this->GetFirstParameter() == sc->GetFirstParameter()) &&
        (this->GetSecondParameter() == sc->GetSecondParameter());
  }
  return false;
}

std::shared_ptr<ClauseEvaluator> SuchThatClauseSyntax::CreateClauseEvaluator(Synonym s, Map declaration_map) {
  std::shared_ptr<ClauseEvaluator> evaluator;
  std::string relationship_reference = ClauseSyntax::GetEntity();
  if (relationship_reference == pql_constants::kPqlFollowsRel) {
    evaluator = std::make_shared<FollowsClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlFollowsStarRel) {
    evaluator = std::make_shared<FollowsStarClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlParentRel) {
    evaluator = std::make_shared<ParentClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlParentStarRel) {
    evaluator = std::make_shared<ParentStarClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlUsesRel) {
    evaluator = std::make_shared<UsesClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
  } else {
    evaluator = std::make_shared<ModifiesClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
  }
  return evaluator;
}
