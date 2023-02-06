#pragma once
#include "FollowsClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

bool FollowsClauseEvaluator::IsBooleanConstraint() {
  return true;
}
bool FollowsClauseEvaluator::EvaluateBooleanConstraint() {
  return true;
}

std::vector<std::vector<std::string>> FollowsClauseEvaluator::EvaluateClause() {
  auto syntax_pair = ClauseEvaluator::GetSyntaxPair();
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  auto pkb = ClauseEvaluator::GetPKB();
  auto synonym = ClauseEvaluator::GetSynonym();
  auto type = declaration_map[synonym];
  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsAssignSynonym(declaration_map, first_arg_)
      || QueryUtil::IsReadSynonym(declaration_map, first_arg_) || QueryUtil::IsContainerStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_integer = LexicalRuleValidator::IsInteger(second_arg_);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg_);

  std::vector<std::vector<std::string>> result;
  if (is_first_arg_a_wildcard && is_second_arg_a_wildcard) {
    //huh
  }

  if (is_first_arg_a_wildcard && is_second_arg_a_integer) {
    //e.g. Follows(_,"5") --> Get statements that "5" follows
    //result = pkb->GetStatementsFollowedBy(second_arg_, type);
  }
  return result;
}

