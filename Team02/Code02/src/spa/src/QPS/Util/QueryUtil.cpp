#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/PQLConstants.h"
#include "General/StatementTypeEnum.h"

bool QueryUtil::IsPartialMatchExpressionSpecification(const std::string& s) {
  bool result = s[0] == '_' && s[s.length() - 1] == '_' && s.length() > 2;
  return result;
}

bool QueryUtil::IsQuoted(const std::string& s) {
  return s.length() >= 2 && (s[0] == '"') && (s[s.length()-1] == '"');
}

bool QueryUtil::IsQuotedIdent(const std::string &s) {
  return (s[0] == '"' && LexicalRuleValidator::IsIdent(s.substr(1, s.length() - 2)) && s[s.length()-1] == '"');
}

bool QueryUtil::IsWildcard(const std::string& s) {
  return s == "_";
}

bool QueryUtil::IsAttrRef(const std::string& s) {
  std::vector<std::string> token_lst = SplitAttrRef(s);
  if (token_lst.size() != 2 || !IsSynonym(token_lst[0]) || pql_constants::kAttrName.find(token_lst[1]) == pql_constants::kAttrName.end()) {
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
  return (IsWildcard(s) || IsSynonym(s) || IsQuotedIdent(s));
}

bool QueryUtil::IsRef(const std::string &s) {
  return IsQuotedIdent(s) || LexicalRuleValidator::IsInteger(s) || IsAttrRef(s);
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


std::string QueryUtil::AdjustSynonymWithTrivialAttrRefValue(Synonym syn, Map &declaration_map) {
  auto token_lst = QueryUtil::SplitAttrRef(syn);
  if (token_lst.size() == 2) {
    bool is_trivial_attr_name = IsTrivialAttrRef(token_lst, declaration_map);
    if (is_trivial_attr_name) {
      return token_lst[0];
    }
  }
  return syn;
}

bool QueryUtil::IsTrivialAttrRef(std::vector<std::string> attr_ref_token_lst, Map &declaration_map) {
  //! remove trivial attr name e.g. r.stmt# is same as r except for c.procName, read.varName and print.varName
  bool is_call_proc_name_attr_ref = (declaration_map[attr_ref_token_lst[0]] == pql_constants::kPqlCallEntity) && (attr_ref_token_lst[1] == pql_constants::kProcName);
  bool is_read_var_name_attr_ref = (declaration_map[attr_ref_token_lst[0]] == pql_constants::kPqlReadEntity) && (attr_ref_token_lst[1] == pql_constants::kVarname);
  bool is_print_var_name_attr_ref = (declaration_map[attr_ref_token_lst[0]] == pql_constants::kPqlPrintEntity) && (attr_ref_token_lst[1] == pql_constants::kVarname);
  return !is_call_proc_name_attr_ref && !is_read_var_name_attr_ref && !is_print_var_name_attr_ref;
}
