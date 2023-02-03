#include "PatternHandler.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Util/QPSTypeDefs.h"
const std::string kEntityKey = "Entity";
const std::string kAssignEntity = "assign";
const std::string kVariableEntity = "variable";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

void PatternHandler::Handle(Map &declaration, Map &clause) {
  //Check if got pattern clause
  if (clause.empty()) {
    return;
  }

  std::string &syn_assign(clause[kEntityKey]);
  std::string &arg_1(clause[kFirstParameterKey]);
  std::string &arg_2(clause[kSecondParameterKey]);

  if (!QueryUtil::IsSynonym(syn_assign) || !QueryUtil::IsEntRef(arg_1)) {
    throw SyntaxErrorException();
  }

  //Check if syn_assign is declared and is 'assign' entity
  if (declaration.find(syn_assign) == declaration.end() || declaration[syn_assign] != kAssignEntity) {
    throw SemanticErrorException();
  }

  //If arg_1 is synonym, check if it is declared and is 'variable' entity
  if (QueryUtil::IsSynonym(arg_1) && declaration.find(syn_assign) == declaration.end()) {
    throw SemanticErrorException();
  }
  if (QueryUtil::IsSynonym(arg_1) && declaration[arg_1] != kVariableEntity) {
    throw SemanticErrorException();
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
