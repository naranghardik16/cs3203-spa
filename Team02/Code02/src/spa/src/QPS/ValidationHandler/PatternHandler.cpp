#include "PatternHandler.h"

void PatternHandler::HandleSyntax(ClauseSyntax *clause) {
  std::string syn_assign(clause->GetEntity());
  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  if (!QueryUtil::IsSynonym(syn_assign) || !QueryUtil::IsEntRef(arg_1)) {
    throw SyntaxErrorException();
  }

  //Check if arg_2 is underscore or valid expression
  //TODO: milestone 1  - only handle partial matching or wildcard and only handle constant matching and variable matching
  bool valid_expr = arg_2[0] == '_' && arg_2[1] == '"' && arg_2[arg_2.length() - 2] == '"' && arg_2[arg_2.length() - 1] == '_' &&
      (LexicalRuleValidator::IsInteger(arg_2.substr(2, arg_2.length() - 4)) || LexicalRuleValidator::IsIdent(arg_2.substr(2, arg_2.length() - 4)));
  if (!QueryUtil::IsWildcard(arg_2) && !valid_expr) {
    throw SyntaxErrorException();
  }

  return;
}

void PatternHandler::HandleSemantic(ClauseSyntax *clause, Map &declaration) {
  std::string syn_assign(clause->GetEntity());
  std::string arg_1(clause->GetFirstParameter());

  //Check if syn_assign is declared and is 'assign' entity
  if (declaration.find(syn_assign) == declaration.end() || declaration[syn_assign] != pql_constants::kAssignEntity) {
    throw SemanticErrorException();
  }

  //If arg_1 is synonym, check if it is declared and is 'variable' entity
  if (QueryUtil::IsSynonym(arg_1) && declaration.find(syn_assign) == declaration.end()) {
    throw SemanticErrorException();
  }
  if (QueryUtil::IsSynonym(arg_1) && declaration[arg_1] != pql_constants::kVariableEntity) {
    throw SemanticErrorException();
  }

  return;
}
