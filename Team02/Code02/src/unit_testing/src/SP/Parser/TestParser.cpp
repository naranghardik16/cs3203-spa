#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"
#include "SP/Parser/PrintStatementParser.h"
#include "SP/Parser/ReadStatementParser.h"
#include "SP/Parser/CallStatementParser.h"

#include "catch.hpp"
#include <string>
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/PunctuationToken.h"

TEST_CASE("Check if IsProcedure works") {
  Parser::Line proc_line{make_shared<NameToken>("procedure"), make_shared<NameToken>("main"),
                         make_shared<PunctuationToken>("{", LEFT_BRACE)};
  Parser::Line stmt_line
      {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
       make_shared<NameToken>("y"), make_shared<PunctuationToken>(";", SEMICOLON)};
  REQUIRE(Parser::IsProcedure(proc_line) == true);
  REQUIRE(Parser::IsProcedure(stmt_line) == false);
}

TEST_CASE("Check if AssignStatementParser works") {
  Parser::Line stmt_line
      {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
       make_shared<NameToken>("y"), make_shared<PunctuationToken>(";", SEMICOLON)};
  Parser::TokenStream stmt_tokens{stmt_line};
  auto parser = make_shared<AssignStatementParser>();
  try {
    auto stmt = parser->ParseEntity(stmt_tokens);
  } catch (SpaException &e) {
    std::cout << e.what() << std::endl;
    REQUIRE(0);
  }
}

TEST_CASE("Check if Parser works with non control flow statements") {
  Parser::Line proc_line{make_shared<NameToken>("procedure"), make_shared<NameToken>("main"),
                         make_shared<PunctuationToken>("{", LEFT_BRACE)};
  Parser::Line stmt_line_var
      {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
       make_shared<NameToken>("y"), make_shared<PunctuationToken>(";", SEMICOLON)};
  Parser::Line stmt_line_const
      {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
       make_shared<IntegerToken>("10"), make_shared<PunctuationToken>(";", SEMICOLON)};
  Parser::Line stmt_line_read{make_shared<NameToken>("read"), make_shared<NameToken>("z"),
                              make_shared<PunctuationToken>(";", SEMICOLON)};
  Parser::Line stmt_line_print{make_shared<NameToken>("print"), make_shared<NameToken>("x"),
                               make_shared<PunctuationToken>(";", SEMICOLON)};
  Parser::Line end_line{make_shared<PunctuationToken>("}", RIGHT_BRACE)};
  Parser::TokenStream
      source
      {proc_line, stmt_line_var, stmt_line_const, stmt_line_read,
       stmt_line_print, end_line};
  auto parser = make_shared<Parser>();
  try {
    auto program = parser->ParseSource(source);

    SECTION(
        "Check if the AssignStatement has correct fields with Variable expression") {
      auto stmt_var = program->GetProcedureList()[0]->GetStatementList()[0];
      auto stmt_type = stmt_var->GetStatementType();
      auto assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_var);
      auto var = assign_stmt->GetVariable();
      auto expression = assign_stmt->GetExpression();
      REQUIRE(assign_stmt->GetStatementType() == "assign");
      REQUIRE(assign_stmt->GetStatementNumber() == 1);
      REQUIRE(var == Variable("x"));
      REQUIRE(*expression == Variable("y"));
    }

    SECTION(
        "Check if the AssignStatement has correct fields with Constant expression") {
      auto stmt_const = program->GetProcedureList()[0]->GetStatementList()[1];
      auto assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_const);
      auto expression = assign_stmt->GetExpression();
      REQUIRE(assign_stmt->GetStatementType() == "assign");
      REQUIRE(assign_stmt->GetStatementNumber() == 2);
      REQUIRE(*expression == Constant("10"));
    }

    SECTION("Check if the ReadStatement has correct fields") {
      auto stmt = program->GetProcedureList()[0]->GetStatementList()[2];
      auto read_stmt = dynamic_pointer_cast<ReadStatement>(stmt);
      auto var = read_stmt->GetVariable();
      REQUIRE(read_stmt->GetStatementType() == "read");
      REQUIRE(read_stmt->GetStatementNumber() == 3);
      REQUIRE(var == Variable("z"));
    }

    SECTION("Check if the PrintStatement has correct fields") {
      auto stmt = program->GetProcedureList()[0]->GetStatementList()[3];
      auto print_stmt = dynamic_pointer_cast<PrintStatement>(stmt);
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
      {{make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
        make_shared<NameToken>("y"), make_shared<PunctuationToken>(";", SEMICOLON)}};
  auto parser = make_shared<Parser>();
  try {
    auto program = parser->ParseSource(invalid_proc_tokens);
  } catch (SyntaxErrorException &e) {
    REQUIRE(e.what() == "A procedure Line should start with procedure");
  }
}

TEST_CASE("Check if CallStatementParser works") {
  SECTION("Check for valid call statement") {
    Parser::Line stmt_line
        {make_shared<NameToken>("call"), make_shared<NameToken>("Third"),
         make_shared<PunctuationToken>(";", SEMICOLON)};
    Parser::TokenStream stmt_tokens{stmt_line};
    auto parser = make_shared<CallStatementParser>();
    auto stmt = parser->ParseEntity(stmt_tokens);
    shared_ptr<CallStatement> call_stmt = dynamic_pointer_cast<CallStatement>(stmt);
    if (call_stmt->GetProcedureName() == "Third") {
      SUCCEED();
    } else {
      FAIL();
    }
  }

  SECTION("Check for invalid call statement - missing semicolon") {
    Parser::Line stmt_line
        {make_shared<NameToken>("call"), make_shared<NameToken>("Third")};
    Parser::TokenStream stmt_tokens{stmt_line};
    auto parser = make_shared<CallStatementParser>();
    REQUIRE_THROWS_AS(parser->ParseEntity(stmt_tokens), SyntaxErrorException);
  }

  SECTION("Check for invalid call statement - missing semicolon") {
    Parser::Line stmt_line
        {make_shared<NameToken>("call"), make_shared<NameToken>("Third")};
    Parser::TokenStream stmt_tokens{stmt_line};
    auto parser = make_shared<CallStatementParser>();
    REQUIRE_THROWS_AS(parser->ParseEntity(stmt_tokens), SyntaxErrorException);
  }

  SECTION("Check for invalid call statement - missing procedure name") {
    Parser::Line stmt_line
        {make_shared<NameToken>("call")};
    Parser::TokenStream stmt_tokens{stmt_line};
    auto parser = make_shared<CallStatementParser>();
    REQUIRE_THROWS_AS(parser->ParseEntity(stmt_tokens), SyntaxErrorException);
  }

  SECTION("Check for invalid call statement - invalid procedure name") {
    Parser::Line stmt_line
        {make_shared<NameToken>("call"), make_shared<IntegerToken>("123")};
    Parser::TokenStream stmt_tokens{stmt_line};
    auto parser = make_shared<CallStatementParser>();
    REQUIRE_THROWS_AS(parser->ParseEntity(stmt_tokens), SyntaxErrorException);
  }

  SECTION("Check for invalid call statement - more than 2 tokens") {
    Parser::Line stmt_line
        {make_shared<NameToken>("call"), make_shared<NameToken>("abc"),
         make_shared<NameToken>("efg")};
    Parser::TokenStream stmt_tokens{stmt_line};
    auto parser = make_shared<CallStatementParser>();
    REQUIRE_THROWS_AS(parser->ParseEntity(stmt_tokens), SyntaxErrorException);
  }
}
