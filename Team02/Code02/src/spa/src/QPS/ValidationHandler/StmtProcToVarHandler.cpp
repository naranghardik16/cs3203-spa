#include "StmtProcToVarHandler.h"
#include "QPS/Util/QueryUtil.h"

const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";
const std::string kVariableEntity = "variable";
const std::unordered_set<std::string> kValidEntity({"stmt", "read", "print", "assign", "if", "while", "call", "procedure"});
const std::unordered_set<std::string> kRel({"Uses", "Modifies"});

void StmtProcToVarHandler::Handle(Map &declaration, Map &clause) {
  std::string &rel_ref(clause[kEntityKey]);

  if (kRel.find(rel_ref) == kRel.end()) {
    return Handler::Handle(declaration, clause);
  }

  std::string &arg_1(clause[kFirstParameterKey]);
  std::string &arg_2(clause[kSecondParameterKey]);

  //Check if arg_1 is "_"
  if (QueryUtil::IsWildcard(arg_1)) {
    throw SemanticErrorException();
  }

  //Check if arg_1 is stmtRef or entRef and if arg_2 is entRef
  if (!QueryUtil::IsStmtRef(arg_1) || !QueryUtil::IsEntRef(arg_1)) {
    throw SyntaxErrorException();
  }
  if (!QueryUtil::IsEntRef(arg_2)) {
    throw SyntaxErrorException();
  }

  //Check valid synonym for arg_1 and arg_2
  if (QueryUtil::IsSynonym(arg_1) && kValidEntity.find(declaration[arg_1]) == kValidEntity.end()) {
    throw SemanticErrorException();
  }
  if(QueryUtil::IsSynonym(arg_2) && declaration[arg_2] != kVariableEntity) {
    throw SemanticErrorException();
  }

  return;
}