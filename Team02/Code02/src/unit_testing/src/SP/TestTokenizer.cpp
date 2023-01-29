
#include "./SP/Tokenizer.h"

#include "catch.hpp"
#include <string>
// must include <sstream> to use iss for istringstream
#include <sstream>

using namespace std;

void require(bool b) {
  REQUIRE(b);
}

TEST_CASE("1st Test") {
  string input = "while (i > 0) {\n"
                 "  x = x + z * 5;\n"
                 "  z = 2;\n"
                 "}";
  std::istringstream is;
  is.str(input);
  Tokenizer* tokenizer = new Tokenizer();
  tokenizer->tokenize(is);
  require(1 == 1);
}


