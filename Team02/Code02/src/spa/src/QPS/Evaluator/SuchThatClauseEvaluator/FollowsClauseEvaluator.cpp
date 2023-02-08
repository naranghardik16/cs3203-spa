#pragma once
#include "FollowsClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"


bool FollowsClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_integer = LexicalRuleValidator::IsInteger(second_arg_);

  ResultTable table;
  const std::string kEmpty = "_";

  if (is_first_arg_a_wildcard) {
    if (is_second_arg_a_wildcard) {
      //e.g. Follows(_,_) -- return all Follows relationships between statements
      table = pkb->GetFollowPairs(kEmpty, kEmpty);
    }
    if (is_second_arg_a_integer) {
      //e.g. Follows(_,"5") --> Get all types of statements that "5" follows
      table = pkb->GetStatementsFollowedBy(second_arg_, kEmpty);
    }
  }

  if (is_first_arg_an_integer) {
    if (is_second_arg_a_wildcard) {
      //e.g. Follows("5", _) --> Get all types of statements that follow "5"
      table = pkb->GetStatementsFollowing(first_arg_, kEmpty);
    }
    if (is_second_arg_a_integer) {
      //e.g. Follows(5, 6)
      return pkb->IsFollows(first_arg_, second_arg_);
    }
  }

  return !table.empty();

}


std::shared_ptr<Result> FollowsClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto syntax_pair = ClauseEvaluator::GetSyntaxPair();
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();


  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_first_arg_a_wildcard = QueryUtil::IsWildcard(first_arg_);

  bool is_second_arg_a_type_of_statement_synonym = QueryUtil::IsATypeOfStatementSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);

  ResultTable table;
  const std::string kEmpty = "_";

  if (is_first_arg_a_type_of_statement_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Follows(s, _) --> Get statements that have followers
      auto constraints = pkb->GetFollowPairs(declaration_map[first_arg_], kEmpty);
      table = QueryUtil::ExtractFirstElementInTheVectors(constraints);
    } else if (is_second_arg_a_type_of_statement_synonym) {
      //e.g. Follows(a,p)
      table = pkb->GetFollowPairs(declaration_map[first_arg_], declaration_map[second_arg_]);
    } else {
      //e.g. Follows(a,"5") --> Get statement that 5 follows of type assignment
      table = pkb->GetStatementsFollowedBy(second_arg_, declaration_map[first_arg_]);
    }
  }

  //Second arg must be a synonym by rule of deciding non-boolean constraints
  if (is_first_arg_an_integer) {
    //e.g. Follows("5", a) --> Get statement that follow 5 of type assignment
    table = pkb->GetStatementsFollowing(first_arg_, declaration_map[second_arg_]);
  }

  //Second arg must be a synonym by rule of non-boolean constraints
  if (is_first_arg_a_wildcard) {
    //e.g. Follows(_, s) --> Get statements that follow another statement
    auto constraints = pkb->GetFollowPairs(declaration_map[second_arg_], kEmpty);
    table = QueryUtil::ExtractSecondElementInTheVectors(constraints);
  }

  ResultHeader header;
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}

