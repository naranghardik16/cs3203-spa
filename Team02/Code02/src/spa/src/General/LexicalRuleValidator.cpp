#include "General/LexicalRuleValidator.h"
#include <iostream>
#include <utility>

/*
 * Checks if the character is a valid letter based on PQL rules.
 */
bool LexicalRuleValidator::IsLetter(char c) {
    return isalpha(c);
}

/*
 * Check if the character is a valid digit based on PQL rules (0-9).
 */
bool LexicalRuleValidator::IsDigit(char c) {
    return isdigit(c);
}

/*
 * Checks if the character is a valid non-zero digit based on PQL rules (1-9).
 */
bool LexicalRuleValidator::IsNzDigit(char c) {
  return ((c >= '1') && (c <= '9'));
}

/*
 * Checks if a string starts with a letter and then has optional letters or numbers after first character.
 * This is the PQL rule for IDENT and NAME.
 */
bool LexicalRuleValidator::IsStartWithLetterThenMadeOfOptionalLetterOrNumbers(std::string s) {
  bool is_start_with_letter = IsLetter(s[0]);
  if (!is_start_with_letter) {
    return false;
  }

  for (char c : s) {
    if (!IsLetter(c) && !IsDigit(c)) {
      return false;
    }
  }

  return true;
}

/*
 * Validates IDENT lexical token for PQL.
 */
bool LexicalRuleValidator::IsIdent(std::string s) {
  return IsStartWithLetterThenMadeOfOptionalLetterOrNumbers(std::move(s));
}

/*
 * Validates a NAME lexical token in PQL.
 */
bool LexicalRuleValidator::IsName(std::string s) {
  return IsStartWithLetterThenMadeOfOptionalLetterOrNumbers(std::move(s));
}

/*
 * Validates an Integer lexical token in PQL.
 */
bool LexicalRuleValidator::IsInteger(std::string s) {
  if (s == "0") {
    return true;
  }

  bool is_first_character_nz_digit = IsNzDigit(s[0]);
  if (!is_first_character_nz_digit) {
    return false;
  }

  for (char c : s) {
    if (!IsDigit(c)) {
      return false;
    }
  }

  return true;
}

/*
 * Validates a SYNONYM lexical token in PQL.
 */
bool LexicalRuleValidator::IsSynonym(std::string s) {
  return IsIdent(std::move(s));
}

/*
 * Validates a Underscore token.
 */
bool LexicalRuleValidator::IsUnderscore(std::string s) {
  return s == "_";
}

/*
 * Validates a Statement Reference in PQL.
 */
bool LexicalRuleValidator::IsStmtRef(const std::string& s) {
  return (IsUnderscore(s) || IsSynonym(s) || IsInteger(s));
}

/*
 * Validates an Entity Reference in PQL.
 */
bool LexicalRuleValidator::IsEntRef(std::string s) {
  bool is_ident_in_quotation = (s[0] == '"' && IsIdent(s.substr(1, s.length() - 2)) && s[s.length()-1] == '"');
  return (IsUnderscore(s) || IsSynonym(s) || is_ident_in_quotation);
}

/*
 * Validates if a string is a Design Entity in PQL.
 */
bool LexicalRuleValidator::IsDesignEntity(const std::string& s) {
  return s == "stmt" || s == "read" || s == "print" || s == "call" || s == "while" ||
      s == "if" || s == "assign" || s == "variable" || s == "constant" || s == "procedure";
}

/*
 * Validates if a string is a Relationship Reference.
 */
bool LexicalRuleValidator::IsRelationshipReference(const std::string& s) {
  return s == "Follows" || s == "Follows*" || s == "Parent" || s == "Parent*" || s == "Uses" || s == "Modifies";
}