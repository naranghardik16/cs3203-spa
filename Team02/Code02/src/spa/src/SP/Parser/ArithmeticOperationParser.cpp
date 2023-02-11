#include "ArithmeticOperationParser.h"

/*
expr: expr '+' term | expr '-' term | term
 */
Expression *ArithmeticOperationParser::Parse() {
  Expression *root = Term();
  while (!IsEndOfLine() && root != nullptr && count(term_operators_.begin(), term_operators_.end(), GetCurrentTokenType())) {
    string prev_token_value = GetCurrentTokenValue();
    GetNext();
    Expression *right_node = Term();
    pair<Expression*, Expression*> arguments;
    arguments.first = root;
    arguments.second = right_node;
    root = new ArithmeticOperation(prev_token_value, arguments);
  }
  return root;
}

/*
term: term '*' factor | term '/' factor | term '%' factor | factor
 */
Expression *ArithmeticOperationParser::Term() {
  Expression *term = Factor();

  while (!IsEndOfLine() && term != nullptr && count(factor_operators_.begin(), factor_operators_.end(), GetCurrentTokenType())) {
    string prev_token_value = GetCurrentTokenValue();
    GetNext();
    Expression *right_node = Factor();
    pair<Expression*, Expression*> arguments;
    arguments.first = term;
    arguments.second = right_node;
    term = new ArithmeticOperation(prev_token_value, arguments);
  }
  return term;
}

/*
factor: var_name | const_value | '(' expr ')'
 */
Expression *ArithmeticOperationParser::Factor() {
  Expression *term = nullptr;

  if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
    GetNext();
    term = Parse();
    if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
      throw new SyntaxErrorException("Missing )");
    }
  } else if (GetCurrentTokenType() == INTEGER) {
    term = new Constant(GetCurrentTokenValue());
  } else if (GetCurrentTokenType() == NAME) {
    term = new Variable(GetCurrentTokenValue());
  }
  GetNext();
  return term;
}

