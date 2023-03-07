#include "SuchThatClauseSyntax.h"

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

bool SuchThatClauseSyntax::IsBooleanClause(Map &declaration_map) {
  auto first_arg = this->GetFirstParameter();
  auto second_arg = this->GetSecondParameter();
  bool is_first_arg_a_synonym = declaration_map.count(first_arg);
  bool is_second_arg_a_synonym = declaration_map.count(second_arg);
  bool has_synonym = is_first_arg_a_synonym || is_second_arg_a_synonym;
  return !has_synonym;
}

std::shared_ptr<ClauseEvaluator> SuchThatClauseSyntax::CreateClauseEvaluator(Map &declaration_map) {
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
  } else if (relationship_reference == pql_constants::kPqlModifiesRel) {
    if (QueryUtil::IsProcedureSynonym(declaration_map, ClauseSyntax::GetFirstParameter())
    || QueryUtil::IsQuoted(ClauseSyntax::GetFirstParameter())) {
      evaluator = std::make_shared<ModifiesPClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
    } else {
      evaluator = std::make_shared<ModifiesSClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
    }
  } else if (relationship_reference == pql_constants::kPqlAffectsRel) {
    evaluator = std::make_shared<AffectsClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlAffectsStarRel) {
    evaluator = std::make_shared<AffectsStarClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlCallsRel) {
    evaluator = std::make_shared<CallsClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else if (relationship_reference == pql_constants::kPqlCallsStarRel) {
    evaluator = std::make_shared<CallsStarClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else {

  }
  return evaluator;
}
