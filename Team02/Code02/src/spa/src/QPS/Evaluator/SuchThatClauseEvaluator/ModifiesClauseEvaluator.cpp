#pragma once
#include "ModifiesClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

bool ModifiesClauseEvaluator::IsBooleanConstraint() {
  auto select_synonym = ClauseEvaluator::GetSynonym();
  bool is_select_synonym_in_arg = first_arg_ == select_synonym || second_arg_ == select_synonym;
  bool is_second_arg_an_ident = QueryUtil::IsQuoted(second_arg_);
  return (is_select_synonym_in_arg || is_second_arg_an_ident);
}

bool ModifiesClauseEvaluator::EvaluateBooleanConstraint() {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  auto pkb = ClauseEvaluator::GetPKB();

  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsAssignSynonym(declaration_map, first_arg_)
      || QueryUtil::IsReadSynonym(declaration_map, first_arg_) || QueryUtil::IsContainerStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);

  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_ident = QueryUtil::IsQuoted(second_arg_);

  std::vector<std::vector<std::string>> result;

  if (is_first_arg_a_type_of_statement_synonym) {
    if (is_second_arg_a_wildcard) {
      //e.g. Select s such that Modifies(s, _) --> is there a statement that modifies a variable?
      //IsAStatementThatModifiesAVariable(s, stmttype)
      auto constraints = pkb->GetModifiesStatementVariablePairs(declaration_map[first_arg_]);
      result = QueryUtil::ExtractFirstElementInTheVectors(constraints);
    } else if (is_second_arg_a_variable_synonym) {
      //e.g. Select a1 such that Modifies(a,v) -- is there an assignment that modifies a variable?
      return true;
    } else {
      //e.g. Select a1 such that Modifies(a,”count”) -- is there an assignment that modifies "count"
      result = pkb->GetStatementsModifiesVariable(second_arg_, declaration_map[first_arg_]);
    }
  }

  if (is_first_arg_an_integer) {
    if (is_second_arg_a_wildcard) {
      //Modifies(5, _) -- does 5 modify any variables?
      return true;
    } else if (is_second_arg_a_variable_synonym) {
      //Select v1 such that Modifies(5,v) -- does 5 modify any variables?
      return true;
    } else {
      //Modifies(5, "count") -- does 5 modify "count"?
      return pkb->IsModifiesStatement(first_arg_, second_arg_);
    }
  }

  return !result.empty();
}

std::vector<std::vector<std::string>> ModifiesClauseEvaluator::EvaluateClause() {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  auto pkb = ClauseEvaluator::GetPKB();

  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsAssignSynonym(declaration_map, first_arg_)
      || QueryUtil::IsReadSynonym(declaration_map, first_arg_) || QueryUtil::IsContainerStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);

  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_ident = QueryUtil::IsQuoted(second_arg_);
  std::vector<std::vector<std::string>> result;

  if (is_first_arg_a_type_of_statement_synonym) {
    auto type = declaration_map[first_arg_];
    //e.g. Modifies(a,v)
    if (is_second_arg_a_variable_synonym) {
      result = pkb->GetModifiesStatementVariablePairs(type);
    } else {
      //e.g. Modifies(a,”count”) -- get assignments that modify count
        result = pkb->GetStatementsModifiesVariable(second_arg_, type);
      }
  }

  if (is_first_arg_an_integer) {
    //e.g.Modifies(5,v)
      result = pkb->GetVariablesModifiedByStatement(first_arg_);
  }

  return result;
}