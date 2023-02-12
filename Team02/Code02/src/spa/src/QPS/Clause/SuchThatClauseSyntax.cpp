#pragma once
#include "SuchThatClauseSyntax.h"
#include <utility>
#include "QPS/Evaluator/SuchThatClauseEvaluator/ModifiesSClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/UsesSClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/UsesPClauseEvaluator.h"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsClauseEvaluator.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ModifiesPClauseEvaluator.h"

SuchThatClauseSyntax::SuchThatClauseSyntax(SyntaxPair pair) : ClauseSyntax(std::move(pair)) {}

bool SuchThatClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  auto *sc = dynamic_cast<SuchThatClauseSyntax*>(&other);
  if (sc) {
    return (this->GetEntity() == sc->GetEntity()) && (this->GetFirstParameter() == sc->GetFirstParameter()) &&
        (this->GetSecondParameter() == sc->GetSecondParameter());
  }
  return false;
}

std::shared_ptr<ClauseEvaluator> SuchThatClauseSyntax::CreateClauseEvaluator(Synonym s, Map &declaration_map) {
  std::shared_ptr<ClauseEvaluator> evaluator;
  std::string relationship_reference = ClauseSyntax::GetEntity();
  if (relationship_reference == pql_constants::kPqlFollowsRel) {
    evaluator = std::make_shared<FollowsClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlFollowsStarRel) {
    evaluator = std::make_shared<FollowsStarClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlParentRel) {
    evaluator = std::make_shared<ParentClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlParentStarRel) {
    evaluator = std::make_shared<ParentStarClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlUsesRel) {
    if (QueryUtil::IsProcedureSynonym(declaration_map, ClauseSyntax::GetFirstParameter())
    || QueryUtil::IsQuoted(ClauseSyntax::GetFirstParameter())) {
      evaluator = std::make_shared<UsesPClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
    } else {
      evaluator = std::make_shared<UsesSClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
    }
  } else {
    if (QueryUtil::IsProcedureSynonym(declaration_map, ClauseSyntax::GetFirstParameter())
    || QueryUtil::IsQuoted(ClauseSyntax::GetFirstParameter())) {
      evaluator = std::make_shared<ModifiesPClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
    } else {
      evaluator = std::make_shared<ModifiesSClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
    }
  }
  return evaluator;
}
