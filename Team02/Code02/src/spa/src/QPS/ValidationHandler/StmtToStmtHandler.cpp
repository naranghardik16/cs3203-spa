#include "StmtToStmtHandler.h"

void StmtToStmtHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::string rel_ref(clause->GetEntity());

  if (!CanHandler(rel_ref)) {
    return Handler::HandleSyntax(clause);
  }

  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  //Check if is valid stmtRef
  if (!QueryUtil::IsStmtRef(arg_1) || !QueryUtil::IsStmtRef(arg_2)) {
    throw SyntaxErrorException();
  }

  return;
}

void StmtToStmtHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string rel_ref(clause->GetEntity());

  if (!CanHandler(rel_ref)) {
    return Handler::HandleSemantic(clause, declaration);
  }

  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  //Check if synonym is a statement synonym or its subset
  if (QueryUtil::IsSynonym(arg_1) && pql_constants::kStmtRefEntities.find(declaration[arg_1]) == pql_constants::kStmtRefEntities.end()) {
    throw SemanticErrorException();
  }
  if (QueryUtil::IsSynonym(arg_2) && pql_constants::kStmtRefEntities.find(declaration[arg_2]) == pql_constants::kStmtRefEntities.end()) {
    throw SemanticErrorException();
  }

  return;
}

bool StmtToStmtHandler::CanHandler(std::string &rel_ref) {
  return pql_constants::kStmtToStmtRel.find(rel_ref) != pql_constants::kStmtToStmtRel.end();
}
