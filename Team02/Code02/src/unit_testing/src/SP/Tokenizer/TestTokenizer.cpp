#pragma once
#include "./SP/Parser/Parser.h"
#include "./SP/Tokenizer.h"

#include "catch.hpp"
#include <string>
// must include <sstream> to use iss for istringstream
#include <sstream>

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
  string input = "while (i > 0 && i <= 10) {\n"
                 "  x = x + z * 5 / 2;\n"
                 "  z = (10 - x) % 2;\n"
                 "}";

  std::istringstream is;
  is.str(input);
  Tokenizer* tokenizer = new Tokenizer();
  Parser::TokenStream *actual = tokenizer->Tokenize(is);
  Parser::TokenStream expected = {
      {new NameToken("while"), new PunctuationToken("(", LEFT_BRACE), new NameToken("i"),
       new RelationalOperatorToken(">", GT), new IntegerToken("0"), new ConditionalOperatorToken("&&", AND),
       new NameToken("i"), new RelationalOperatorToken("<=", LTE), new IntegerToken("10"),
       new PunctuationToken(")", RIGHT_BRACE), new PunctuationToken("{", LEFT_PARENTHESIS)},
      {new NameToken("x"), new PunctuationToken("=", SINGLE_EQUAL), new NameToken("x"),
       new ArithmeticOperatorToken("+", PLUS), new NameToken("z"), new ArithmeticOperatorToken("*", MULTIPLY),
       new IntegerToken("5"), new ArithmeticOperatorToken("/", DIV), new IntegerToken("2"),
       new PunctuationToken(";", SEMICOLON)},
      {new NameToken("z"), new PunctuationToken("=", SINGLE_EQUAL), new PunctuationToken("(", LEFT_BRACE),
       new IntegerToken("10"), new ArithmeticOperatorToken("-", MINUS), new NameToken("x"),
       new PunctuationToken(")", RIGHT_BRACE), new ArithmeticOperatorToken("%", MOD), new IntegerToken("2"),
       new PunctuationToken(";", SEMICOLON)},
      {new PunctuationToken("}", RIGHT_PARENTHESIS)}
  };
  REQUIRE(CheckTokenStreamEquality(*actual, expected));
}

TEST_CASE("Checks if SP Tokenizer::MatchOtherToken works as expected") {
  string arithmetic_input = "x = x + z * 5 / 2;";
  string conditional_and_relational_input = "while (i > 0 && i <= 10)";
  Tokenizer* tokenizer = new Tokenizer();
  int skip_index = 0;
  SECTION("Test if it returns the ArithmeticOperatorToken with the correct ArithmeticOperatorType") {
    Token *t = tokenizer->MatchOtherToken(6, arithmetic_input, &skip_index);
    ArithmeticOperatorToken *aot = new ArithmeticOperatorToken("+", PLUS);
    REQUIRE(t->Equals(*aot));
  }

  SECTION("Test if it returns the ConditionalOperatorToken with the correct ConditionalOperatorType") {
    Token *t = tokenizer->MatchOtherToken(13, conditional_and_relational_input, &skip_index);
    ConditionalOperatorToken *cot = new ConditionalOperatorToken("&&", AND);
    REQUIRE(t->Equals(*cot));
  }

  SECTION("Test if it returns the RelationalOperatorToken with the correct RelationalOperatorType") {
    Token *t = tokenizer->MatchOtherToken(18, conditional_and_relational_input, &skip_index);
    RelationalOperatorToken *rot = new RelationalOperatorToken("<=", LTE);
    REQUIRE(t->Equals(*rot));
  }

  SECTION("Test if it returns the PunctuationToken with the correct PunctuationType") {
    Token *t = tokenizer->MatchOtherToken(6, conditional_and_relational_input, &skip_index);
    PunctuationToken *pt = new PunctuationToken("(", LEFT_BRACE);
    REQUIRE(t->Equals(*pt));
  }
}


