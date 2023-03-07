#include "CallsHandler.h"

void CallsHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::string rel_ref(clause->GetEntity());

  if (!CanHandler(rel_ref)) {
    return Handler::HandleSyntax(clause);
  }

  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  //Check if is valid stmtRef
  if (!QueryUtil::IsEntRef(arg_1) || !QueryUtil::IsEntRef(arg_2)) {
    throw SyntaxErrorException("The statement reference was not valid");
  }

  return;
}

void CallsHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string rel_ref(clause->GetEntity());

  if (!CanHandler(rel_ref)) {
    return Handler::HandleSemantic(clause, declaration);
  }

  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  //Check if synonym is procedure synonym
  if (QueryUtil::IsSynonym(arg_1) && declaration[arg_1] != pql_constants::kPqlProcedureEntity) {
    throw SemanticErrorException("The synonym is not assign statement synonym");
  }
  if (QueryUtil::IsSynonym(arg_2) && declaration[arg_2] != pql_constants::kPqlProcedureEntity) {
    throw SemanticErrorException("The synonym is not assign statement synonym");
  }

  return;
}

bool CallsHandler::CanHandler(std::string &rel_ref) {
  return rel_ref == pql_constants::kPqlCallsRel || rel_ref == pql_constants::kPqlCallsStarRel;
}
