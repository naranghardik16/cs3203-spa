#include "StmtProcToVarHandler.h"

const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";
const std::string kVariableEntity = "variable";
const std::unordered_set<std::string> kValidEntity({"stmt", "read", "print", "assign", "if", "while", "call", "procedure"});
const std::unordered_set<std::string> kRel({"Uses", "Modifies"});

void StmtProcToVarHandler::Handle(Map &declaration, Map &clause) {
  std::string &rel_ref(clause[kEntityKey]);

  if (kRel.find(rel_ref) == kRel.end()) {
    Handler::Handle(declaration, clause);
  }

  std::string &arg_1(clause[kFirstParameterKey]);
  std::string &arg_2(clause[kSecondParameterKey]);

  //Check if arg_1 is "_"
  if (LexicalRuleValidator::IsUnderscore(arg_1)) {
    throw SemanticErrorException();
  }

  //Check if arg_1 is stmtRef or entRef and if arg_2 is entRef
  if (!LexicalRuleValidator::IsStmtRef(arg_1) || !LexicalRuleValidator::IsEntRef(arg_1)) {
    throw SyntaxErrorException();
  }
  if (!LexicalRuleValidator::IsEntRef(arg_2)) {
    throw SyntaxErrorException();
  }

  //Check valid synonym for arg_1 and arg_2
  if (LexicalRuleValidator::IsSynonym(arg_1) && kValidEntity.find(declaration[arg_1]) == kValidEntity.end()) {
    throw SemanticErrorException();
  }
  if(LexicalRuleValidator::IsSynonym(arg_2) && declaration[arg_2] != kVariableEntity) {
    throw SemanticErrorException();
  }

  return;
}