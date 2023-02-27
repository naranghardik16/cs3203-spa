#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "QPSTypeDefs.h"
#include <unordered_set>
#include <unordered_map>
#include "General/StatementTypeEnum.h"
#include "PKB/Types/PkbCommunicationTypes.h"
#include "General/StringUtil.h"

/*!
 * Abstracts out functions that are used in QPS when handling arguments in queries.
 */
class QueryUtil {

 public:

  /**
   * Validates if a given string is a wildcard
   * @param s is the input string
   * @return True if string is a wildcard, else false
   */
  static bool IsWildcard(const std::string& s);


  /**
   * Validates if a given string fulfills the lexical rules to be a synonym
   * @param s is the input string
   * @return True if string fulfills rules of a synonym, else false
   */
  static bool IsSynonym(const std::string& s);

  /**
   * Validates if a given string fulfills the lexical rules to be a statement reference
   * @param s is the input string
   * @return True if string fulfills rules of a statement reference, else false
   */
  static bool IsStmtRef(const std::string& s);

  /**
   * Validates if a given string fulfills the lexical rules to be a entity reference
   * @param s is the input string
   * @return True if string fulfills rules of a statement reference, else false
   */
  static bool IsEntRef(const std::string& s);

  /**
   * Validates if a string belongs to any design entity
   * @param s is the input string
   * @return True if string is a design entity, else false
   */
  static bool IsDesignEntity(const std::string& s);

  /**
   * Checks if a string is quoted as this means that the string is considered an IDENT type
   * @param s is the input string
   * @return True if string is in quotation marks, else false
   */
  static bool IsQuoted(const std::string& s);

  /**
   * Checks if a string is a relationship reference
   * @param s is the input string
   * @return True if string is a relationship reference, else false
   */
  static bool IsRelationshipReference(const std::string& s);

  /**
   * Checks if an expression specification requires a partial match
   * @param s is the input string
   * @return True if string is surrounded by '_', else false
   */
  static bool IsPartialMatchExpressionSpecification(const std::string& s);

  /**
   * Helper function to check if a expression has been declared as a specific design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @param type of design entity to validate with
   * @return true if the expression is a valid synonym of specified design entity type
   */
  static bool IsCorrectSynonymType(Map &declaration, const std::string& expression, const std::string type);

  /**
   * Validates if the expression has been declared as a variable design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid variable design entity, else false
   */
  static bool IsVariableSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as a constant design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression  to be validated
   * @return true if the expression is a valid constant design entity, else false
   */
  static bool IsConstantSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as an assign design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid assign design entity, else false
   */
  static bool IsAssignSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as an if design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid if design entity, else false
   */
  static bool IsIfSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as a statement design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid statement design entity, else false
   */
  static bool IsStatementSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as a while design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid while design entity, else false
   */
  static bool IsWhileSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as a print design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid print design entity, else false
   */
  static bool IsPrintSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as a read design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid read design entity, else false
   */
  static bool IsReadSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as a call design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid call design entity, else false
   */
  static bool IsCallSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as a procedure design entity
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid call design entity, else false
   */
  static bool IsProcedureSynonym(Map &declaration, const std::string& expression);

  /**
   * Validates if the expression has been declared as any design entity that represents statements
   * @param declaration which contains the synonyms as key and design entity as value
   * @param expression to be validated
   * @return true if the expression is a valid statement-based design entity, else false
   */
  static bool IsATypeOfStatementSynonym(Map &declaration, const std::string& expression);

  /**
   * Get the IDENT inside quotations.
   *
   * @param quoted_ident Quoted IDENT
   * @return The ident with quotations removed.
   */
  static std::string GetIdent(const std::string &quoted_ident);

  /**
   * Gets the statement type based on the design entity assigned to the synonym for accessing data in PKB
   * @param declaration which contains the synonyms as key and design entity as value
   * @param synonym to get statement type of
   * @return statement type of synonym
   */
  static StatementType GetStatementType(Map &declaration, const std::string &synonym);
  static bool IsAttrRef(const std::string &s);

  static std::vector<std::string> SplitAttrRef(const std::string &s);
};

