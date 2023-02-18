#include "catch.hpp"

#include <string>
// must include <sstream> to use iss for istringstream
#include <sstream>
#include "./SP/Parser/Parser.h"
#include "SP/Tokenizer/Tokenizer.h"

using namespace std;

bool CheckTokenStreamEquality(Parser::TokenStream ts1, Parser::TokenStream ts2) {
  if (ts1.size() != ts2.size()) {
    return false;
  }
  for (int i = 0; i < ts1.size(); i++) {
    if (ts1[i].size() != ts2[i].size()) {
      return false;
    }

    for (int j = 0; j < ts1[i].size(); j++) {
      if (!ts1[i][j]->Equals(*ts2[i][j])) {
        return false;
      }
    }
  }

  return true;
}

TEST_CASE("Check if SP Tokenizer::Tokenize works as expected") {
  Tokenizer* tokenizer = new Tokenizer();

  SECTION("Test if it valid tokens (e.g. abc123 for name token) are tokenized as expected") {
    string input = "abc123 = 1;\n"
                   "ABC123 = 2;\n"
                   "a1b2 = 3;\n"
                   "if (i == 0) then {";
    std::istringstream is;
    is.str(input);

    Parser::TokenStream *actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {new NameToken("abc123"), new PunctuationToken("=", SINGLE_EQUAL),  new IntegerToken("1"),
         new PunctuationToken(";", SEMICOLON)},
        {new NameToken("ABC123"), new PunctuationToken("=", SINGLE_EQUAL),
         new IntegerToken("2"), new PunctuationToken(";", SEMICOLON)},
        {new NameToken("a1b2"), new PunctuationToken("=", SINGLE_EQUAL), new IntegerToken("3"),
         new PunctuationToken(";", SEMICOLON)},
        {new NameToken("if"), new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("i"),
         new RelationalOperatorToken("==", DOUBLE_EQUALS), new IntegerToken("0"),
         new PunctuationToken(")", RIGHT_PARENTHESIS), new NameToken("then"), new PunctuationToken("{", LEFT_BRACE)}
    };
    REQUIRE(CheckTokenStreamEquality(*actual, expected));
  }

  SECTION("Test if it works for variation of spacing between tokens") {
    string input = "while (i>0&&i<=10) {";
    std::istringstream is;
    is.str(input);

    Parser::TokenStream *actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {new NameToken("while"), new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("i"),
         new RelationalOperatorToken(">", GT), new IntegerToken("0"), new ConditionalOperatorToken("&&", AND),
         new NameToken("i"), new RelationalOperatorToken("<=", LTE), new IntegerToken("10"),
         new PunctuationToken(")", RIGHT_PARENTHESIS), new PunctuationToken("{", LEFT_BRACE)}
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

    Parser::TokenStream *actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {new NameToken("while"), new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("i"),
         new RelationalOperatorToken(">", GT), new IntegerToken("0"), new ConditionalOperatorToken("&&", AND),
         new NameToken("i"), new RelationalOperatorToken("<=", LTE), new IntegerToken("10"),
         new PunctuationToken(")", RIGHT_PARENTHESIS), new PunctuationToken("{", LEFT_BRACE)},
        {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL), new NameToken("x"),
         new ArithmeticOperatorToken("+", PLUS), new NameToken("z"), new ArithmeticOperatorToken("*", MULTIPLY),
         new IntegerToken("5"), new ArithmeticOperatorToken("/", DIV), new IntegerToken("2"),
         new PunctuationToken(";", SEMICOLON)},
        {new NameToken("z"), new PunctuationToken("=", SINGLE_EQUAL), new PunctuationToken("(", LEFT_PARENTHESIS),
         new IntegerToken("10"), new ArithmeticOperatorToken("-", MINUS), new NameToken("x"),
         new PunctuationToken(")", RIGHT_PARENTHESIS), new ArithmeticOperatorToken("%", MOD), new IntegerToken("2"),
         new PunctuationToken(";", SEMICOLON)},
        {new PunctuationToken("}", RIGHT_BRACE)}
    };
    REQUIRE(CheckTokenStreamEquality(*actual, expected));
  }

  SECTION("Test if it works for identifying lines based on END_OF_LINES punctuations") {
    string input = "if (i == 0) { x = 1; y = 3; z = 5; }";
    std::istringstream is;
    is.str(input);

    Parser::TokenStream *actual = tokenizer->Tokenize(is);
    Parser::TokenStream expected = {
        {new NameToken("if"), new PunctuationToken("(", LEFT_PARENTHESIS), new NameToken("i"),
         new RelationalOperatorToken("==", DOUBLE_EQUALS), new IntegerToken("0"), new PunctuationToken(")", RIGHT_PARENTHESIS),
         new PunctuationToken("{", LEFT_BRACE)},
        {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL), new IntegerToken("1"),
         new PunctuationToken(";", SEMICOLON)},
        {new NameToken("y"), new PunctuationToken("=", SINGLE_EQUAL), new IntegerToken("3"),
         new PunctuationToken(";", SEMICOLON)},
        {new NameToken("z"), new PunctuationToken("=", SINGLE_EQUAL), new IntegerToken("5"),
        new PunctuationToken(";", SEMICOLON)},
        {new PunctuationToken("}", RIGHT_BRACE)}
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


