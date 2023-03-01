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
  auto first_arg = this->GetFirstParameter();
  auto second_arg = this->GetSecondParameter();

  //If not, the only case left is int or ident
  bool is_first_arg_an_attr_ref = QueryUtil::IsAttrRef(first_arg);
  bool is_second_arg_an_attr_ref = QueryUtil::IsAttrRef(second_arg);

  if (is_first_arg_an_attr_ref && is_second_arg_an_attr_ref) {
    //e.g. p.procName = c.value
    if (QueryUtil::IsMismatchingAttrRef(first_arg, second_arg)) {
      return true;
    } else {
      return false;
    }
  } else if (is_first_arg_an_attr_ref) {
    //e.g. p.procName = 5, a.stmt# = "v"
    return QueryUtil::IsTrivialAttrRefWithNoResult(first_arg, second_arg);
  } else if (is_second_arg_an_attr_ref) {
    //e.g. p.procName = 5, a.stmt# = "v"
    return QueryUtil::IsTrivialAttrRefWithNoResult(second_arg, first_arg);
  } else {
    // 5 = 6, v = 5 -- no synonym present
    return true;
  }
}

std::shared_ptr<ClauseEvaluator> WithClauseSyntax::CreateClauseEvaluator(Map &declaration_map) {
  std::shared_ptr<ClauseEvaluator> eval = std::make_shared<WithClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  return eval;
}