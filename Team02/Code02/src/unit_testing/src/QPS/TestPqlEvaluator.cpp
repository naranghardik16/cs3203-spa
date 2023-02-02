#include "catch.hpp"
#include "QPS/QPSTypeDefs.h"
#include "QPS/Evaluator/PqlEvaluator.h"
#include "Stubs/StubPkb.h"
#include <memory>

ParserOutput CreateParserOutput(Map declaration_map, Synonym synonym) {
  ParserOutput output;
  ClauseSyntaxPtrList syntax_ptr_list;
  output.first = synonym;
  output.second.first = syntax_ptr_list; // in this trivial case there will be an empty syntax_ptr_list
  output.second.second = declaration_map;
  return output;
}

//! This is temporary -- will need to edit as PKB functions are completed and parser is completed
TEST_CASE("Check if PQLEvaluator works as expected given dummy inputs from PKB") {
  std::shared_ptr<PKB> pkb = std::make_shared<StubPkb>();
  SECTION("Test on variable synonym") {
    std::string query = "variable v;Select v";

    Map declaration_map = {{"v", "variable"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "v");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"a", "b", "c"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on statement synonym") {
    std::string query = "stmt s;Select s";

    Map declaration_map = {{"s", "stmt"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "s");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1", "2", "3"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on read synonym") {
    std::string query = "read r;Select r";

    Map declaration_map = {{"r", "read"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "r");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"4", "5", "6"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on print synonym") {
    std::string query = "print p;Select p";

    Map declaration_map = {{"p", "print"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "p");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"6", "7", "8"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on call synonym") {
    std::string query = "call c;Select c";

    Map declaration_map = {{"c", "call"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "c");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"9", "10", "11"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on while synonym") {
    std::string query = "while w;Select w";

    Map declaration_map = {{"w", "while"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "w");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"12", "13", "14"});
    REQUIRE(eval_result == correct_set);
  }


  SECTION("Test on if synonym") {
    std::string query = "if i;Select i";

    Map declaration_map = {{"i", "if"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "i");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"15", "16", "18"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on assign synonym") {
    std::string query = "assign a;Select a";

    Map declaration_map = {{"a", "assign"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "a");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"19", "20", "21"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on constant synonym") {
    std::string query = "constant c;Select c";

    Map declaration_map = {{"c", "constant"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "c");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"22", "23", "24"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on procedure synonym") {
    std::string query = "procedure p; Select p";

    Map declaration_map = {{"p", "procedure"}};
    ParserOutput correct_output = CreateParserOutput(declaration_map, "p");

    auto eval = std::make_shared<PqlEvaluator>(&correct_output, pkb);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"eval", "parse", "validate"});
    REQUIRE(eval_result == correct_set);
  }

}