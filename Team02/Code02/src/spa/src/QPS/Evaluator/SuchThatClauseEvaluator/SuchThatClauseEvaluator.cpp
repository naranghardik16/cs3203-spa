#include "SuchThatClauseEvaluator.h"

bool SuchThatClauseEvaluator::EvaluateBooleanConstraint() {
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    // Case: relRef(_, _)
    return HandleBothWildcard();
  } else if (is_first_arg_a_wildcard) {
    // Case: relRef(_, val)
    return HandleFirstWildcardSecondValue();
  } else if (is_second_arg_a_wildcard) {
    // Case: relRef(val, _)
    return HandleFirstValueSecondWildcard();
  } else {
    // Case: relRef(val, val)
    return HandleBothValue();
  }
}

std::shared_ptr<Result> SuchThatClauseEvaluator::EvaluateClause() {
  ResultHeader header;
  ResultTable table;

  bool is_first_arg_synonym = QueryUtil::IsSynonym(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_synonym = QueryUtil::IsSynonym(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_synonym) {
    header[first_arg_] = static_cast<int>(header.size());
  }
  if (is_second_arg_synonym) {
    header[second_arg_] = static_cast<int>(header.size());
  }

  if (is_first_arg_synonym && is_second_arg_synonym) {
    // Case: relRef(syn, syn)
    table = HandleBothSynonym();
  } else if (is_first_arg_synonym && is_second_arg_a_wildcard) {
    // Case: relRef(syn,_)
    table = HandleFirstSynonymSecondWildcard();
  } else if (is_first_arg_synonym) {
    // Case: relRef(syn, val)
    table = HandleFirstSynonymSecondValue();
  } else if (is_first_arg_a_wildcard) {
    // Case: relRef(_, syn)
    table = HandleFirstWildcardSecondSynonym();
  } else {
    // Case: relRef(val, syn)
    table = HandleFirstValueSecondSynonym();
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
