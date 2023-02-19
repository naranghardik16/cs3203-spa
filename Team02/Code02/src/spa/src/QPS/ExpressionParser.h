#pragma once
#include <string>

/*!
 * ExpressionParser is used to parse expression specifications in Pattern clauses for PQL
 */
class ExpressionParser {
 public:

  /*!
   * Parses and validates the expression specification
   * Formats the expression specification such that the factor easily obtained
   * @param expression_spec which is either a wildcard or a partial match with only a factor inside
   * @throws SyntaxErrorException if the expression specification flouts lexical rules
   */
  static std::string ParseExpressionSpec(std::string expression_spec);
};