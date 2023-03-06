#include "IfPatternClauseEvaluator.h"

bool IfPatternClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  //Would never be called as pattern clause always has synonym
  return false;
}

std::shared_ptr<Result> IfPatternClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  ResultHeader header{{syn_if_, 0}};
  ResultTable table;

  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_arg_1_synonym = declaration_map.count(first_arg_);
  bool is_arg_1_wildcard = QueryUtil::IsWildcard(first_arg_);

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  if (is_arg_1_synonym) {
    //e.g. if(s, _, _)
    header[first_arg_] = (int) header.size();

    pair_constraint = pkb->GetIfConditionVariablePair();
  } else if (is_arg_1_wildcard) {
    //e.g. if(_,_,_)
    single_constraint = pkb->GetIfThatHasConditionVariable();
  } else {
    single_constraint = pkb->GetIfWithConditionVariable(QueryUtil::GetIdent(first_arg_));
  }

  if (!single_constraint.empty()) {
    table = ClauseEvaluator::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = ClauseEvaluator::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
