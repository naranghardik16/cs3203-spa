#include "catch.hpp"

#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"

#include <string>
#include "SP/NameToken.h"
#include "SP/IntegerToken.h"
#include "SP/PunctuationToken.h"
#include "SP/ArithmeticOperatorToken.h"

TEST_CASE("Check if ArithmeticOperationParser works") {
  SECTION("Check if arithmetic expression with only 2 operands and + or - operator (e.g., x + z) parses correctly") {
    Parser::Line expr_line{new IntegerToken("11"), new ArithmeticOperatorToken("+", PLUS), new NameToken("x")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line);
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> arguments;
    arguments.first = new Constant("11");
    arguments.second = new Variable("x");
    ArithmeticOperation *expected = new ArithmeticOperation("+", arguments);
    REQUIRE(actual->operator==(*expected));
  }
  SECTION("Check if arithmetic expression with only 2 operands and * or / operator (e.g., x * z) parses correctly") {
    Parser::Line expr_line{new NameToken("x"), new ArithmeticOperatorToken("*", PLUS), new NameToken("z")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line);
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> arguments;
    arguments.first = new Variable("x");
    arguments.second = new Variable("z");
    ArithmeticOperation *expected = new ArithmeticOperation("*", arguments);
    REQUIRE(actual->operator==(*expected));
  }
  SECTION("Check if arithmetic expression with only 3 operands and 2 + or - operator (e.g., x + y + z) parses correctly") {
    Parser::Line expr_line{new NameToken("x"), new ArithmeticOperatorToken("+", PLUS), new NameToken("y"),
                           new ArithmeticOperatorToken("+", PLUS), new NameToken("z")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line);
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> left_subtree_args;
    left_subtree_args.first = new Variable("x");
    left_subtree_args.second = new Variable("y");
    ArithmeticOperation *left_subtree = new ArithmeticOperation("+", left_subtree_args);
    pair<Expression*, Expression*> root_args;
    left_subtree_args.first = left_subtree;
    left_subtree_args.second = new Variable("z");
    ArithmeticOperation *root = new ArithmeticOperation("+", left_subtree_args);
    REQUIRE(actual->operator==(*root));
  }
  // TODO: Add more tests
}