#include "WithClauseSyntax.h"

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
  auto first_arg = this->GetFirstParameter();
  auto second_arg = this->GetSecondParameter();

  // If not, the only case left is int or ident
  bool is_first_arg_an_attr_ref = QueryUtil::IsAttrRef(first_arg);
  bool is_second_arg_an_attr_ref = QueryUtil::IsAttrRef(second_arg);

  return !is_first_arg_an_attr_ref && !is_second_arg_an_attr_ref;
}

std::shared_ptr<ClauseEvaluator> WithClauseSyntax::CreateClauseEvaluator(Map &declaration_map) {
  std::shared_ptr<ClauseEvaluator> eval = std::make_shared<WithClauseEvaluator>(declaration_map,
                                                                                ClauseSyntax::GetSyntaxPair());
  return eval;
}

int WithClauseSyntax::GetClauseScore(Map &declaration_map) {
  return 1;
}
