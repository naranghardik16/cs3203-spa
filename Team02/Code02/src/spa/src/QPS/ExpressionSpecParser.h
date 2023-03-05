#pragma once

#include <string>
#include <sstream>
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/Parser/ArithmeticOperationParser.h"
#include "QPS/Util/QueryUtil.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/LexicalRuleValidator.h"
#include "General/StringUtil.h"

/*!
 * ExpressionParser is used to parse expression specifications in Pattern clauses for PQL.
 * Make Use of SP tokenizer and parser.
 */
class ExpressionSpecParser {
 public:

  /*!
   * Parses and validates the expression specification
   * Formats the expression specification such that the factor easily obtained
   * @param expression_spec which is either a wildcard or a partial match with only a factor inside
   * @throws SyntaxErrorException if the expression specification flouts lexical rules
   */
  static std::shared_ptr<Expression> ParseExpressionSpec(const std::string& expression_spec);
};