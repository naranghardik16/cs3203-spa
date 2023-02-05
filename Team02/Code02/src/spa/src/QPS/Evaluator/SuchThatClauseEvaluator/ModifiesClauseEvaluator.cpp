#pragma once
#include "ModifiesClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"

std::vector<std::vector<std::string>> ModifiesClauseEvaluator::EvaluateClause() {
  auto syntax_pair = ClauseEvaluator::GetSyntaxPair();
  auto relationship_reference = syntax_pair.first;
  auto first_arg = syntax_pair.second.first;
  auto second_arg = syntax_pair.second.second;
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  auto pkb = ClauseEvaluator::GetPKB();

  //TODO maybe can abstract this out
  bool is_first_arg_a_type_of_statement_synonym = QueryUtil::IsAssignSynonym(declaration_map, first_arg)
      || QueryUtil::IsReadSynonym(declaration_map, first_arg) || QueryUtil::IsContainerStatementSynonym(declaration_map, first_arg);
  bool is_first_arg_an_integer = LexicalRuleValidator::IsInteger(first_arg);
  bool is_second_arg_a_wildcard = QueryUtil::IsWildcard(second_arg);
  bool is_second_arg_a_variable_synonym = QueryUtil::IsVariableSynonym(declaration_map, second_arg);
  bool is_second_arg_an_ident = LexicalRuleValidator::IsIdent(second_arg) && !is_second_arg_a_variable_synonym;

  std::vector<std::vector<std::string>> result;

  //e.g. Modifies(5, _)
  if (is_first_arg_an_integer && is_second_arg_a_wildcard) {
  }

  if (is_first_arg_an_integer && is_second_arg_a_variable_synonym) {
    //TODO Boolean constraint handling
  }

  //e.g. Modifies(a, _)
  if (is_first_arg_a_type_of_statement_synonym && is_second_arg_a_wildcard) {
    result = pkb->GetModifiesStatementVariablePairs();
    //TODO need to return the first element in every vector
  }

  //e.g. Modifies(a,v)
  if (is_first_arg_a_type_of_statement_synonym && is_second_arg_a_variable_synonym) {
    result = pkb->GetModifiesStatementVariablePairs();
  }

  //e.g. Modifies(a, _)
  if (is_first_arg_a_type_of_statement_synonym && is_second_arg_a_wildcard) {
    result = pkb->GetModifiesStatementVariablePairs();
  }

  //e.g. Modifies(a,”count”)
  if (is_first_arg_a_type_of_statement_synonym && is_second_arg_an_ident) {
    result = pkb->GetStatementsModifiesVariable(second_arg);
  }

  //e.g. Modifies(5,v)
  bool temp = is_first_arg_an_integer && is_second_arg_a_variable_synonym;

  if (is_first_arg_an_integer && is_second_arg_a_variable_synonym) {
    result = pkb->GetVariablesModifiedByStatement(first_arg);
  }

  return result;
}