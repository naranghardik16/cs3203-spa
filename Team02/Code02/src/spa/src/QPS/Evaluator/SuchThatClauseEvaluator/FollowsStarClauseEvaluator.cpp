#pragma once
#include "FollowsStarClauseEvaluator.h"
#include "PKB/Types/PkbCommunicationTypes.h"

bool FollowsStarClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  if (is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    //Example query: Follow*(_, _)

    //TODO: PKB call
  } else if (is_first_arg_a_wildcard && !is_second_arg_a_wildcard) {
    //Example query: Follow*(_, 1)

    //TODO: PKB call
  } else if (!is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    //Example query: Follow*(1, _)

    //TODO: PKB call
  } else {
    //Example query: Follow*(1, 6)

    //TODO: PKB call
  }
  return true;
}

std::shared_ptr<Result> FollowsStarClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  ResultHeader header;
  ResultTable table;

  bool is_first_arg_synonym = declaration_map.count(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_synonym = declaration_map.count(second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  if (is_first_arg_synonym) {
    header.push_back(first_arg_);
  }
  if (is_second_arg_synonym) {
    header.push_back(second_arg_);
  }

  PkbCommunicationTypes::SingleConstraintSet single_constraint;
  PkbCommunicationTypes::PairConstraintSet pair_constraint;

  if (is_first_arg_synonym && is_second_arg_synonym) {
    //Example query: Follows* (s,s)

    //TODO: pkb call
  } else if (is_first_arg_synonym && is_second_arg_a_wildcard) {
    //Example query: Follows* (s,_)

    //TODO: pkb call
  } else if (is_first_arg_synonym) {
    //Example query: Follows* (s, 1)

    //TODO: pkb call
  } else if (is_first_arg_a_wildcard) {
    //Example query: Follows* (_, s)

    //TODO: pkb call
  } else {
    //Example query: Follows* (1, s)

    //TODO: pkb call
  }

  if (!single_constraint.empty()) {
    table = QueryUtil::ConvertSetToResultTableFormat(single_constraint);
  }
  if (!pair_constraint.empty()) {
    table = QueryUtil::ConvertPairSetToResultTableFormat(pair_constraint);
  }

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}
