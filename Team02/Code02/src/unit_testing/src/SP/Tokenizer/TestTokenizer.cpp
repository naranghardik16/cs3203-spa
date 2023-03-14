#include "catch.hpp"

#include <string>
// must include <sstream> to use iss for istringstream
#include <sstream>
#include "./SP/Parser/Parser.h"
#include "SP/Tokenizer/Tokenizer.h"


bool CheckTokenStreamEquality(Parser::TokenStream ts1, Parser::TokenStream ts2) {
  if (ts1.size() != ts2.size()) {
    return false;
  }
  for (int i = 0; i < ts1.size(); i++) {
    if (ts1[i].size() != ts2[i].size()) {
      return false;
    }

    for (int j = 0; j < ts1[i].size(); j++) {
      if (!ts1[i][j]->Equals(ts2[i][j])) {
        return false;
      }
    }
  }

  return true;
}

TEST_CASE("Check if SP Tokenizer::Tokenize works as expected") {
  shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();

  SECTION("Test if it valid tokens (e.g. abc123 for name token) are tokenized as expected") {
    string input = "abc123 = 1;\n"
                   "ABC123 = 2;\n"
                   "a1b2 = 3;\n"
                   "if (i == 0) then {";
    std::istringstream is;
    is.str(input);

    shared_ptr<Parser::TokenStream> actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {make_shared<NameToken>("abc123"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
         make_shared<IntegerToken>("1"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("ABC123"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
         make_shared<IntegerToken>("2"), make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("a1b2"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
         make_shared<IntegerToken>("3"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("if"), make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
         make_shared<NameToken>("i"),
         make_shared<RelationalOperatorToken>("==", DOUBLE_EQUALS), make_shared<IntegerToken>("0"),
         make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS), make_shared<NameToken>("then"),
         make_shared<PunctuationToken>("{", LEFT_BRACE)}
    };
    REQUIRE(CheckTokenStreamEquality(*actual, expected));
  }

  SECTION("Test if it works for variation of spacing between tokens -- 1") {
    string input = "while (i>0&&i<=10) {";
    std::istringstream is;
    is.str(input);

    shared_ptr<Parser::TokenStream> actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {make_shared<NameToken>("while"), make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
         make_shared<NameToken>("i"),
         make_shared<RelationalOperatorToken>(">", GT), make_shared<IntegerToken>("0"),
         make_shared<ConditionalOperatorToken>("&&", AND),
         make_shared<NameToken>("i"), make_shared<RelationalOperatorToken>("<=", LTE), make_shared<IntegerToken>("10"),
         make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS), make_shared<PunctuationToken>("{", LEFT_BRACE)}
    };
    REQUIRE(CheckTokenStreamEquality(*actual, expected));
  }

  SECTION("Test if it works for variation of spacing between tokens -- 2") {
    string input = "  read print;"
                   "  then  "
                   "  = "
                   "  read  "
                   "  ; "
                   "  else  "
                   "  = "
                   "  print "
                   "  ; ";
    std::istringstream is;
    is.str(input);

    shared_ptr<Parser::TokenStream> actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {make_shared<NameToken>("read"), make_shared<NameToken>("print"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("then"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
         make_shared<NameToken>("read"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("else"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
         make_shared<NameToken>("print"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
    };
    REQUIRE(CheckTokenStreamEquality(*actual, expected));
  }

  SECTION("Test if it works for input with normal syntax + multiple spacing") {
    string input = "while (i > 0 && i <= 10) {\n"
                   "  x = x + z * 5 / 2;\n"
                   "  z = (10 - x) % 2;\n"
                   "}";
    std::istringstream is;
    is.str(input);

    shared_ptr<Parser::TokenStream> actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {make_shared<NameToken>("while"), make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
         make_shared<NameToken>("i"),
         make_shared<RelationalOperatorToken>(">", GT), make_shared<IntegerToken>("0"),
         make_shared<ConditionalOperatorToken>("&&", AND),
         make_shared<NameToken>("i"), make_shared<RelationalOperatorToken>("<=", LTE), make_shared<IntegerToken>("10"),
         make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS), make_shared<PunctuationToken>("{", LEFT_BRACE)},
        {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL), make_shared<NameToken>("x"),
         make_shared<ArithmeticOperatorToken>("+", PLUS), make_shared<NameToken>("z"),
         make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
         make_shared<IntegerToken>("5"), make_shared<ArithmeticOperatorToken>("/", DIV), make_shared<IntegerToken>("2"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("z"), make_shared<PunctuationToken>("=", SINGLE_EQUAL),
         make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
         make_shared<IntegerToken>("10"), make_shared<ArithmeticOperatorToken>("-", MINUS), make_shared<NameToken>("x"),
         make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS), make_shared<ArithmeticOperatorToken>("%", MOD),
         make_shared<IntegerToken>("2"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<PunctuationToken>("}", RIGHT_BRACE)}
    };
    REQUIRE(CheckTokenStreamEquality(*actual, expected));
  }

  SECTION("Test if it works for identifying lines based on END_OF_LINES punctuations") {
    string input = "if (i == 0) { x = 1; y = 3; z = 5; }";
    std::istringstream is;
    is.str(input);

    shared_ptr<Parser::TokenStream> actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {make_shared<NameToken>("if"), make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
         make_shared<NameToken>("i"),
         make_shared<RelationalOperatorToken>("==", DOUBLE_EQUALS), make_shared<IntegerToken>("0"),
         make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
         make_shared<PunctuationToken>("{", LEFT_BRACE)},
        {make_shared<NameToken>("x"), make_shared<PunctuationToken>("=", SINGLE_EQUAL), make_shared<IntegerToken>("1"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("y"), make_shared<PunctuationToken>("=", SINGLE_EQUAL), make_shared<IntegerToken>("3"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<NameToken>("z"), make_shared<PunctuationToken>("=", SINGLE_EQUAL), make_shared<IntegerToken>("5"),
         make_shared<PunctuationToken>(";", SEMICOLON)},
        {make_shared<PunctuationToken>("}", RIGHT_BRACE)}
    };
    REQUIRE(CheckTokenStreamEquality(*actual, expected));
  }

  SECTION("Test if it throws SyntaxError for invalid syntax input") {
    SECTION("Test invalid name token") {
      string input = "1abc = 3;";
      std::istringstream is;
      is.str(input);
      REQUIRE_THROWS_AS(tokenizer->Tokenize(is), SyntaxErrorException);
    }

    SECTION("Test invalid integer token") {
      string input = "x = 003;";
      std::istringstream is;
      is.str(input);
      REQUIRE_THROWS_AS(tokenizer->Tokenize(is), SyntaxErrorException);
    }

    SECTION("Test invalid token") {
      string input = "x _= 3;";
      std::istringstream is;
      is.str(input);
      REQUIRE_THROWS_AS(tokenizer->Tokenize(is), SyntaxErrorException);
    }
  }
}
