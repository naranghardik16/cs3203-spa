#pragma once
#include "FollowsClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

bool FollowsClauseEvaluator::IsBooleanConstraint() {
  auto select_synonym = ClauseEvaluator::GetSynonym();
  bool is_select_synonym_in_arg = first_arg_ == select_synonym || second_arg_ == select_synonym;
  bool is_either_arg_an_ident = QueryUtil::IsQuoted(first_arg_) || QueryUtil::IsQuoted(second_arg_);
  return (is_select_synonym_in_arg || is_either_arg_an_ident);
}

bool FollowsClauseEvaluator::EvaluateBooleanConstraint() {
  auto pkb = ClauseEvaluator::GetPKB();
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_integer = LexicalRuleValidator::IsInteger(second_arg_);
  bool is_second_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, second_arg_);

  std::vector<std::vector<std::string>> result;
  const std::string kEmpty = "NOT_TYPE_CONSTRAINT";

  if (is_first_arg_a_wildcard) {
    if (is_second_arg_a_wildcard) {
      //e.g. Follows(_,_) -- return all Follows relationships between statements
      result = pkb->GetFollowPairs(kEmpty, kEmpty);
    } else if (is_second_arg_a_type_of_statement_synonym) {
      //e.g. Follows(_, s) --> Get statements that follow another statement
      auto constraints = pkb->GetFollowPairs(declaration_map[second_arg_], kEmpty);
      result = QueryUtil::ExtractSecondElementInTheVectors(constraints);
    } else {
      //e.g. Follows(_,"5") --> Get all types of statements that "5" follows
      result = pkb->GetStatementsFollowedBy(second_arg_, kEmpty);
    }
  }

  if (is_first_arg_a_type_of_statement_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Follows(s, _) --> Get statements that have followers
      auto constraints = pkb->GetFollowPairs(declaration_map[first_arg_], kEmpty);
      result = QueryUtil::ExtractFirstElementInTheVectors(constraints);
    } else if (is_second_arg_a_type_of_statement_synonym) {
      //e.g. Follows(a,p)
      auto constraints = pkb->GetFollowPairs(declaration_map[first_arg_], declaration_map[second_arg_]);
    } else {
      //e.g. Follows(a,"5") --> Get statement that 5 follows of type assignment
      result = pkb->GetStatementsFollowedBy(second_arg_, declaration_map[first_arg_]);
    }
  }

    if (is_first_arg_an_integer) {
      if (is_second_arg_a_wildcard) {
        //e.g. Follows("5", _) --> Get all types of statements that follow "5"
        result = pkb->GetStatementsFollowing(first_arg_, kEmpty);
      } else if (is_second_arg_a_type_of_statement_synonym) {
        //e.g. Follows("5", a) --> Get statement that follow 5 of type assignment
        result = pkb->GetStatementsFollowing(first_arg_, declaration_map[second_arg_]);
      } else {
        //e.g. Follows(5, 6)
        return pkb->IsFollows(first_arg_, second_arg_);
      }
    }

    return !result.empty();
  }

  std::vector<std::vector<std::string>> FollowsClauseEvaluator::EvaluateClause() {
    auto syntax_pair = ClauseEvaluator::GetSyntaxPair();
    auto declaration_map = ClauseEvaluator::GetDeclarationMap();
    auto pkb = ClauseEvaluator::GetPKB();

    bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, first_arg_);
    bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
    bool is_second_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, second_arg_);

    std::vector<std::vector<std::string>> result;

    if (is_first_arg_a_type_of_statement_synonym) {
      if (is_second_arg_a_type_of_statement_synonym) {
        //e.g. Follows(a,p)
        result = pkb->GetFollowPairs(declaration_map[first_arg_], declaration_map[second_arg_]);
      } else {
        //e.g. Follows(a,"5") --> Get statement that 5 follows of type assignment
        result = pkb->GetStatementsFollowedBy(second_arg_, declaration_map[first_arg_]);
      }
    }

    if (is_first_arg_an_integer && is_second_arg_a_type_of_statement_synonym) {
      //e.g. Follows("5", a) --> Get statement that follow 5 of type assignment
      result = pkb->GetStatementsFollowing(first_arg_, declaration_map[second_arg_]);
    }

    return result;
  }

