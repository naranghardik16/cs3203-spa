#include "PatternHandler.h"

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
  std::string &arg_2(clause[kSecondParameterKey]); //TODO: validate expr

  if (!LexicalRuleValidator::IsSynonym(syn_assign) || !LexicalRuleValidator::IsEntRef(arg_1)) {
    throw SyntaxErrorException();
  }

  //Check if syn_assign is declared and is 'assign' entity
  if (declaration.find(syn_assign) == declaration.end() || declaration[syn_assign] != kAssignEntity) {
    throw SemanticErrorException();
  }

  //If arg_1 is synonym, check if it is declared and is 'variable' entity
  if (LexicalRuleValidator::IsSynonym(arg_1) && declaration.find(syn_assign) != declaration.end()) {
    throw SemanticErrorException();
  }
  if (LexicalRuleValidator::IsSynonym(arg_1) && declaration[arg_1] != kVariableEntity) {
    throw SemanticErrorException();
  }

  return;
}
