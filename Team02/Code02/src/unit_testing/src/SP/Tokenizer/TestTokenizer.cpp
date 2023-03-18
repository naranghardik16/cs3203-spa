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

  SECTION("Test if overkill next source works") {
    string input = "procedure A {\n"
                   "lol = lol + 1;\n"
                   "d = f * 3 - r;\n"
                   "if ((w == x) && ((w == y) && (w ==z))) then {\n"
                   "if ((y != z) || (!( (y > z) && (z <= y) ))) then {\n"
                   "read input101;\n"
                   "q = (a + b - c / d);\n"
                   "} else {\n"
                   "while(e != e) {\n"
                   "print output101;\n"
                   "}\n"
                   "}\n"
                   "} else {\n"
                   "w = (x + (y * z));\n"
                   "}\n"
                   "call B;\n"
                   "}\n"
                   "\n"
                   "procedure B {\n"
                   "while ((!(a != 0) && ( 0 > 1))) {\n"
                   "b = a - 1;\n"
                   "call D;\n"
                   "if (r != d) then {\n"
                   "read a;\n"
                   "} else {\n"
                   "call C;\n"
                   "}\n"
                   "print a;\n"
                   "print output202;\n"
                   "i =  (i + (1 + 2 + (3 + 4 + (5))));\n"
                   "while ((f > 4) || ((f <= 1) && (f != 5))) {\n"
                   "while (f < 6) {\n"
                   "f = f - 1;\n"
                   "if (d <= 0) then {\n"
                   "a = a + (5 * 10);\n"
                   "}\n"
                   "else {\n"
                   "r = t + 2 + 1 + 3 + 4 + 5 + 6 + 7 + z;\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "call E;\n"
                   "}\n"
                   "\n"
                   "procedure C {\n"
                   "if ( x >= 1) then {\n"
                   "read input301;\n"
                   "if ( a == 1 ) then {\n"
                   "read aVeryLargeInputToSeeIfLexerCanParseItCorrectlyLOLHopeItWorks7331is42TheAnswer;\n"
                   "} else {\n"
                   "complicatedCalculationHereWOOHOO = (1 + (1+2 + (1+2+3 + (1 + 2 + 3 * 4 * 5 / 6 - 7))));\n"
                   "}\n"
                   "} else {\n"
                   "while (y < 0) {\n"
                   "a = y + 1;\n"
                   "if (x == w + y) then {\n"
                   "x = x * 3 + y / z % 5 + 2 + 3 + 5 + 6 + 7;\n"
                   "y = c + 2 - z;\n"
                   "} else {\n"
                   "if((a==0)&&((b==0)&&(c==0))) then {\n"
                   "a = d + e + a + f + b + c + 1;\n"
                   "} else {\n"
                   "b = c + (a + 1);\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "call F;\n"
                   "}\n"
                   "\n"
                   "}\n"
                   "\n"
                   "procedure D {\n"
                   "while (f == 0) {\n"
                   "print result;\n"
                   "read result12321;\n"
                   "while(e == f + 6 % e) {\n"
                   "if (y != a) then {\n"
                   "while (w <= z) {\n"
                   "while (a == b - c * 20 / 10 + 20 % 5 ) {\n"
                   "t = 5 - (x / y % 2);\n"
                   "call F;\n"
                   "}\n"
                   "}\n"
                   "} else {\n"
                   "while (a - 5 < b) {\n"
                   "if(b == c - w + v) then {\n"
                   "a = 4 / (a % b * c);\n"
                   "} else {\n"
                   "read input401;\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "\n"
                   "procedure E {\n"
                   "if ((g == 0) && ((h>1) || ( (!(j < 2)) && (i != 0)))) then {\n"
                   "while (h < 1) {\n"
                   "if (j >= 2) then {\n"
                   "k = 1;\n"
                   "} else {\n"
                   "while(i <= 0) {\n"
                   "read something;\n"
                   "while (O == 0) {\n"
                   "print p;\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "}\n"
                   "} else {\n"
                   "l = m + 2 + 4 * 5 * 6 * 7 / 10;\n"
                   "}\n"
                   "\n"
                   "}\n"
                   "\n"
                   "procedure F {\n"
                   "read nothingToDoHere;\n"
                   "}";
    std::istringstream is;
    is.str(input);

    REQUIRE_NOTHROW(tokenizer->Tokenize(is));
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
