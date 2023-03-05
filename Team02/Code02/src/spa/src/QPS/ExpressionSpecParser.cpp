#include "ExpressionSpecParser.h"

std::string ExpressionSpecParser::ParseExpressionSpec(std::string expression_spec) {
  std::istringstream s1("number % 10 + 10 * 10 / 10 - 10;");
  std::shared_ptr<Tokenizer> tk = std::make_shared<Tokenizer>();

  if (expression_spec == "_") {
    return expression_spec;
  }

  std::string expr;

  bool is_partial_match = QueryUtil::IsPartialMatchExpressionSpecification(expression_spec);
  if (is_partial_match) {
    expr = string_util::Trim(expression_spec.substr(1, expression_spec.length() - 2));
  } else {
    throw SyntaxErrorException("Wrong usage of _ in expression specification " + expression_spec);
  }

  bool is_quoted = QueryUtil::IsQuoted(expr);

  if (is_quoted) {
      expr = string_util::Trim(expr.substr(1, expr.length()-2));
  } else {
    throw SyntaxErrorException("Wrong usage of quotation in expression specification " + expression_spec);
  }

  if ((!LexicalRuleValidator::IsInteger(expr)) &&
  (!LexicalRuleValidator::IsIdent(expr))) {

    throw SyntaxErrorException("Expression Specification does not adhere to the lexical rules of being a factor "
    + expression_spec);
  }

  return "_" + expr + "_"; //e.g. if _ "     y " _ --> return "_y_"
}