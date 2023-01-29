#include "SuchThatBaseHandler.h"

const std::unordered_set<std::string> kRelRef({"Follows", "Follows*", "Parent", "Parent*", "Uses", "Modifies"});
const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

void SuchThatBaseHandler::Handle(Map &declaration, Map &clause) {
  //Check if got such that clause
  if (clause.empty()) {
    return;
  }

  std::string &rel_ref(clause[kEntityKey]);
  std::string &arg_1(clause[kFirstParameterKey]);
  std::string &arg_2(clause[kSecondParameterKey]);

  //Check if relRef valid
  if (kRelRef.find(rel_ref) == kRelRef.end()) {
    throw SyntaxErrorException();
  }

  //Check if synonyms declared
  if (LexicalRuleValidator::IsSynonym(arg_1) && declaration.find(arg_1) == declaration.end()) {
    throw SemanticErrorException();
  }
  if (LexicalRuleValidator::IsSynonym(arg_2) && declaration.find(arg_2) == declaration.end()) {
    throw SemanticErrorException();
  }

  Handler::Handle(declaration, clause);
}
