#include "ExpressionSpecParser.h"

std::shared_ptr<Expression> ExpressionSpecParser::ParseExpressionSpec(const std::string& expression_spec) {
  if (QueryUtil::IsWildcard(expression_spec)) {
    return nullptr;
  }

  std::string expr = expression_spec;
  if (QueryUtil::IsPartialMatchExpressionSpecification(expr)) {
    expr = string_util::Trim(expr.substr(1, expr.length() - 2));
  }
  if (!QueryUtil::IsQuoted(expr)) {
    throw SyntaxErrorException();
  }

  expr = string_util::Trim(expr.substr(1, expr.length()-2));
  if (expr.empty()) {
    throw SyntaxErrorException();
  }
  std::istringstream str(expr + pql_constants::kSemicolon);
  std::shared_ptr<Tokenizer> tk = std::make_shared<Tokenizer>();
  std::shared_ptr<Parser::TokenStream> tokens = tk->Tokenize(str);
  std::shared_ptr<ArithmeticOperationParser> parser = std::make_shared<ArithmeticOperationParser>();

  if (tokens->size() != 1) {
    throw SyntaxErrorException();
  }
  vector<shared_ptr<Token>> expression_tokens{tokens->front().begin(), tokens->front().end() - 1};
  if (expression_tokens.size() == 1 && expression_tokens[0]->GetType() == LEFT_PARENTHESIS) {
    throw SyntaxErrorException();
  }
  std::shared_ptr<Expression> expression = parser->ParseEntity(expression_tokens);
  if (!expression) {
    throw SyntaxErrorException();
  }
  return expression;
}
