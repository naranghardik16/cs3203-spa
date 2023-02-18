#include "SP/Parser/Parser.h"
#include "SP/Parser/WhileStatementParser.h"

#include "catch.hpp"
#include <string>
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/IntegerToken.h"
#include "SP/Tokenizer/PunctuationToken.h"

TEST_CASE("Check if StartOfWhileStatement is detected") {
  Parser::Line while_line_valid{
      new NameToken("while"), new PunctuationToken("(", LEFT_PARENTHESIS),
      new NameToken("x"), new PunctuationToken("<", LT),
      new IntegerToken("5"), new PunctuationToken(")", RIGHT_PARENTHESIS),
      new PunctuationToken("{", LEFT_BRACE)
  };

  Parser::Line while_line_no_brace{
      new NameToken("while"), new PunctuationToken("(", LEFT_PARENTHESIS),
      new NameToken("x"), new PunctuationToken("<", LT),
      new IntegerToken("5"), new PunctuationToken(")", RIGHT_PARENTHESIS),
  };

  Parser::Line stmt_line
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  auto *while_parser = new WhileStatementParser();
  SECTION("Check for validation of syntax of while statements") {
    REQUIRE_THROWS(while_parser->CheckStartOfLoopStatement(while_line_no_brace));
  }SECTION("Check for a valid while statement start") {
    REQUIRE_NOTHROW(while_parser->CheckStartOfLoopStatement(while_line_valid));
  } SECTION("Check throws for assign statement") {
    REQUIRE_THROWS(while_parser->CheckStartOfLoopStatement(stmt_line));
  }
}

TEST_CASE("Check if IsEndOFWhileStatement is detected") {
  Parser::Line while_end_line{
      new PunctuationToken("}", RIGHT_BRACE)
  };
  auto while_parser = new WhileStatementParser();
  SECTION("Check if the token is correct for end of while statement") {
    REQUIRE(while_parser->IsEndOfWhileStatement(while_end_line) == true);
  }
}

TEST_CASE("Check if WhileStatementParser detects and parses statement list") {
  auto dummy_prog = new Program();
  Parser::Line while_line_valid{
      new NameToken("while"), new PunctuationToken("(", LEFT_PARENTHESIS),
      new NameToken("x"), new PunctuationToken("<", LT),
      new IntegerToken("5"), new PunctuationToken(")", RIGHT_PARENTHESIS),
      new PunctuationToken("{", LEFT_BRACE)
  };
  Parser::Line while_line_1
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  Parser::Line while_line_2
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("z"), new PunctuationToken(";", SEMICOLON)};
  Parser::Line while_end_line{
      new PunctuationToken("}", RIGHT_BRACE)
  };

  Parser::TokenStream
      tokens{while_line_valid, while_line_1, while_line_2, while_end_line};
  auto while_parser = new WhileStatementParser();
  shared_ptr<WhileStatement> while_stmt = dynamic_pointer_cast<WhileStatement>(while_parser->ParseEntity(tokens));
  REQUIRE(while_stmt->GetStatementNumber() == 1);
  auto condition = while_stmt->GetCondition();
  pair<shared_ptr<Expression>, shared_ptr<Expression>>
      rel_args{new Variable("x"), new Constant("5")};
  auto rel = make_shared<RelationalOperation>("<", rel_args);

  pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args{rel, nullptr};
  auto
      expected_condition_expr =
      new ConditionalOperation("rel_expr", cond_args);
  REQUIRE(condition.operator==(*expected_condition_expr));
  auto stmt_list = while_stmt->GetLoopStatements();
  REQUIRE(stmt_list[0]->GetStatementNumber() == 2);
  auto assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_list[0]);
  REQUIRE(assign_stmt->GetVariable() == Variable("x"));
  assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_list[1]);
  REQUIRE(*(assign_stmt->GetExpression()) == Variable("z"));
}