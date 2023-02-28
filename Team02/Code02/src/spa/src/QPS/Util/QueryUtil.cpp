#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/PQLConstants.h"
#include "General/StatementTypeEnum.h"

bool QueryUtil::IsPartialMatchExpressionSpecification(const std::string& s) {
  bool result = s[0] == '_' && s[s.length()-1] == '_' &&s.length() > 2;
  return result;
}

bool QueryUtil::IsQuoted(const std::string& s) {
  return s.length() >= 2 && (s[0] == '"') && (s[s.length()-1] == '"');
}

bool QueryUtil::IsWildcard(const std::string& s) {
  return s == "_";
}


bool QueryUtil::IsAttrRef(const std::string& s) {
  std::vector<std::string> token_lst = SplitAttrRef(s);
  if (token_lst.size() != 2 ||  !IsSynonym(token_lst[0]) || pql_constants::kAttrName.find(token_lst[1]) == pql_constants::kAttrName.end()) {
    return false;
  }
  return true;
}

bool QueryUtil::IsSynonym(const std::string& s) {
  return LexicalRuleValidator::IsIdent(s);
}

bool QueryUtil::IsStmtRef(const std::string& s) {
  return (IsWildcard(s) || IsSynonym(s) || LexicalRuleValidator::IsInteger(s));
}

bool QueryUtil::IsEntRef(const std::string& s) {
  bool is_ident_in_quotation = (s[0] == '"' && LexicalRuleValidator::IsIdent(s.substr(1, s.length() - 2)) && s[s.length()-1] == '"');
  return (IsWildcard(s) || IsSynonym(s) || is_ident_in_quotation);
}

bool QueryUtil::IsDesignEntity(const std::string& s) {
  return s == pql_constants::kPqlStatementEntity || s == pql_constants::kPqlReadEntity || s == pql_constants::kPqlPrintEntity
  || s == pql_constants::kPqlCallEntity || s == pql_constants::kPqlWhileEntity || s == pql_constants::kPqlIfEntity ||
  s == pql_constants::kPqlAssignEntity || s == pql_constants::kPqlVariableEntity || s == pql_constants::kPqlConstantEntity ||
  s == pql_constants::kPqlProcedureEntity;
}

bool QueryUtil::IsRelationshipReference(const std::string& s) {
  return s == pql_constants::kPqlFollowsRel || s == pql_constants::kPqlFollowsRel  || s == pql_constants::kPqlParentRel
  || s == pql_constants::kPqlFollowsRel  || s == pql_constants::kPqlUsesRel  || s == pql_constants::kPqlModifiesRel ;
}

bool QueryUtil::IsVariableSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlVariableEntity);
}

bool QueryUtil::IsConstantSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlConstantEntity);
}


bool QueryUtil::IsStatementSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlStatementEntity);
}

bool QueryUtil::IsReadSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlReadEntity);
}

/*
* Checks if the expression is a print synonym
*/
bool QueryUtil::IsPrintSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlPrintEntity);
}

bool QueryUtil::IsCallSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlCallEntity);
}


bool QueryUtil::IsWhileSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlWhileEntity);
}

/*
* Checks if the expression is an if synonym
*/
bool QueryUtil::IsIfSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlIfEntity);
}

bool QueryUtil::IsAssignSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlAssignEntity);
}

bool QueryUtil::IsATypeOfStatementSynonym(Map &declaration, const std::string& expression) {
  //check if synonym first
  if (declaration.count(expression) == 0) {
    return false;
  }

  return !IsVariableSynonym(declaration, expression) && !IsConstantSynonym(declaration, expression)
  && !IsProcedureSynonym(declaration, expression);
}

bool QueryUtil::IsProcedureSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlProcedureEntity);
}

bool QueryUtil::IsCorrectSynonymType(Map &declaration, const std::string &expression, const std::string type) {
  if (declaration.count(expression) == 0) {
    return false;
  }

  std::string t = declaration[expression];
  return t == type;
}

std::string QueryUtil::GetIdent(const std::string& quoted_ident) {
  return string_util::Trim(quoted_ident.substr(1, quoted_ident.length() - 2));
}

StatementType QueryUtil::GetStatementType(Map &declaration, const std::string& synonym) {
  if (IsIfSynonym(declaration, synonym)) {
    return StatementType::IF;
  } else if (IsReadSynonym(declaration, synonym)) {
    return StatementType::READ;
  } else if (IsPrintSynonym(declaration, synonym)) {
    return StatementType::PRINT;
  } else if (IsCallSynonym(declaration, synonym)) {
    return StatementType::CALL;
  } else if (IsAssignSynonym(declaration, synonym)) {
    return StatementType::ASSIGN;
  } else if (IsWhileSynonym(declaration, synonym)){
    return StatementType::WHILE;
  } else if (IsStatementSynonym(declaration, synonym)){
    return StatementType::STATEMENT;
  } else {
    return StatementType::UNK;
  }
}

std::vector<std::string> QueryUtil::SplitAttrRef(const std::string &s) {
  std::stringstream attr_ref(s);
  std::vector<std::string> token_lst;

  for (std::string token; std::getline(attr_ref, token, '.'); ) {
    token_lst.push_back(string_util::Trim(token));
  }

  return token_lst;
}


std::string QueryUtil::GetAttrNameFromAttrRef(std::string attrRef) {
  auto token_lst = SplitAttrRef(attrRef);
  return token_lst[1];
}

std::string QueryUtil::GetSynonymFromAttrRef(std::string attrRef) {
  auto token_lst = SplitAttrRef(attrRef);
  return token_lst[0];
}


bool QueryUtil::IsMismatchingAttrRef(std::string attrRef_1, std::string attrRef_2) {
  auto attr_name_1 = GetAttrNameFromAttrRef(attrRef_1);
  auto attr_name_2 = GetAttrNameFromAttrRef(attrRef_2);

  bool is_attr_name_1_return_int = ((attr_name_1 == pql_constants::kStmtNo) || (attr_name_1 == pql_constants::kValue));
  bool is_attr_name_2_return_int = ((attr_name_2 == pql_constants::kStmtNo) || (attr_name_2 == pql_constants::kValue));
  bool both_return_int = is_attr_name_1_return_int && is_attr_name_2_return_int;

  bool is_attr_name_1_return_ident = ((attr_name_1 == pql_constants::kProcName) || (attr_name_1 == pql_constants::kVarname));
  bool is_attr_name_2_return_ident = ((attr_name_2 == pql_constants::kProcName) || (attr_name_2 == pql_constants::kVarname));
  bool both_return_ident = is_attr_name_1_return_ident && is_attr_name_2_return_ident;

  if (!both_return_ident && !both_return_int) {
    return false;
  } else {
    return true;
  }
}

bool QueryUtil::IsTrivialAttrRefWithNoResult(std::string attrRef, std::string comparison_value) {
  auto attr_name = GetAttrNameFromAttrRef(attrRef);

  bool is_attr_name_return_int = ((attr_name == pql_constants::kStmtNo) || (attr_name == pql_constants::kValue));
  //either IDENT or INT
  //e.g. a.stmt# = ""v""
  bool is_comparison_value_int = LexicalRuleValidator::IsInteger(comparison_value);
  if (is_attr_name_return_int) {
    return is_comparison_value_int;
  } else {
    //attr_name return ident -- e.g. procName or varName which must follow the NAME lexical rule and cannot be an integer
    //e.g. p.procName = "5"
    return !is_comparison_value_int;
  }
}


