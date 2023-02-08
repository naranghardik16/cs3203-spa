#pragma once
#include "SuchThatClauseSyntax.h"

#include <utility>
#include "QPS/Evaluator/SuchThatClauseEvaluator/ModifiesStatementClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/UsesClauseEvaluator.h"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ParentClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsStarClauseEvaluator.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/FollowsClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Evaluator/SuchThatClauseEvaluator/ModifiesProcedureClauseEvaluator.h"

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
    auto first_arg = ClauseSyntax::GetSyntaxPair().second.first;
    auto second_arg = ClauseSyntax::GetSyntaxPair().second.second;
    bool first_arg_is_ident = QueryUtil::IsQuoted(first_arg);
    bool first_arg_is_a_type_of_procedure_synonym = QueryUtil::IsProcedureSynonym(declaration_map, first_arg)
        || QueryUtil::IsCallSynonym(declaration_map, first_arg);
    if (first_arg_is_ident || first_arg_is_a_type_of_procedure_synonym) {
      evaluator = std::make_shared<ModifiesProcedureClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
    } else {
      //either statement synonym or integer
      evaluator = std::make_shared<ModifiesStatementClauseEvaluator>(s, declaration_map, ClauseSyntax::GetSyntaxPair());
    }
  }
  return evaluator;
}
