#include "catch.hpp"

#include <string>
#include <sstream>
#include "./SP/Parser/Parser.h"
#include "SP/Tokenizer/Tokenizer.h"
#include "SP/Validator/SpSemanticValidator.h"

TEST_CASE("Valid source program") {
  string input = "      procedure First {\n"
                 "      read x;\n"
                 "      read z;\n"
                 "      call Second; }\n"
                 "\n"
                 "      procedure Second {\n"
                 "        x = 0;\n"
                 "        i = 5;\n"
                 "        while (i!=0) {\n"
                 "            x = x + 2*y;\n"
                 "            call Third;\n"
                 "            i = i - 1; }\n"
                 "        if (x==1) then {\n"
                 "            x = x+1; }\n"
                 "          else {\n"
                 "            z = 1; }\n"
                 "        z = z + x + i;\n"
                 "        y = z + 2;\n"
                 "        x = x * y + z; }\n"
                 "\n"
                 "      procedure Third {\n"
                 "          z = 5;\n"
                 "          v = z;\n"
                 "          print v; }";
  std::istringstream is;
  is.str(input);

  shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
  shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(is);

  shared_ptr<Parser> parser = make_shared<Parser>();
  shared_ptr<Program> program = parser->ParseSource(*tokens);

  shared_ptr<SpSemanticValidator>
      validator = make_shared<SpSemanticValidator>();
  REQUIRE_NOTHROW(validator->ValidateProgram(program));
}

TEST_CASE(
    "Valid source program [Make sure that case sensitive works \"First\" and \"first\"]") {
  string input = "      procedure First {\n"
                 "      read x;\n"
                 "      read z;\n"
                 "      call first; }\n"
                 "\n"
                 "      procedure first {\n"
                 "        x = 0;\n"
                 "        i = 5;\n"
                 "        while (i!=0) {\n"
                 "            x = x + 2*y;\n"
                 "            call Third;\n"
                 "            i = i - 1; }\n"
                 "        if (x==1) then {\n"
                 "            x = x+1; }\n"
                 "          else {\n"
                 "            z = 1; }\n"
                 "        z = z + x + i;\n"
                 "        y = z + 2;\n"
                 "        x = x * y + z; }\n"
                 "\n"
                 "      procedure Third {\n"
                 "          z = 5;\n"
                 "          v = z;\n"
                 "          print v; }";
  std::istringstream is;
  is.str(input);

  shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
  shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(is);

  shared_ptr<Parser> parser = make_shared<Parser>();
  shared_ptr<Program> program = parser->ParseSource(*tokens);

  shared_ptr<SpSemanticValidator>
      validator = make_shared<SpSemanticValidator>();
  REQUIRE_NOTHROW(validator->ValidateProgram(program));
}

TEST_CASE(
    "Invalid source program [Program having 2 or more procedures with the same name]") {
  string input = "      procedure First {\n"
                 "      read x;\n"
                 "      read z;\n"
                 "      call Second; }\n"
                 "\n"
                 "      procedure Second {\n"
                 "        x = 0;\n"
                 "        i = 5;\n"
                 "        while (i!=0) {\n"
                 "            x = x + 2*y;\n"
                 "            call Third;\n"
                 "            i = i - 1; }\n"
                 "        if (x==1) then {\n"
                 "            x = x+1; }\n"
                 "          else {\n"
                 "            z = 1; }\n"
                 "        z = z + x + i;\n"
                 "        y = z + 2;\n"
                 "        x = x * y + z; }\n"
                 "\n"
                 "      procedure First {\n"
                 "          z = 5;\n"
                 "          v = z;\n"
                 "          print v; }";
  std::istringstream is;
  is.str(input);

  shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
  shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(is);

  shared_ptr<Parser> parser = make_shared<Parser>();
  shared_ptr<Program> program = parser->ParseSource(*tokens);

  shared_ptr<SpSemanticValidator>
      validator = make_shared<SpSemanticValidator>();
  REQUIRE_THROWS_AS(validator->ValidateProgram(program),
                    SemanticErrorException);
}

TEST_CASE(
    "Invalid source program [Recursive and cyclic calls are not allowed e.g. A calls A]") {
  string input = "      procedure First {\n"
                 "      read x;\n"
                 "      read z;\n"
                 "      call First; }\n"
                 "\n"
                 "      procedure Second {\n"
                 "        x = 0;\n"
                 "        i = 5;\n"
                 "        while (i!=0) {\n"
                 "            x = x + 2*y;\n"
                 "            call Second;\n"
                 "            i = i - 1; }\n"
                 "        if (x==1) then {\n"
                 "            x = x+1; }\n"
                 "          else {\n"
                 "            z = 1; }\n"
                 "        z = z + x + i;\n"
                 "        y = z + 2;\n"
                 "        x = x * y + z; }\n"
                 "\n"
                 "      procedure Third {\n"
                 "          z = 5;\n"
                 "          v = z;\n"
                 "          print v; }";
  std::istringstream is;
  is.str(input);

  shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
  shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(is);

  shared_ptr<Parser> parser = make_shared<Parser>();
  shared_ptr<Program> program = parser->ParseSource(*tokens);

  shared_ptr<SpSemanticValidator>
      validator = make_shared<SpSemanticValidator>();
  REQUIRE_THROWS_AS(validator->ValidateProgram(program),
                    SemanticErrorException);
}

TEST_CASE(
    "Invalid source program [Recursive and cyclic calls are not allowed e.g. A calls B, B calls C, C calls A]") {
  string input = "      procedure A {\n"
                 "      read x;\n"
                 "      read z;\n"
                 "      call B; }\n"
                 "\n"
                 "      procedure B {\n"
                 "        x = 0;\n"
                 "        i = 5;\n"
                 "        while (i!=0) {\n"
                 "            x = x + 2*y;"
                 "            call D;\n"
                 "            call C;\n"
                 "            i = i - 1; }\n"
                 "        if (x==1) then {\n"
                 "            x = x+1; }\n"
                 "          else {\n"
                 "            z = 1; }\n"
                 "        z = z + x + i;\n"
                 "        y = z + 2;\n"
                 "        x = x * y + z; }\n"
                 "\n"
                 "      procedure C {\n"
                 "          z = 5;\n"
                 "          v = z;\n"
                 "          print v;"
                 "          call A; }"
                 "\n"
                 "      procedure D {"
                 "        print x;"
                 "      }";
  std::istringstream is;
  is.str(input);

  shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
  shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(is);

  shared_ptr<Parser> parser = make_shared<Parser>();
  shared_ptr<Program> program = parser->ParseSource(*tokens);

  shared_ptr<SpSemanticValidator>
      validator = make_shared<SpSemanticValidator>();
  REQUIRE_THROWS_AS(validator->ValidateProgram(program),
                    SemanticErrorException);
}

TEST_CASE(
    "Invalid source program [A procedure cannot call a non-existing procedure]") {
  string input = "      procedure First {\n"
                 "      read x;\n"
                 "      read z;\n"
                 "      call Second; }\n"
                 "\n"
                 "      procedure Second {\n"
                 "        x = 0;\n"
                 "        i = 5;\n"
                 "        while (i!=0) {\n"
                 "            x = x + 2*y;\n"
                 "            call Fourth;\n"
                 "            i = i - 1; }\n"
                 "        if (x==1) then {\n"
                 "            x = x+1; }\n"
                 "          else {\n"
                 "            z = 1; }\n"
                 "        z = z + x + i;\n"
                 "        y = z + 2;\n"
                 "        x = x * y + z; }\n"
                 "\n"
                 "      procedure Third {\n"
                 "          z = 5;\n"
                 "          v = z;\n"
                 "          print v; }";
  std::istringstream is;
  is.str(input);

  shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
  shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(is);

  shared_ptr<Parser> parser = make_shared<Parser>();
  shared_ptr<Program> program = parser->ParseSource(*tokens);

  shared_ptr<SpSemanticValidator>
      validator = make_shared<SpSemanticValidator>();
  REQUIRE_THROWS_AS(validator->ValidateProgram(program),
                    SemanticErrorException);
}
