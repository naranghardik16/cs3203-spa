#include "SuchThatBaseHandler.h"

void SuchThatBaseHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::string rel_ref(clause->GetEntity());

  // Check if relRef valid
  if (pql_constants::kRelRefs.find(rel_ref) == pql_constants::kRelRefs.end()) {
    throw SyntaxErrorException("The relationship reference is invalid in the Such That clause");
  }
  if (clause->GetParameters().size() != pql_constants::kPairArgumentValidSize) {
    throw SyntaxErrorException("Invalid number of argument");
  }

  return Handler::HandleSyntax(clause);
}

void SuchThatBaseHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());


  if (QueryUtil::IsSynonym(arg_1) && declaration.find(arg_1) == declaration.end()) {
    throw SemanticErrorException("The synonym in the first argument was not declared");
  }
  if (QueryUtil::IsSynonym(arg_2) && declaration.find(arg_2) == declaration.end()) {
    throw SemanticErrorException("The synonym in the second argument was not declared");
  }
  if (QueryUtil::IsSynonym(arg_1)) {
    clause->syn_.insert(arg_1);
  }
  if (QueryUtil::IsSynonym(arg_2)) {
    clause->syn_.insert(arg_2);
  }

  return Handler::HandleSemantic(clause, declaration);
}
