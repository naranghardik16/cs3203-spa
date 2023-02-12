#pragma once
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/PQLConstants.h"
#include "General/StatementTypeEnum.h"

/*
* Checks if the expression is a variable synonym
* */
bool QueryUtil::IsPartialMatchExpressionSpecification(const std::string& s) {
  bool result = s[0] == '_' && s[s.length()-1] == '_' &&s.length() > 2;
  return result;
}

/*
 * Checks if a string is quoted.
 */
bool QueryUtil::IsQuoted(const std::string& s) {
  return (s[0] == '"') && (s[s.length()-1] == '"');
}

/*
 * Validates a wildcard token.
 */
bool QueryUtil::IsWildcard(const std::string& s) {
  return s == "_";
}

/*
 * Validates a SYNONYM lexical token in PQL.
 */
bool QueryUtil::IsSynonym(const std::string& s) {
  return LexicalRuleValidator::IsIdent(s);
}

/*
 * Validates a Statement Reference in PQL.
 */
bool QueryUtil::IsStmtRef(const std::string& s) {
  return (IsWildcard(s) || IsSynonym(s) || LexicalRuleValidator::IsInteger(s));
}
/*
 * Validates an Entity Reference in PQL.
 */
bool QueryUtil::IsEntRef(const std::string& s) {
  bool is_ident_in_quotation = (s[0] == '"' && LexicalRuleValidator::IsIdent(s.substr(1, s.length() - 2)) && s[s.length()-1] == '"');
  return (IsWildcard(s) || IsSynonym(s) || is_ident_in_quotation);
}

/*
 * Validates if a string is a Design Entity in PQL.
 */
bool QueryUtil::IsDesignEntity(const std::string& s) {
  return s == pql_constants::kPqlStatementEntity || s == pql_constants::kPqlReadEntity || s == pql_constants::kPqlPrintEntity
  || s == pql_constants::kPqlCallEntity || s == pql_constants::kPqlWhileEntity || s == pql_constants::kPqlIfEntity ||
  s == pql_constants::kPqlAssignEntity || s == pql_constants::kPqlVariableEntity || s == pql_constants::kPqlConstantEntity ||
  s == pql_constants::kPqlProcedureEntity;
}

/*
 * Validates if a string is a Relationship Reference.
 */
bool QueryUtil::IsRelationshipReference(const std::string& s) {
  return s == pql_constants::kPqlFollowsRel || s == pql_constants::kPqlFollowsRel  || s == pql_constants::kPqlParentRel
  || s == pql_constants::kPqlFollowsRel  || s == pql_constants::kPqlUsesRel  || s == pql_constants::kPqlModifiesRel ;
}


/*
 * Checks if the string is quoted, which is a character string
 * */
bool QueryUtil::IsCharacterString(const std::string& s) {
  bool result = s[0] == '"' && s[s.length()-1] == '"';
  return result;
}

/*
* Checks if the expression is a variable synonym
*/
bool QueryUtil::IsVariableSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlVariableEntity);
}

/*
* Checks if the expression is a constant synonym
*/
bool QueryUtil::IsConstantSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlConstantEntity);
}

/*
* Checks if the expression is a statement synonym
*/
bool QueryUtil::IsStatementSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlStatementEntity);
}


/*
* Checks if the expression is a read synonym
*/
bool QueryUtil::IsReadSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlReadEntity);
}

/*
* Checks if the expression is a print synonym
*/
bool QueryUtil::IsPrintSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlPrintEntity);
}

/*
* Checks if the expression is a call synonym
*/
bool QueryUtil::IsCallSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlCallEntity);
}

/*
* Checks if the expression is a while synonym
*/
bool QueryUtil::IsWhileSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlWhileEntity);
}

/*
* Checks if the expression is an if synonym
*/
bool QueryUtil::IsIfSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlIfEntity);
}


/*
* Checks if the expression is an assign synonym
*/
bool QueryUtil::IsAssignSynonym(Map &declaration, const std::string& expression) {
  return IsCorrectSynonymType(declaration, expression, pql_constants::kPqlAssignEntity);
}

/*
* Checks if the expression is a container statement.
*/
bool QueryUtil::IsContainerStatementSynonym(Map &declaration, const std::string& expression) {
  bool result = IsIfSynonym(declaration, expression) || IsWhileSynonym(declaration, expression);
  return result;
}

/*
 * Checks if the synonym belongs to the category of a statement synonym
 */
bool QueryUtil::IsATypeOfStatementSynonym(Map &declaration, const std::string& expression) {
  //check if synonym first
  if (declaration.count(expression) == 0) {
    return false;
  }

  return !IsVariableSynonym(declaration, expression) && !IsConstantSynonym(declaration, expression)
  && !IsProcedureSynonym(declaration, expression);
}

/*
* Checks if the expression is a procedure synonym
*/
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

/**
 * Returns a statement type enum based on a given synonym
 */
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

/*
 * Converts a vector to an unordered set
 */
std::unordered_set<std::string> QueryUtil::ConvertToSet(std::vector<std::vector<std::string>> v) {
  std::unordered_set<std::string> set;
  for (int i = 0; i < v.size(); i++) {
    auto nested_vector = v[i];
    set.insert(nested_vector[0]);
  }

  return set;
}

/**
 * Extract the first of a vector in a vector of vectors
 */
std::vector<std::vector<std::string>> QueryUtil::ExtractFirstElementInTheVectors(std::vector<std::vector<std::string>> v) {
  std::vector<std::vector<std::string>> result;
  for (int i = 0; i < v.size(); i++) {
    auto nested_vector = v[i];
    std::vector<std::string> new_vector = {nested_vector[0]};
    result.push_back(new_vector);
  }
  return result;
}


/**
 * Converts an unordered set to a ResultRow format
 */
ResultTable QueryUtil::ConvertSetToResultTableFormat(PkbCommunicationTypes::SingleConstraintSet s) {
  std::vector<std::vector<std::string>> result;
  for (const auto& kElem: s) {
    std::vector<std::string> nested_vector;
    nested_vector.push_back(kElem);
    result.push_back(nested_vector);
  }
  return result;
}

/**
 * Converts an unordered set of pairs to a ResultRow format
 */
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


/**
 * Extract the 2nd element of a vector in a vector of vectors
 */
std::vector<std::vector<std::string>> QueryUtil::ExtractSecondElementInTheVectors(std::vector<std::vector<std::string>> v) {
  std::vector<std::vector<std::string>> result;
  for (int i = 0; i < v.size(); i++) {
    auto nested_vector = v[i];
    std::vector<std::string> new_vector = {nested_vector[1]};
    result.push_back(new_vector);
  }
  return result;
}
