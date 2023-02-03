#pragma once
#include "ExpressionParser.h"
#include "QPS/Util/QueryUtil.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/LexicalRuleValidator.h"

std::string ExpressionParser::ParseExpressionSpec(std::string expression_spec) {
  //TODO: milestone 1  - only handle partial matching or wildcard and only handle constant matching and variable matching
  if (expression_spec == "_") {
    return expression_spec;
  }

  std::string expr;
  if (QueryUtil::IsPartialMatchExpressionSpecification(expression_spec)) {
    expr = expression_spec.substr(1, expression_spec.length() - 2);

  } else {
    throw SyntaxErrorException("Wrong usage of _ in expression specification");
  }

  if (QueryUtil::IsQuoted(expr)) {
      expr = expr.substr(1, expr.length()-2);

  } else {
    throw SyntaxErrorException("Wrong usage of quotation in expression specification");
  }

  if ((!LexicalRuleValidator::IsInteger(expr)) && (!LexicalRuleValidator::IsIdent(expr))) {
    throw SyntaxErrorException("Expression Specification does not adhere to the lexical rules of being a factor");
  }

  return expression_spec;

}