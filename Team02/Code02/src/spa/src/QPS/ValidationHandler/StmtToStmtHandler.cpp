#include "StmtToStmtHandler.h"
#include "QPS/QueryUtil.h"
#include <iostream>

const std::unordered_set<std::string> kRel({"Follows", "Follows*", "Parent", "Parent*"});
const std::unordered_set<std::string> kStmtEntity({"stmt", "read", "print", "assign", "if", "while", "call"});
const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

void StmtToStmtHandler::Handle(Map &declaration, Map &clause) {
  std::string &rel_ref(clause[kEntityKey]);

  if (kRel.find(rel_ref) == kRel.end()) {
    return Handler::Handle(declaration, clause);
  }

  std::string &arg_1(clause[kFirstParameterKey]);
  std::string &arg_2(clause[kSecondParameterKey]);

  //Check if is valid stmtRef
  if (!QueryUtil::IsStmtRef(arg_1) || !QueryUtil::IsStmtRef(arg_2)) {
    throw SyntaxErrorException();
  }

  //Check if synonym is a statement synonym or its subset
  if (QueryUtil::IsSynonym(arg_1) && kStmtEntity.find(declaration[arg_1]) == kStmtEntity.end()) {
    throw SemanticErrorException();
  }
  if (QueryUtil::IsSynonym(arg_2) && kStmtEntity.find(declaration[arg_2]) == kStmtEntity.end()) {
    throw SemanticErrorException();
  }

  return;
}
