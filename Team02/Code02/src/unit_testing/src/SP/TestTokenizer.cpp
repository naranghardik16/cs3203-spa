
#include "./SP/Tokenizer.h"

#include "catch.hpp"
#include <string>
// must include <sstream> to use iss for istringstream
#include <sstream>

using namespace std;

void require(bool b) {
  REQUIRE(b);
}

TEST_CASE("SP Tokenizer::Tokenize Test") {
  string input = "while (i > 0 && i <= 10) {\n"
                 "  x = x + z * 5 / 2;\n"
                 "  z = (10 - x) % 2;\n"
                 "}";
  std::istringstream is;
  is.str(input);
  Tokenizer* tokenizer = new Tokenizer();
  tokenizer->Tokenize(is);
  require(1 == 1);
}

TEST_CASE("SP Tokenizer::MatchToken Test") {
  string arithmetic_input = "x = x + z * 5 / 2;";
  string conditional_and_relational_input = "while (i > 0 && i <= 10)";
  Tokenizer* tokenizer = new Tokenizer();
  int skip_index = 0;
  SECTION("Test if it returns the ArithmeticOperatorToken with the correct ArithmeticOperatorType") {
    Token *t = tokenizer->MatchToken(6, arithmetic_input, &skip_index);
    ArithmeticOperatorToken *aot = new ArithmeticOperatorToken("+", PLUS);
    require(t->Equals(*aot));
  }

  SECTION("Test if it returns the ConditionalOperatorToken with the correct ConditionalOperatorType") {
    Token *t = tokenizer->MatchToken(13, conditional_and_relational_input, &skip_index);
    ConditionalOperatorToken *cot = new ConditionalOperatorToken("&&", AND);
    require(t->Equals(*cot));
  }

  SECTION("Test if it returns the RelationalOperatorToken with the correct RelationalOperatorType") {
    Token *t = tokenizer->MatchToken(18, conditional_and_relational_input, &skip_index);
    RelationalOperatorToken *rot = new RelationalOperatorToken("<=", LTE);
    require(t->Equals(*rot));
  }

  SECTION("Test if it returns the PunctuationToken with the correct PunctuationType") {
    Token *t = tokenizer->MatchToken(6, conditional_and_relational_input, &skip_index);
    PunctuationToken *pt = new PunctuationToken("(", LEFT_BRACE);
    require(t->Equals(*pt));
  }
}


