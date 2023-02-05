#pragma once
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Util/QPSTypeDefs.h"
#include <algorithm>
#include "QPS/Util/PQLConstants.h"
#include "General/SpaException/SyntaxErrorException.h"

/*
* Checks if the expression is a variable synonym
* */
bool QueryUtil::IsPartialMatchExpressionSpecification(const std::string& s) {
  bool result = s[0] == '_' && s[s.length()-1] == '_';
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
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlVariableEntity;
  return result;
}

/*
* Checks if the expression is a constant synonym
*/
bool QueryUtil::IsConstantSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlConstantEntity;
  return result;
}

/*
* Checks if the expression is a statement synonym
*/
bool QueryUtil::IsStatementSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlStatementEntity;
  return result;
}


/*
* Checks if the expression is a read synonym
*/
bool QueryUtil::IsReadSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlReadEntity;
  return result;
}

/*
* Checks if the expression is a print synonym
*/
bool QueryUtil::IsPrintSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlPrintEntity;
  return result;
}

/*
* Checks if the expression is a call synonym
*/
bool QueryUtil::IsCallSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlCallEntity;
  return result;
}

/*
* Checks if the expression is a while synonym
*/
bool QueryUtil::IsWhileSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == "while";
  return result;
}

/*
* Checks if the expression is an if synonym
*/
bool QueryUtil::IsIfSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlIfEntity;
  return result;
}


/*
* Checks if the expression is an assign synonym
*/
bool QueryUtil::IsAssignSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlAssignEntity;
  return result;
}

/*
* Checks if the expression is a container statement.
*/
bool QueryUtil::IsContainerStatementSynonym(Map &declaration, const std::string& expression) {
  bool result = IsIfSynonym(declaration, expression) || IsWhileSynonym(declaration, expression);
  return result;
}


/*
* Checks if the expression is a procedure synonym
*/
bool QueryUtil::IsProcedureSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == pql_constants::kPqlProcedureEntity;
  return result;
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

