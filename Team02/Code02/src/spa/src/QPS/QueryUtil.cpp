#pragma once
#include "General/LexicalRuleValidator.h"
#include "QueryUtil.h"
#include "QPS/QPSTypeDefs.h"
#include <unordered_map>
#include <algorithm>

/*
 * Validates a wildcard token,
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
  return s == "stmt" || s == "read" || s == "print" || s == "call" || s == "while" ||
      s == "if" || s == "assign" || s == "variable" || s == "constant" || s == "procedure";
}

/*
 * Validates if a string is a Relationship Reference.
 */
bool QueryUtil::IsRelationshipReference(const std::string& s) {
  return s == "Follows" || s == "Follows*" || s == "Parent" || s == "Parent*" || s == "Uses" || s == "Modifies";
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
* */
bool QueryUtil::IsPartialMatchExpressionSpecification(const std::string& s) {
  bool result = s[0] == '_' && s[s.length()-1] == '_';
  return result;
}

/*
* Checks if the expression is a variable synonym
*/
bool QueryUtil::IsVariableSynonym(Map &declaration, const std::string& expression) {
  std::string type = declaration[expression];
  bool result = type == "variable";
  return result;
}


/*
 * Get intersection between two vectors
 * TODO To complete this
 * Reference: https://stackoverflow.com/questions/19483663/vector-intersection-in-c
 */
SingleConstraintSet QueryUtil::GetIntersection(const SingleConstraintSet& set_1, const SingleConstraintSet& set_2) {
  SingleConstraintSet set;
  return set;
}

