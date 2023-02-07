#pragma once
#include "ModifiesClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

bool ModifiesClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg_);

  //! If first arg is wildcard then semantic error; If first arg is synonym then it is not considered boolean constraint
  if (is_first_arg_an_integer) {
    if (is_second_arg_a_wildcard) {
      //Modifies(5, _) -- does 5 modify any variables?
      return !pkb->GetVariablesModifiedByStatement(first_arg_).empty();
    } else if (is_second_arg_a_variable_synonym) {
      //Select v1 such that Modifies(5,v) -- does 5 modify any variables?
      return !pkb->GetVariablesModifiedByStatement(first_arg_).empty();
    } else {
      //Modifies(5, "count") -- does 5 modify "count"?
      return pkb->IsModifiesStatement(first_arg_, second_arg_);
    }
  }
}

std::shared_ptr<Result> ModifiesClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();

  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsAssignSynonym(declaration_map, first_arg_)
      || QueryUtil::IsReadSynonym(declaration_map, first_arg_) || QueryUtil::IsContainerStatementSynonym(declaration_map, first_arg_);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg_);

  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg_);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg_);
  bool is_second_arg_a_ident = QueryUtil::IsQuoted(second_arg_);
  ResultTable table;

  if (is_first_arg_a_type_of_statement_synonym) {
    auto type = declaration_map[first_arg_];
    if (is_second_arg_a_wildcard) {
      //e.g. Select s such that Modifies(s, _) --> is there a statement that modifies a variable?
      auto constraints = pkb->GetModifiesStatementVariablePairs(declaration_map[first_arg_]);
      table = QueryUtil::ExtractFirstElementInTheVectors(constraints);
    } else if (is_second_arg_a_variable_synonym) {
      //e.g. Modifies(a,v)
      table = pkb->GetModifiesStatementVariablePairs(type);
    } else {
      //e.g. Modifies(a,”count”) -- get assignments that modify count
      table = pkb->GetStatementsModifiesVariable(second_arg_, type);
      }
  }

  if (is_first_arg_an_integer) {
    //e.g.Modifies(5,v)
    table = pkb->GetVariablesModifiedByStatement(first_arg_);
  }

  ResultHeader header;
  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);

  return result_ptr;

}