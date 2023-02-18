#include "ArithmeticOperationParser.h"

/*
expr: expr '+' term | expr '-' term | term
 */
shared_ptr<Expression> ArithmeticOperationParser::Parse() {
  shared_ptr<Expression> root = Term();
  while (!IsEndOfLine() && root != nullptr && count(term_operators_.begin(), term_operators_.end(), GetCurrentTokenType())) {
    string prev_token_value = GetCurrentTokenValue();
    GetNext();
    shared_ptr<Expression> right_node = Term();
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
    arguments.first = root;
    arguments.second = right_node;
    root = make_shared<ArithmeticOperation>(prev_token_value, arguments);
  }
  return root;
}

/*
term: term '*' factor | term '/' factor | term '%' factor | factor
 */
shared_ptr<Expression> ArithmeticOperationParser::Term() {
  shared_ptr<Expression> term = Factor();

  while (!IsEndOfLine() && term != nullptr && count(factor_operators_.begin(), factor_operators_.end(), GetCurrentTokenType())) {
    string prev_token_value = GetCurrentTokenValue();
    GetNext();
    shared_ptr<Expression> right_node = Factor();
    pair<shared_ptr<Expression>, shared_ptr<Expression>> arguments;
    arguments.first = term;
    arguments.second = right_node;
    term = make_shared<ArithmeticOperation>(prev_token_value, arguments);
  }
  return term;
}

/*
factor: var_name | const_value | '(' expr ')'
 */
shared_ptr<Expression> ArithmeticOperationParser::Factor() {
  shared_ptr<Expression> term = nullptr;

  if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
    GetNext();
    term = Parse();
    if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
      throw SyntaxErrorException("Missing )");
    }
  } else if (GetCurrentTokenType() == INTEGER) {
    term = make_shared<Constant>(GetCurrentTokenValue());
  } else if (GetCurrentTokenType() == NAME) {
    term = make_shared<Variable>(GetCurrentTokenValue());
  }
  GetNext();
  return term;
}