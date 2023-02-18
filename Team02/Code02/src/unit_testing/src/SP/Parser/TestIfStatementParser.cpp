#include "SP/Parser/Parser.h"
#include "SP/Parser/IfStatementParser.h"

#include "catch.hpp"
#include <string>
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/IntegerToken.h"
#include "SP/Tokenizer/PunctuationToken.h"

TEST_CASE("Check if StartOfIfStatement is detected") {
  Parser::Line if_line_valid
      {new NameToken("if"), new PunctuationToken("(", LEFT_PARENTHESIS),
       new NameToken("x"), new PunctuationToken("<", LT),
       new IntegerToken("5"), new PunctuationToken(")", RIGHT_PARENTHESIS),
       new NameToken("then"),
       new PunctuationToken("{", LEFT_BRACE)};
  Parser::Line if_line_no_then
      {new NameToken("if"), new PunctuationToken("(", LEFT_PARENTHESIS),
       new NameToken("x"), new PunctuationToken("<", LT),
       new IntegerToken("5"), new PunctuationToken(")", RIGHT_PARENTHESIS),
       new PunctuationToken("{", LEFT_BRACE)};
  Parser::Line stmt_line
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  auto if_parser = new IfStatementParser();
  SECTION("Check for validation of syntax of if statements") {
    REQUIRE_THROWS(if_parser->CheckStartOfIfStatement(if_line_no_then));
  }SECTION("Check for a valid if statement start") {
    REQUIRE_NOTHROW(if_parser->CheckStartOfIfStatement(if_line_valid));
  }SECTION("Check throws for assign statement") {
    REQUIRE_THROWS(if_parser->CheckStartOfIfStatement(stmt_line));
  }
}

TEST_CASE("Check if ExtractCondition works") {
  Parser::Line if_line_valid
      {new NameToken("if"), new PunctuationToken("(", LEFT_PARENTHESIS),
       new NameToken("x"), new PunctuationToken(">", LT),
       new IntegerToken("5"), new PunctuationToken(")", RIGHT_PARENTHESIS),
       new NameToken("then"),
       new PunctuationToken("{", LEFT_BRACE)};
  try {
    auto if_parser = new IfStatementParser();
    auto condition = if_parser->ExtractCondition(if_line_valid);
    pair<shared_ptr<Expression>, shared_ptr<Expression>>
        rel_args{new Variable("x"), new Constant("5")};
    auto rel = new RelationalOperation(">", rel_args);

    pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args{rel, nullptr};
    auto
        expected_condition_expr =
        make_shared<ConditionalOperation>("rel_expr", cond_args);
    REQUIRE(condition->operator==(*expected_condition_expr));
  } catch (std::exception &e) {
    cout << e.what() << endl;
  }
}

TEST_CASE("Check if EndOfThenStatements is detected") {
  Parser::Line end_of_then{
      new PunctuationToken("}", RIGHT_BRACE)
  };
  Parser::Line else_line_invalid{
      new NameToken("else"),
      new PunctuationToken("{", LEFT_BRACE)
  };
  auto *if_parser = new IfStatementParser();
  SECTION("Check for validation of syntax of end of then statements") {
    REQUIRE(if_parser->IsEndOfThenStatement(else_line_invalid) == false);
  }SECTION("Check if start of else statement is detected") {
    REQUIRE(if_parser->IsEndOfThenStatement(end_of_then) == true);
  }
}

TEST_CASE("Check if IfStatementParser detects then and else statements") {
  auto prog = new Program();
  Parser::Line if_line_valid
      {new NameToken("if"), new PunctuationToken("(", LEFT_PARENTHESIS),
       new NameToken("x"), new PunctuationToken("<", LT),
       new IntegerToken("5"), new PunctuationToken(")", RIGHT_PARENTHESIS),
       new NameToken("then"),
       new PunctuationToken("{", LEFT_BRACE)};
  Parser::Line then_stmt
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("y"), new PunctuationToken(";", SEMICOLON)};
  Parser::Line end_of_then{new PunctuationToken("}", RIGHT_BRACE)};
  Parser::Line else_line{
      new NameToken("else"),
      new PunctuationToken("{", LEFT_BRACE)
  };
  Parser::Line else_stmt
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL),
       new NameToken("z"), new PunctuationToken(";", SEMICOLON)};
  Parser::Line end_line{
      new PunctuationToken("}", RIGHT_BRACE)
  };

  try {
    Parser::TokenStream
        tokens
        {if_line_valid, then_stmt, end_of_then, else_line, else_stmt, end_line};
    auto if_parser = new IfStatementParser();
    shared_ptr<IfStatement> if_stmt = dynamic_pointer_cast<IfStatement>(if_parser->ParseEntity(tokens));
    REQUIRE(if_stmt->GetStatementNumber() == 1);
    auto condition = if_stmt->GetCondition();
    pair<shared_ptr<Expression>, shared_ptr<Expression>>
        rel_args{new Variable("x"), new Constant("5")};
    auto rel = make_shared<RelationalOperation>("<", rel_args);

    pair<shared_ptr<Expression>, shared_ptr<Expression>> cond_args{rel, nullptr};
    auto
        expected_condition_expr =
        make_shared<ConditionalOperation>("rel_expr", cond_args);
    REQUIRE(condition.operator==(*expected_condition_expr));
    auto then_stmts = if_stmt->GetThenStatements();
    REQUIRE(then_stmts[0]->GetStatementNumber() == 2);
    auto assign_stmt = dynamic_pointer_cast<AssignStatement>(then_stmts[0]);
    auto print_stmt_wrong = dynamic_pointer_cast<PrintStatement>(then_stmts[0]);
    REQUIRE(assign_stmt != nullptr);
    REQUIRE(print_stmt_wrong == nullptr);
    REQUIRE(assign_stmt->GetVariable() == Variable("x"));
    auto else_stmts = if_stmt->GetElseStatements();
    assign_stmt = dynamic_pointer_cast<AssignStatement>(else_stmts[0]);
    REQUIRE(assign_stmt != nullptr);
    REQUIRE(assign_stmt->GetStatementNumber() == 3);
    REQUIRE(*(assign_stmt->GetExpression()) == (Variable("z")));
    SUCCEED();
  } catch (SpaException &e) {
    cout << e.what() << endl;
    FAIL();
  }
}