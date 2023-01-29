#include "FollowHandler.h"

const std::unordered_set<std::string> kStmtEntity({"stmt", "read", "print", "assign", "if", "while", "call"});
const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

void FollowHandler::Handle(Map &declaration, Map &clause) {
  std::string &rel_ref(clause[kEntityKey]);

  if (rel_ref != "Follows" || rel_ref != "Follows*") {
    Handler::Handle(declaration, clause);
  }

  std::string &arg_1(clause[kFirstParameterKey]);
  std::string &arg_2(clause[kSecondParameterKey]);

  //Check if is valid stmtRef
  if (!LexicalRuleValidator::IsStmtRef(arg_1) || !LexicalRuleValidator::IsStmtRef(arg_2)) {
    throw SyntaxErrorException();
  }

  //Check if synonym is a statement synonym or its subset
  if (LexicalRuleValidator::IsSynonym(arg_1) && kStmtEntity.find(declaration[arg_1]) == kStmtEntity.end()) {
    throw SemanticErrorException();
  }
  if (LexicalRuleValidator::IsSynonym(arg_2) && kStmtEntity.find(declaration[arg_2]) == kStmtEntity.end()) {
    throw SemanticErrorException();
  }

  return;
}
