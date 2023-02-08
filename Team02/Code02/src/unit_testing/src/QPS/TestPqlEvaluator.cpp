#include "catch.hpp"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Evaluator/PqlEvaluator.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/QueryParser.h"
#include <memory>
/*
std::shared_ptr<Query> CreateParserOutput(Map declaration_map, Synonym synonym) {
  ClauseSyntaxPtrList syntax_ptr_list;
  return std::make_shared<Query>(synonym, declaration_map, syntax_ptr_list);
}

//! This is temporary -- to make sure the demo can work -- need to figure out a way to create a stub PKB
TEST_CASE("Check if PQLEvaluator works as expected given dummy inputs from PKB") {
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<PkbReadFacade>(pkb_);

  SECTION("Test on variable synonym") {
    std::string query = "variable v;Select v";

    Map declaration_map = {{"v", "variable"}};
    auto correct_output = CreateParserOutput(declaration_map, "v");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);

    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"a", "b", "c"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on statement synonym") {
    std::string query = "stmt s;Select s";

    Map declaration_map = {{"s", "stmt"}};
    auto correct_output = CreateParserOutput(declaration_map, "s");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1", "2", "3"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on read synonym") {
    std::string query = "read r;Select r";

    Map declaration_map = {{"r", "read"}};
    auto correct_output = CreateParserOutput(declaration_map, "r");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"4", "5", "6"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on print synonym") {
    std::string query = "print p;Select p";

    Map declaration_map = {{"p", "print"}};
    auto correct_output = CreateParserOutput(declaration_map, "p");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"6", "7", "8"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on call synonym") {
    std::string query = "call c;Select c";

    Map declaration_map = {{"c", "call"}};
    auto correct_output = CreateParserOutput(declaration_map, "c");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"9", "10", "11"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on while synonym") {
    std::string query = "while w;Select w";

    Map declaration_map = {{"w", "while"}};
    auto correct_output = CreateParserOutput(declaration_map, "w");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"12", "13", "14"});
    REQUIRE(eval_result == correct_set);
  }


  SECTION("Test on if synonym") {
    std::string query = "if i;Select i";

    Map declaration_map = {{"i", "if"}};
    auto correct_output = CreateParserOutput(declaration_map, "i");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"15", "16", "18"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on assign synonym") {
    std::string query = "assign a;Select a";

    Map declaration_map = {{"a", "assign"}};
    auto correct_output = CreateParserOutput(declaration_map, "a");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"19", "20", "21"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on constant synonym") {
    std::string query = "constant c;Select c";

    Map declaration_map = {{"c", "constant"}};
    auto correct_output = CreateParserOutput(declaration_map, "c");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"22", "23", "24"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on procedure synonym") {
    std::string query = "procedure p; Select p";

    Map declaration_map = {{"p", "procedure"}};
    auto correct_output = CreateParserOutput(declaration_map, "p");
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"eval", "parse", "validate"});
    REQUIRE(eval_result == correct_set);
  }
}

//! For Demo Only
TEST_CASE("Check if PQLEvaluator works as expected using Parser") {

  auto qp = std::make_shared<QueryParser>();
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<PkbReadFacade>(pkb_);

  SECTION("Test on variable synonym") {
    std::string query = "variable v;Select v";

    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);

    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"a", "b", "c"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on read synonym") {
    std::string query = "read r;Select r";

    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"4", "5", "6"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on print synonym") {
    std::string query = "print p;Select p";

    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"6", "7", "8"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on assign synonym") {
    std::string query = "assign a;Select a";

    Map declaration_map = {{"a", "assign"}};
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"19", "20", "21"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on Modifies(Int, IDENT)") {
    std::string query = "variable v;Select v such that Modifies(1,v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"v", "v1"});
    REQUIRE(eval_result == correct_set);
  }
}

*/

/*

TEST_CASE("Temp") {
  auto qp = std::make_shared<QueryParser>();
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<PkbReadFacade>(pkb_);


  SECTION("Test on Modifies(Int, Int)") {
    std::string query = "variable v;Select v such that Modifies(1,\"v\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);

  }


  SECTION("Test on Modifies(Int, IDENT)") {
    std::string query = "variable v;Select v such that Modifies(1,v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"v", "v1"});
    REQUIRE(eval_result == correct_set);
  }

}
*/
