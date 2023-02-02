#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"

#include "catch.hpp"
#include <string>
#include "SP/NameToken.h"
#include "SP/PunctuationToken.h"

TEST_CASE("Check if IsProcedure works") {
  Parser::Line proc_line{new NameToken("procedure"), new NameToken("main"),
                         new PunctuationToken("{", LEFT_PARENTHESIS)};
  Parser::Line stmt_line
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  REQUIRE(Parser::IsProcedure(proc_line) == true);
  REQUIRE(Parser::IsProcedure(stmt_line) == false);
}

TEST_CASE("Check if AssignStatementParser works") {
  Parser::Line stmt_line
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  Parser::TokenStream stmt_tokens{stmt_line};
  auto parser = new AssignStatementParser();
  try {
    auto stmt = parser->ParseEntity(stmt_tokens);
  } catch (SpaException &e) {
    std::cout << e.what() << std::endl;
    REQUIRE(0);
  }
}

TEST_CASE("Check if Parser works with only assign statement") {
  Parser::Line proc_line{new NameToken("procedure"), new NameToken("main"),
                         new PunctuationToken("{", LEFT_PARENTHESIS)};
  Parser::Line stmt_line
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  Parser::Line end_line{new PunctuationToken("}", RIGHT_PARENTHESIS)};
  Parser::TokenStream source{proc_line, stmt_line, end_line};
  auto parser = new Parser();
  try {
    auto program = parser->ParseSource(source);
    auto stmt = program.GetProcedureList()[0]->GetStatementList()[0];
    auto stmt_type = stmt->GetStatementType();
    auto assign_stmt = dynamic_cast<AssignStatement *>(stmt);
    auto var = assign_stmt->GetVariable();
    auto expression = assign_stmt->GetExpression();
    REQUIRE(var == Variable("x"));
    REQUIRE(expression == Expression("y", "variable"));
  } catch (SpaException &e) {
    cout << e.what() << endl;
    REQUIRE(0);
  }
}

TEST_CASE(
    "Check if Parser throws Syntax Error for not starting with a procedure") {
  Parser::TokenStream invalid_proc_tokens
      {{new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
        new NameToken("y"), new PunctuationToken(";", SEMICOLON)}};
  auto parser = new Parser();
  try {
    auto program = parser->ParseSource(invalid_proc_tokens);
  } catch (SyntaxErrorException &e) {
    std::cout << e.what() << std::endl;
    REQUIRE(1);
  }

}