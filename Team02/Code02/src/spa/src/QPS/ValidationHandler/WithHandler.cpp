#include "WithHandler.h"

void WithHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  if (clause->GetParameters().size() != 2) {
    throw SyntaxErrorException("Invalid number of argument");
  }

  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  if (!QueryUtil::IsRef(arg_1)) {
    throw SyntaxErrorException("Argument 1 is not a valid ref: " + arg_1);
  }

  if (!QueryUtil::IsRef(arg_2)) {
    throw SyntaxErrorException("Argument 2 is not a valid ref: " + arg_2);
  }
}

void WithHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  bool is_first_arg_an_attr_ref = QueryUtil::IsAttrRef(arg_1);
  bool is_second_arg_an_attr_ref = QueryUtil::IsAttrRef(arg_2);

  if (is_first_arg_an_attr_ref) {
    clause->syn_.insert(CheckAttrRef(arg_1, declaration));
  }
  if (is_second_arg_an_attr_ref) {
    clause->syn_.insert(CheckAttrRef(arg_2, declaration));
  }
  if (GetAttrType(arg_1) != GetAttrType(arg_2)) {
    throw SemanticErrorException("Invalid comparison");
  }
}

std::string WithHandler::CheckAttrRef(std::string &ref, Map &declaration) {
  std::vector<std::string> token_lst = QueryUtil::SplitAttrRef(ref);
  auto it = declaration.find(token_lst[0]);
  if (it == declaration.end()) {
    throw SemanticErrorException("The synonym not declared: " + ref);
  }
  auto attr_name = pql_constants::kEntityToAttrName.at(it->second);
  if (attr_name.find(token_lst[1]) == attr_name.end()) {
    throw SemanticErrorException("The attr is invalid: " + ref);
  }
  return token_lst[0];
}

std::string WithHandler::GetAttrType(std::string &ref) {
  if (QueryUtil::IsQuotedIdent(ref)) {
    return "STR";
  }
  if (LexicalRuleValidator::IsInteger(ref)) {
    return "INT";
  }
  auto attr_name = QueryUtil::GetAttrNameFromAttrRef(ref);
  if (attr_name == pql_constants::kProcName || attr_name == pql_constants::kVarname) {
    return "STR";
  }
  return "INT";
}
