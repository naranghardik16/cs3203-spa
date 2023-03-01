#include "WithHandler.h"

void WithHandler::HandleSyntax(std::shared_ptr<ClauseSyntax> clause) {
  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  if (!LexicalRuleValidator::IsIdent(arg_1) && !LexicalRuleValidator::IsInteger(arg_1) && !QueryUtil::IsAttrRef(arg_1)) {
    throw SyntaxErrorException("Argument 1 is not a valid ref: " + arg_1);
  }

  if (!LexicalRuleValidator::IsIdent(arg_2) && !LexicalRuleValidator::IsInteger(arg_2) && !QueryUtil::IsAttrRef(arg_2)) {
    throw SyntaxErrorException("Argument 2 is not a valid ref: " + arg_2);
  }
}

void WithHandler::HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration) {
  std::string arg_1(clause->GetFirstParameter());
  std::string arg_2(clause->GetSecondParameter());

  bool is_first_arg_an_attr_ref = QueryUtil::IsAttrRef(arg_1);
  bool is_second_arg_an_attr_ref = QueryUtil::IsAttrRef(arg_2);

  if (is_first_arg_an_attr_ref) {
    CheckAttrRef(arg_1, declaration);
  }
  if (is_second_arg_an_attr_ref) {
    CheckAttrRef(arg_2, declaration);
  }
  if (GetAttrType(arg_1) != GetAttrType(arg_2)) {
    throw SemanticErrorException("Invalid comparison");
  }
}

void WithHandler::CheckAttrRef(std::string &ref, Map &declaration) {
  std::vector<std::string> token_lst = QueryUtil::SplitAttrRef(ref);
  auto it = declaration.find(token_lst[0]);
  if (it == declaration.end()) {
    throw SemanticErrorException("The synonym not declared: " + ref);
  }
  auto attr_name = pql_constants::kEntityToAttrName.at(it->second);
  if (attr_name.find(token_lst[1]) == attr_name.end()) {
    throw SemanticErrorException("The attr is invalid: " + ref);
  }
}

std::string WithHandler::GetAttrType(std::string &ref) {
  if (LexicalRuleValidator::IsIdent(ref)) {
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
