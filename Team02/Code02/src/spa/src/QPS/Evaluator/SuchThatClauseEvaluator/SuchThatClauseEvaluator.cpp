#include "SuchThatClauseEvaluator.h"

bool SuchThatClauseEvaluator::EvaluateBooleanConstraint() {
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    // Example query: Follow*(_, _)

    return HandleBothWildcard();
  } else if (is_first_arg_a_wildcard) {
    // Example query: Follow*(_, 1)

    return HandleFirstWildcardSecondValue();
  } else if (is_second_arg_a_wildcard) {
    // Example query: Follow*(1, _)

    return HandleFirstValueSecondWildcard();
  } else {
    // Example query: Follow*(1, 6)

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
    // Example query: Follows* (s,s)

    table = HandleBothSynonym();
  } else if (is_first_arg_synonym && is_second_arg_a_wildcard) {
    // Example query: Follows* (s,_)

    table = HandleFirstSynonymSecondWildcard();
  } else if (is_first_arg_synonym) {
    // Example query: Follows* (s, 1)

    table = HandleFirstSynonymSecondValue();
  } else if (is_first_arg_a_wildcard) {
    // Example query: Follows* (_, s)

    table = HandleFirstWildcardSecondSynonym();
  } else {
    // Example query: Follows* (1, s)

    table = HandleFirstValueSecondSynonym();
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
