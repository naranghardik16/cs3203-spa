#include "SP/Parser/Parser.h"
#include "SP/Parser/WhileStatementParser.h"

#include "catch.hpp"
#include <string>
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/IntegerToken.h"
#include "SP/Tokenizer/PunctuationToken.h"

TEST_CASE("Check if StartOfWhileStatement is detected") {
  Parser::Line while_line_valid{
      make_shared<NameToken>("while"), make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"), make_shared<PunctuationToken>("<", LT),
      make_shared<IntegerToken>("5"), make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<PunctuationToken>("{", LEFT_BRACE)
  };

  Parser::Line while_line_no_brace{
      make_shared<NameToken>("while"), make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"), make_shared<PunctuationToken>("<", LT),
      make_shared<IntegerToken>("5"), make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
  };

  Parser::Line stmt_line
      {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
       make_shared<NameToken>("y"), make_shared<PunctuationToken>(";", SEMICOLON)};
  auto while_parser = make_shared<WhileStatementParser>();
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
      make_shared<PunctuationToken>("}", RIGHT_BRACE)
  };
  auto while_parser = make_shared<WhileStatementParser>();
  SECTION("Check if the token is correct for end of while statement") {
    REQUIRE(while_parser->IsEndOfWhileStatement(while_end_line) == true);
  }
}

TEST_CASE("Check if WhileStatementParser detects and parses statement list") {
  auto dummy_prog = make_shared<Program>();
  Parser::Line while_line_valid{
      make_shared<NameToken>("while"), make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"), make_shared<PunctuationToken>("<", LT),
      make_shared<IntegerToken>("5"), make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<PunctuationToken>("{", LEFT_BRACE)
  };
  Parser::Line while_line_1
      {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
       make_shared<NameToken>("y"), make_shared<PunctuationToken>(";", SEMICOLON)};
  Parser::Line while_line_2
      {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
       make_shared<NameToken>("z"), make_shared<PunctuationToken>(";", SEMICOLON)};
  Parser::Line while_end_line{
      make_shared<PunctuationToken>("}", RIGHT_BRACE)
  };

  Parser::TokenStream
      tokens{while_line_valid, while_line_1, while_line_2, while_end_line};
  auto while_parser = make_shared<WhileStatementParser>();
  shared_ptr<WhileStatement> while_stmt = dynamic_pointer_cast<WhileStatement>(while_parser->ParseEntity(tokens));
  REQUIRE(while_stmt->GetStatementNumber() == 1);
  auto condition = while_stmt->GetCondition();
  pair<shared_ptr<Expression>, shared_ptr<Expression>>
      rel_args{make_shared<Variable>("x"), make_shared<Constant>("5")};
  auto rel = make_shared<RelationalOperation>("<", rel_args);

  pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args{rel, nullptr};
  auto
      expected_condition_expr =
      make_shared<ConditionalOperation>("rel_expr", cond_args);
  REQUIRE(condition->operator==(*expected_condition_expr));
  auto stmt_list = while_stmt->GetLoopStatements();
  REQUIRE(stmt_list[0]->GetStatementNumber() == 2);
  auto assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_list[0]);
  REQUIRE(assign_stmt->GetVariable() == Variable("x"));
  assign_stmt = dynamic_pointer_cast<AssignStatement>(stmt_list[1]);
  REQUIRE(*(assign_stmt->GetExpression()) == Variable("z"));
}
