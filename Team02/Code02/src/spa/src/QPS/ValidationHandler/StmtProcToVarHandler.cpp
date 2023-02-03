#include "StmtProcToVarHandler.h"

void StmtProcToVarHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::string rel_ref(clause->GetEntity());

  if (!CanHandler(rel_ref)) {
    return Handler::HandleSyntax(clause);
  }

  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  //Check if arg_1 is stmtRef or entRef and if arg_2 is entRef
  if (!QueryUtil::IsStmtRef(arg_1) || !QueryUtil::IsEntRef(arg_1)) {
    throw SyntaxErrorException();
  }
  if (!QueryUtil::IsEntRef(arg_2)) {
    throw SyntaxErrorException();
  }

  return;
}

void StmtProcToVarHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string rel_ref(clause->GetEntity());

  if (!CanHandler(rel_ref)) {
    return Handler::HandleSemantic(clause, declaration);
  }

  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  //Check if arg_1 is "_"
  if (QueryUtil::IsWildcard(arg_1)) {
    throw SemanticErrorException();
  }

  //Check valid synonym for arg_1 and arg_2
  if (QueryUtil::IsSynonym(arg_1) && pql_constants::kStmtProcRefEntities.find(declaration[arg_1]) == pql_constants::kStmtProcRefEntities.end()) {
    throw SemanticErrorException();
  }
  if(QueryUtil::IsSynonym(arg_2) && declaration[arg_2] != pql_constants::kVariableEntity) {
    throw SemanticErrorException();
  }

  return;
}

bool StmtProcToVarHandler::CanHandler(std::string &rel_ref) {
  return pql_constants::kStmtProcToStmtRel.find(rel_ref) != pql_constants::kStmtProcToStmtRel.end();
}
