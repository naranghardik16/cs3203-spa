#include "PatternHandler.h"

void PatternHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::string syn(clause->GetEntity());
  ParameterVector args(clause->GetParameters());

  if (args.size() != pql_constants::kPairArgumentValidSize && args.size() != pql_constants::kTripleArgumentValidSize) {
    throw SyntaxErrorException("Invalid number of argument");
  }

  if (!QueryUtil::IsSynonym(syn) || !QueryUtil::IsEntRef(args[0])) {
    throw SyntaxErrorException("Invalid synonym or entity reference");
  }
  if (args.size() == pql_constants::kPairArgumentValidSize) {
    clause->SetExpression(ExpressionSpecParser::ParseExpressionSpec(args[1]));
  }
  if (args.size() ==  pql_constants::kTripleArgumentValidSize && (!QueryUtil::IsWildcard(args[1]) ||
  !QueryUtil::IsWildcard(args[2]))) {
    throw SyntaxErrorException("Invalid if pattern syntax");
  }

  return;
}

void PatternHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string syn(clause->GetEntity());
  ParameterVector args(clause->GetParameters());

  // Check if syn is declared and is correct entity
  if (declaration.find(syn) == declaration.end()) {
    throw SemanticErrorException();
  }

  if (args.size() == pql_constants::kPairArgumentValidSize) {
    bool is_arg_2_wildcard = QueryUtil::IsWildcard(args[1]);
    if (!is_arg_2_wildcard && declaration[syn] != pql_constants::kPqlAssignEntity) {
      throw SemanticErrorException();
    }
    if (is_arg_2_wildcard && declaration[syn] != pql_constants::kPqlAssignEntity
    && declaration[syn] != pql_constants::kPqlWhileEntity) {
      throw SemanticErrorException();
    }
  }
  if (args.size() == pql_constants::kTripleArgumentValidSize && declaration[syn] != pql_constants::kPqlIfEntity) {
    throw SemanticErrorException();
  }

  // If arg_1 is synonym, check if it is declared and is 'variable' entity
  bool is_syn = QueryUtil::IsSynonym(args[0]);
  if (is_syn && declaration.find(args[0]) == declaration.end()) {
    throw SemanticErrorException(args[0] + "is a synonym that is not declared");
  }
  if (is_syn && declaration[args[0]] != pql_constants::kPqlVariableEntity) {
    throw SemanticErrorException(args[0] + "is not a variable entity");
  }
  clause->syn_.insert(syn);
  if (is_syn) {
    clause->syn_.insert(args[0]);
  }

  return;
}
