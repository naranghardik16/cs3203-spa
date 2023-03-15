#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"

#include "catch.hpp"
#include <string>
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/IntegerToken.h"

TEST_CASE("Check if IntegerToken is parsed as a Constant Expression") {
  Parser::Line expr_line{make_shared<IntegerToken>("11")};
  auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
  auto expr = expr_parser->ParseEntity(expr_line);
  REQUIRE(expr->GetExpressionType() == "constant");
}

TEST_CASE("Check if NameToken is parsed as a Variable Expression") {
  Parser::Line expr_line{make_shared<NameToken>("x")};
  auto expr_parser = ExpressionParserFactory::GetExpressionParser(expr_line, "assign");
  auto expr = expr_parser->ParseEntity(expr_line);
  REQUIRE(expr->GetExpressionType() == "variable");
}
