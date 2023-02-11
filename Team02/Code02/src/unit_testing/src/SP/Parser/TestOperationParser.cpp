#include "catch.hpp"

#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"

#include <string>
#include "SP/NameToken.h"
#include "SP/IntegerToken.h"
#include "SP/PunctuationToken.h"
#include "SP/ArithmeticOperatorToken.h"

TEST_CASE("Check if ArithmeticOperationParser works") {
  SECTION("Check if arithmetic expression with only 2 operands and 1 (+ or -) operator (e.g., x + z) parses correctly") {
    Parser::Line expr_line{new IntegerToken("11"), new ArithmeticOperatorToken("+", PLUS), new NameToken("x")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> arguments;
    arguments.first = new Constant("11");
    arguments.second = new Variable("x");
    ArithmeticOperation *expected = new ArithmeticOperation("+", arguments);
    REQUIRE(actual->operator==(*expected));
  }
  SECTION("Check if arithmetic expression with only 2 operands and 1 (* or / or %) operator (e.g., x * z) parses correctly") {
    Parser::Line expr_line{new NameToken("x"), new ArithmeticOperatorToken("*", MULTIPLY), new NameToken("z")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> arguments;
    arguments.first = new Variable("x");
    arguments.second = new Variable("z");
    ArithmeticOperation *expected = new ArithmeticOperation("*", arguments);
    REQUIRE(actual->operator==(*expected));
  }
  SECTION("Check if arithmetic expression with only 3 operands and 2 (+ or -) operator (e.g., x + y + z) parses correctly") {
    Parser::Line expr_line{new NameToken("x"), new ArithmeticOperatorToken("+", PLUS), new NameToken("y"),
                           new ArithmeticOperatorToken("+", PLUS), new NameToken("z")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> left_subtree_args;
    left_subtree_args.first = new Variable("x");
    left_subtree_args.second = new Variable("y");
    ArithmeticOperation *left_subtree = new ArithmeticOperation("+", left_subtree_args);
    pair<Expression*, Expression*> root_args;
    root_args.first = left_subtree;
    root_args.second = new Variable("z");
    ArithmeticOperation *root = new ArithmeticOperation("+", root_args);
    REQUIRE(actual->operator==(*root));
  }
  SECTION("Check if arithmetic expression with only 3 operands with 1 (+ or -) first then 1 (* or / or %) operator (e.g., x + z * 5) parses correctly") {
    Parser::Line expr_line{new NameToken("x"), new ArithmeticOperatorToken("+", PLUS), new NameToken("z"),
                           new ArithmeticOperatorToken("*", MULTIPLY), new IntegerToken("5")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> right_subtree_args;
    right_subtree_args.first = new Variable("z");
    right_subtree_args.second = new Constant("5");
    ArithmeticOperation *right_subtree = new ArithmeticOperation("*", right_subtree_args);
    pair<Expression*, Expression*> root_args;
    root_args.first = new Variable("x");
    root_args.second = right_subtree;
    ArithmeticOperation *root = new ArithmeticOperation("+", root_args);
    REQUIRE(actual->operator==(*root));
  }
  SECTION("Check if arithmetic expression with only 3 operands with 2 (* or / or %) operator (e.g., x / y * z) parses correctly") {
    Parser::Line expr_line{new NameToken("x"), new ArithmeticOperatorToken("/", DIV), new NameToken("y"),
                           new ArithmeticOperatorToken("*", MULTIPLY), new NameToken("z")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> left_subtree_args;
    left_subtree_args.first = new Variable("x");
    left_subtree_args.second = new Variable("y");
    ArithmeticOperation *left_subtree = new ArithmeticOperation("/", left_subtree_args);
    pair<Expression*, Expression*> root_args;
    root_args.first = left_subtree;
    root_args.second = new Variable("z");
    ArithmeticOperation *root = new ArithmeticOperation("*", root_args);
    REQUIRE(actual->operator==(*root));
  }
  SECTION("Check if arithmetic expression with only 3 operands with 1 (* or / or %) first then 1 (+ or -) operator (e.g., z * 5 + x) parses correctly") {
    Parser::Line expr_line{new NameToken("z"), new ArithmeticOperatorToken("*", MULTIPLY), new IntegerToken("5"),
                           new ArithmeticOperatorToken("+", PLUS), new NameToken("x")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> left_subtree_args;
    left_subtree_args.first = new Variable("z");
    left_subtree_args.second = new Constant("5");
    ArithmeticOperation *left_subtree = new ArithmeticOperation("*", left_subtree_args);
    pair<Expression*, Expression*> root_args;
    root_args.first = left_subtree;
    root_args.second = new Variable("x");
    ArithmeticOperation *root = new ArithmeticOperation("+", root_args);
    REQUIRE(actual->operator==(*root));
  }
  SECTION("Check if arithmetic expression with only 3 operands where the 1st pair is enclosed by () and uses 1 (+ or -) followed by 1 (* or / or %) operator and 1 operand (e.g., (x + z) * 5) parses correctly") {
    Parser::Line expr_line{new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("x"), new ArithmeticOperatorToken("+", PLUS),
                           new NameToken("z"), new PunctuationToken(")", RIGHT_PARENTHESIS), new ArithmeticOperatorToken("*", MULTIPLY),
                           new IntegerToken("5")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> left_subtree_args;
    left_subtree_args.first = new Variable("x");
    left_subtree_args.second = new Variable("z");
    ArithmeticOperation *left_subtree = new ArithmeticOperation("+", left_subtree_args);
    pair<Expression*, Expression*> root_args;
    root_args.first = left_subtree;
    root_args.second = new Constant("5");
    ArithmeticOperation *root = new ArithmeticOperation("*", root_args);
    REQUIRE(actual->operator==(*root));
  }
  SECTION("Check if arithmetic expression with only > 3 operands using a mixture of operators (+-*/%) and 1 pair enclosed in () (e.g., z % ost + x * (y * z)) parses correctly") {
    Parser::Line expr_line{new NameToken("z"), new ArithmeticOperatorToken("%", MOD), new NameToken("ost"),
                           new ArithmeticOperatorToken("+", PLUS), new NameToken("x"), new ArithmeticOperatorToken("*", MULTIPLY),
                           new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("y"), new ArithmeticOperatorToken("*", MULTIPLY),
                           new NameToken("z"), new PunctuationToken(")", RIGHT_PARENTHESIS)};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> root_left_subtree_args;
    root_left_subtree_args.first = new Variable("z");
    root_left_subtree_args.second = new Variable("ost");
    ArithmeticOperation *root_left_subtree = new ArithmeticOperation("%", root_left_subtree_args);

    pair<Expression*, Expression*> root_right_right_subtree_args;
    root_right_right_subtree_args.first = new Variable("y");
    root_right_right_subtree_args.second = new Variable("z");
    ArithmeticOperation *root_right_right_subtree = new ArithmeticOperation("*", root_right_right_subtree_args);

    pair<Expression*, Expression*> root_right_subtree_args;
    root_right_subtree_args.first = new Variable("x");
    root_right_subtree_args.second = root_right_right_subtree;
    ArithmeticOperation *root_right_subtree = new ArithmeticOperation("*", root_right_subtree_args);

    pair<Expression*, Expression*> root_args;
    root_args.first = root_left_subtree;
    root_args.second = root_right_subtree;
    ArithmeticOperation *root = new ArithmeticOperation("+", root_args);
    REQUIRE(actual->operator==(*root));
  }
}

TEST_CASE("Check if ConditionalOperationParser & RelationalOperationParser works") {
  SECTION("Check if a single rel_expr (e.g. x == 1) parses correctly") {
    Parser::Line expr_line{new NameToken("x"), new RelationalOperatorToken("==", DOUBLE_EQUALS), new IntegerToken("1")};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "if");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> rel_args;
    rel_args.first = new Variable("x");
    rel_args.second = new Constant("1");
    RelationalOperation *rel = new RelationalOperation("==", rel_args);

    pair<Expression*, Expression*> cond_args;
    cond_args.first = rel;
    ConditionalOperation *expected = new ConditionalOperation("rel_expr", cond_args);
    REQUIRE(actual->operator==(*expected));
  }
  SECTION("Check if ! '(' cond_expr ')' (e.g. ! (x > y) ) parses correctly") {
    Parser::Line expr_line{new ConditionalOperatorToken("!", NOT), new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("x"),
                           new RelationalOperatorToken(">", GT), new NameToken("y"), new PunctuationToken(")", RIGHT_PARENTHESIS)};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "while");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> rel_args;
    rel_args.first = new Variable("x");
    rel_args.second = new Variable("y");
    RelationalOperation *rel = new RelationalOperation(">", rel_args);

    pair<Expression*, Expression*> inner_cond_args;
    inner_cond_args.first = rel;
    ConditionalOperation *inner_cond_expr = new ConditionalOperation("rel_expr", inner_cond_args);

    pair<Expression*, Expression*> root_cond_args;
    root_cond_args.first = inner_cond_expr;
    ConditionalOperation *root_cond_expr = new ConditionalOperation("!", root_cond_args);
    REQUIRE(actual->operator==(*root_cond_expr));
  }
  SECTION("Check if '(' cond_expr ')' '&&' or '||' '(' cond_expr ')' (e.g. (x < y) && (y >= 100) ) parses correctly") {
    Parser::Line expr_line{new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("x"), new RelationalOperatorToken("<", LT),
                           new NameToken("y"), new PunctuationToken(")", RIGHT_PARENTHESIS), new ConditionalOperatorToken("||", OR),
                           new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("y"), new RelationalOperatorToken(">=", GTE),
                           new IntegerToken("100"), new PunctuationToken(")", RIGHT_PARENTHESIS)};
    auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "if");
    auto actual = expr_parser->ParseEntity(expr_line);
    pair<Expression*, Expression*> lhs_rel_args;
    lhs_rel_args.first = new Variable("x");
    lhs_rel_args.second = new Variable("y");
    RelationalOperation *lhs_rel_expr = new RelationalOperation("<", lhs_rel_args);
    pair<Expression*, Expression*> lhs_cond_args;
    lhs_cond_args.first = lhs_rel_expr;
    ConditionalOperation *lhs_cond_expr = new ConditionalOperation("rel_expr", lhs_cond_args);


    pair<Expression*, Expression*> rhs_rel_args;
    rhs_rel_args.first = new Variable("y");
    rhs_rel_args.second = new Constant("100");
    RelationalOperation *rhs_rel_expr = new RelationalOperation(">=", rhs_rel_args);
    pair<Expression*, Expression*> rhs_cond_args;
    rhs_cond_args.first = rhs_rel_expr;
    ConditionalOperation *rhs_cond_expr = new ConditionalOperation("rel_expr", rhs_cond_args);

    pair<Expression*, Expression*> root_cond_args;
    root_cond_args.first = lhs_cond_expr;
    root_cond_args.second = rhs_cond_expr;
    ConditionalOperation *root_cond_expr = new ConditionalOperation("||", root_cond_args);
    REQUIRE(actual->operator==(*root_cond_expr));
  }
}