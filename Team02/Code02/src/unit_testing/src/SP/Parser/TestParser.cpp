#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"
#include "SP/Parser/PrintStatementParser.h"
#include "SP/Parser/ReadStatementParser.h"

#include "catch.hpp"
#include <string>
#include "SP/NameToken.h"
#include "SP/PunctuationToken.h"

TEST_CASE("Check if IsProcedure works") {
  Parser::Line proc_line{new NameToken("procedure"), new NameToken("main"),
                         new PunctuationToken("{", LEFT_BRACE)};
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

TEST_CASE("Check if Parser works with non control flow statements") {
  Parser::Line proc_line{new NameToken("procedure"), new NameToken("main"),
                         new PunctuationToken("{", LEFT_BRACE)};
  Parser::Line stmt_line_var
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  Parser::Line stmt_line_const
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new IntegerToken("10"), new PunctuationToken(";", SEMICOLON)};
  Parser::Line stmt_line_read{new NameToken("read"), new NameToken("z"),
                              new PunctuationToken(";", SEMICOLON)};
  Parser::Line stmt_line_print{new NameToken("print"), new NameToken("x"),
                               new PunctuationToken(";", SEMICOLON)};
  Parser::Line end_line{new PunctuationToken("}", RIGHT_BRACE)};
  Parser::TokenStream
      source
      {proc_line, stmt_line_var, stmt_line_const, stmt_line_read,
       stmt_line_print, end_line};
  auto parser = new Parser();
  try {
    auto program = parser->ParseSource(source);

    SECTION(
        "Check if the AssignStatement has correct fields with Variable expression") {
      auto stmt_var = program.GetProcedureList()[0]->GetStatementList()[0];
      auto stmt_type = stmt_var->GetStatementType();
      auto assign_stmt = dynamic_cast<AssignStatement *>(stmt_var);
      auto var = assign_stmt->GetVariable();
      auto expression = assign_stmt->GetExpression();
      REQUIRE(assign_stmt->GetStatementType() == "assign");
      REQUIRE(assign_stmt->GetStatementNumber() == 1);
      REQUIRE(var == Variable("x"));
      REQUIRE(*expression == Variable("y"));
    }

    SECTION(
        "Check if the AssignStatement has correct fields with Constant expression") {
      auto stmt_const = program.GetProcedureList()[0]->GetStatementList()[1];
      auto assign_stmt = dynamic_cast<AssignStatement *>(stmt_const);
      auto expression = assign_stmt->GetExpression();
      REQUIRE(assign_stmt->GetStatementType() == "assign");
      REQUIRE(assign_stmt->GetStatementNumber() == 2);
      REQUIRE(*expression == Constant("10"));
    }

    SECTION("Check if the ReadStatement has correct fields") {
      auto stmt = program.GetProcedureList()[0]->GetStatementList()[2];
      auto read_stmt = dynamic_cast<ReadStatement *>(stmt);
      auto var = read_stmt->GetVariable();
      REQUIRE(read_stmt->GetStatementType() == "read");
      REQUIRE(read_stmt->GetStatementNumber() == 3);
      REQUIRE(var == Variable("z"));
    }

    SECTION("Check if the PrintStatement has correct fields") {
      auto stmt = program.GetProcedureList()[0]->GetStatementList()[3];
      auto print_stmt = dynamic_cast<PrintStatement *>(stmt);
      auto var = print_stmt->GetVariable();
      REQUIRE(print_stmt->GetStatementType() == "print");
      REQUIRE(print_stmt->GetStatementNumber() == 4);
      REQUIRE(var == Variable("x"));
    }
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
    REQUIRE(e.what() == "A procedure Line should start with procedure");
  }

}