#include "PatternHandler.h"

void PatternHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::string syn_assign(clause->GetEntity());
  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  if (!QueryUtil::IsSynonym(syn_assign) || !QueryUtil::IsEntRef(arg_1)) {
    throw SyntaxErrorException();
  }

  return;
}

void PatternHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string syn_assign(clause->GetEntity());
  std::string arg_1(clause->GetFirstParameter());

  //Check if syn_assign is declared and is 'assign' entity
  if (declaration.find(syn_assign) == declaration.end() || declaration[syn_assign] != pql_constants::kPqlAssignEntity) {
    throw SemanticErrorException();
  }

  //If arg_1 is synonym, check if it is declared and is 'variable' entity
  if (QueryUtil::IsSynonym(arg_1) && declaration.find(syn_assign) == declaration.end()) {
    throw SemanticErrorException();
  }
  if (QueryUtil::IsSynonym(arg_1) && declaration[arg_1] != pql_constants::kPqlVariableEntity) {
    throw SemanticErrorException();
  }

  return;
}
