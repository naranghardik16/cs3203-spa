#pragma once
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

ResultTable QueryUtil::ConvertSetToResultTableFormat(PkbCommunicationTypes::SingleConstraintSet s) {
  std::vector<std::vector<std::string>> result;
  for (const auto& kElem: s) {
    std::vector<std::string> nested_vector;
    nested_vector.push_back(kElem);
    result.push_back(nested_vector);
  }
  return result;
}

ResultTable QueryUtil::ConvertPairSetToResultTableFormat(PkbCommunicationTypes::PairConstraintSet s) {
  std::vector<std::vector<std::string>> result;
  for (const auto& kElem: s) {
    std::vector<std::string> nested_vector;
    nested_vector.push_back(kElem.first);
    nested_vector.push_back(kElem.second);
    result.push_back(nested_vector);
  }
  return result;
}


