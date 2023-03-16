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
  std::string syn = declaration_map.at(ClauseSyntax::GetEntity());
  std::shared_ptr<ClauseEvaluator> eval;
  if (syn == pql_constants::kPqlAssignEntity) {
    eval = std::make_shared<AssignPatternClauseEvaluator>(declaration_map,
                                                          ClauseSyntax::GetSyntaxPair(),
                                                          ClauseSyntax::GetExpression());
  } else if (syn == pql_constants::kPqlIfEntity) {
    eval = std::make_shared<IfPatternClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  } else {
    eval = std::make_shared<WhilePatternClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  }

  return eval;
}

int PatternClauseSyntax::GetClauseScore(Map &declaration_map) {
  int score;
  std::string syn = declaration_map.at(ClauseSyntax::GetEntity());
  if (syn == pql_constants::kPqlAssignEntity) {
    score = 3;
  } else if (syn == pql_constants::kPqlIfEntity) {
    score = 2;
  } else {
    score = 2;
  }
  return score;
}
