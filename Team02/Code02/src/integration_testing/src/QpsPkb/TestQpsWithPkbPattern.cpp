#include "catch.hpp"

#include <memory>

#include "core/model/Expression.h"
#include "ExpressionGeneratorStub/ExpressionGeneratorStub.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Pkb.h"
#include "QPS/Qps.h"

TEST_CASE("Check if QPS works with Pkb for Pattern Operations") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::shared_ptr<ExpressionGeneratorStub> ExpressionGeneratorPtr;

  typedef std::string Query;
  typedef std::list<std::string> Results;

  typedef std::vector<std::shared_ptr<Token>> TokenList;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  ExpressionGeneratorPtr egs = std::make_shared<ExpressionGeneratorStub>();

  // pure numbered expressions
  // 4 + 2
  TokenList token_list_pure_numbered_expression_1{
      make_shared<IntegerToken>("4"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2")
  };

  // 3 * 6 - 7 + 2
  TokenList token_list_pure_numbered_expression_2{
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("6"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("7"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2")
  };

  // 6 * 2 + (5 - 3) * 3 - 8
  TokenList token_list_pure_numbered_expression_3{
      make_shared<IntegerToken>("6"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("5"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("8")
  };

  // (3 + 4) + 7 * 2 - 1 - 9
  TokenList token_list_pure_numbered_expression_4{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("4"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("7"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("9")
  };

  // 5 - 2 + 4 * (8 - (5 + 1)) + 9
  TokenList token_list_pure_numbered_expression_5{
      make_shared<IntegerToken>("5"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("4"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("8"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("5"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("9")
  };

  // (8 - 1 + 3) * 6 - ((3 + 7) * 2)
  TokenList token_list_pure_numbered_expression_6{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("8"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("6"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("7"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS)
  };

  // 1 - 18 / (3 * 15)
  TokenList token_list_pure_numbered_expression_7{
      make_shared<IntegerToken>("1"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("18"),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("15"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS)
  };

  // (3 * 16 + 3 * 1)
  TokenList token_list_pure_numbered_expression_8{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("16"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS)
  };

  // (6 + 16) / 16
  TokenList token_list_pure_numbered_expression_9{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("6"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("16"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<IntegerToken>("16")
  };

  // 6 * 3 + 14 + 0 * (4 * 0 / 4) - (5 * 12 / 16) - ((4 + 0) - 20)
  TokenList token_list_pure_numbered_expression_10{
      make_shared<IntegerToken>("6"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("3"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("14"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("0"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("4"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("0"),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<IntegerToken>("4"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("5"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("12"),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<IntegerToken>("16"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("4"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("0"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("20"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS)
  };

  // expressions with variables
  // 11 + x
  TokenList token_list_expression_with_variables_1{
      make_shared<IntegerToken>("11"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("x")
  };

  // (x + 3) * 2
  TokenList token_list_expression_with_variables_2{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("2")
  };

  // x - 5
  TokenList token_list_expression_with_variables_3{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("5")
  };

  // 2 * x + 3
  TokenList token_list_expression_with_variables_4{
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3")
  };

  // x / 2
  TokenList token_list_expression_with_variables_5{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<IntegerToken>("2")
  };

  // x % 2
  TokenList token_list_expression_with_variables_6{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("%", MOD),
      make_shared<IntegerToken>("2")
  };

  // x * (x + 1) / 2
  TokenList token_list_expression_with_variables_7{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<IntegerToken>("2")
  };

  // (x + 3) * (x - 5) * (2 * x + 3) / (x / 2) % (x % 2)
  TokenList token_list_expression_with_variables_8{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("5"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("%", MOD),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("%", MOD),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS)
  };

  // ((x + 1) * (x + 2) * (x + 3)) - ((x - 1) * (x - 2) * (x - 3))
  TokenList token_list_expression_with_variables_9{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS)
  };

  // (x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) * (x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x)
  TokenList token_list_expression_with_variables_10{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("3"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("hello"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<IntegerToken>("64"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("x"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS)
  };

  // statement_number. <>
  // 1. y = 11 + x
  pkb_write->AddStatementOfAType("1", ASSIGN);
  pkb_write->AddStatementModifyingVariable("1", "y");
  pkb_write->AddAssignmentStatementAndExpression(
      "1", egs->GetExpressionFromInput(
          token_list_expression_with_variables_1, "assign"));

  // 2. y = x * (x + 1) / 2
  pkb_write->AddStatementOfAType("2", ASSIGN);
  pkb_write->AddStatementModifyingVariable("2", "y");
  pkb_write->AddAssignmentStatementAndExpression(
      "2", egs->GetExpressionFromInput(
          token_list_expression_with_variables_7, "assign"));

  // 3. x = (3 * 16 + 3 * 1)
  pkb_write->AddStatementOfAType("3", ASSIGN);
  pkb_write->AddStatementModifyingVariable("3", "x");
  pkb_write->AddAssignmentStatementAndExpression(
      "3", egs->GetExpressionFromInput(
          token_list_pure_numbered_expression_8, "assign"));

  // 4. z = 3 * 6 - 7 + 2
  pkb_write->AddStatementOfAType("4", ASSIGN);
  pkb_write->AddStatementModifyingVariable("4", "z");
  pkb_write->AddAssignmentStatementAndExpression(
      "4", egs->GetExpressionFromInput(
          token_list_pure_numbered_expression_2, "assign"));

  // 5. factor = (x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) * (x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x)
  pkb_write->AddStatementOfAType("5", ASSIGN);
  pkb_write->AddStatementModifyingVariable("5", "factor");
  pkb_write->AddAssignmentStatementAndExpression(
      "5", egs->GetExpressionFromInput(
          token_list_expression_with_variables_10, "assign"));

  // 6. FacTor = (x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) * (x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x)
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementModifyingVariable("6", "FacTor");
  pkb_write->AddAssignmentStatementAndExpression(
      "6", egs->GetExpressionFromInput(
          token_list_expression_with_variables_10, "assign"));



  SECTION("Test Exact Match Assign Statement") {
    Query query = "assign a; variable v; Select a pattern a (v, _\"x\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"1", "2", "5", "6"};
    REQUIRE(results == expected_results);
  }

  SECTION("All assignments") {
    Query query = "assign a; Select a pattern a (_,_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("All assignments by full pattern") {
    Query query = "assign a; Select a pattern a(_,\"3 * 6 - 7 + 2\")";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"4"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("All assignments by sub pattern") {
    Query query = "assign a; Select a pattern a(_,_\"3 * 6 - 7\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"4"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("No assignments by sub pattern") {
    Query query = "assign a; Select BOOLEAN pattern a(_,_\"6 - 7\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Using full pattern as sub pattern") {
    Query query = "assign a; Select a pattern a(_,_\"x * (x + 1) / 2\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"2"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Using brackets in sub-pattern - match") {
    Query query = "assign a; Select a pattern a(_,_\"((3 * 16) + (3 * 1))\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"3"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Using brackets in sub-pattern - no match") {
    Query query = "assign a; Select BOOLEAN pattern a(_,_\"(x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) * (x - 3) "
                  "* (2 * x + 1) * ((2 * hello - 1) / (64 * x))\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get assign by variable name") {
    Query query = "assign a; Select a pattern a(\"factor\",_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"5"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get assign by variable name - case insensitive") {
    Query query = "assign a; Select a pattern a(\"FacTor\",_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get by variable and full pattern") {
    Query query = "assign a; Select a pattern a(\"FacTor\",\"(x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) * "
                  "(x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x)\")";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get by variable and sub pattern - full expression") {
    Query query = "assign a; Select a pattern a(\"FacTor\",_\"(x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) * "
                  "(x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x)\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get by variable and sub pattern - subexpression") {
    Query query = "assign a; Select a pattern a(\"FacTor\",_\"(2 * hello - 1)\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get by variable and sub pattern - constant") {
    Query query = R"(assign a; Select a pattern a("FacTor",_"64"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get by variable and sub pattern - partial constant") {
    Query query = R"(assign a; Select a pattern a("FacTor",_"6"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get by variable and sub pattern - varname") {
    Query query = R"(assign a; Select a pattern a(_,_"hello"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get all assigned variables") {
    Query query = R"(assign a; variable v; Select v pattern a(v,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FacTor", "factor", "x", "y", "z"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get all variables by full pattern") {
    Query query = R"(assign a; variable v; Select v pattern a(v,"(x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) *
      (x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x) "))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FacTor", "factor"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get all variables by sub pattern - full expression") {
    Query query = R"(assign a; variable v; Select v pattern a(v,_"(x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) *
      (x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x) "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FacTor", "factor"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get all variables by sub pattern - sub expression") {
    Query query = R"(assign a; variable v; Select v pattern a(v,_"(2 * hello - 1) "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FacTor", "factor"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get all variables by sub pattern - varName") {
    Query query = R"(assign a; variable v; Select v pattern a(v,_"hello"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FacTor", "factor"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get all variables by sub pattern - partial varName") {
    Query query = R"(assign a; variable v; Select BOOLEAN pattern a(v,_"hel"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get all variables by sub pattern - constant") {
    Query query = R"(assign a; variable v; Select v pattern a(v,_"64"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FacTor", "factor"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Get assign by sub pattern - pattern is not substring") {
    Query query = R"(assign a; variable v; Select a pattern a(v,_"(2 * hello - 1) "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Bracket matters - correct bracket") {
    Query query = R"(assign a; variable v; Select a pattern a(v,_"((x + 1) * (x + 2)) "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Bracket matters - wrong bracket") {
    Query query = R"(assign a; variable v; Select BOOLEAN pattern a(v,_"x + 1 * x + 2 "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("AST lhs and rhs cannot swap - sub pattern") {
    Query query = R"(assign a; variable v; Select BOOLEAN pattern a(v,_"((x + 2) * (x + 1)) "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("AST lhs and rhs cannot swap - full pattern") {
    Query query = R"(assign a; variable v; Select BOOLEAN pattern a(v,_"x + 11 "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("RHS is not an expression - syntactic error") {
    Query query = R"(assign a; variable v; Select BOOLEAN pattern a(v,_"y = 11 + x; "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Using partial expression as subpattern - syntactic error") {
    Query query = R"(assign a; Select BOOLEAN pattern a(_,_"+ x"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Using operator as subpattern - syntactic error") {
    Query query = R"(assign a; Select BOOLEAN pattern a(_,_"+"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Using mismatching brackets in subpattern - syntactic error") {
    Query query = R"(assign a; Select BOOLEAN pattern a(_,_"x * (x + (1 / 2) "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(s, _) - Semantic Error") {
    Query query = R"(assign a; read r; Select BOOLEAN pattern a(r,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(r, _) - Semantic Error") {
    Query query = R"(assign a; read r; Select BOOLEAN pattern a(r,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(pn, _) - Semantic Error") {
    Query query = R"(assign a; print pn; Select BOOLEAN pattern a(pn,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(a1, _) - Semantic Error") {
    Query query = R"(assign a; assign a1; Select BOOLEAN pattern a(a1,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(w, _) - Semantic Error") {
    Query query = R"(assign a; while w; Select BOOLEAN pattern a(w,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(cl, _) - Semantic Error") {
    Query query = R"(assign a; call cl; Select BOOLEAN pattern a(cl,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(c, _) - Semantic Error") {
    Query query = R"(assign a; constant c; Select BOOLEAN pattern a(c,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(p, _) - Semantic Error") {
    Query query = R"(assign a; procedure p; Select BOOLEAN pattern a(p,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, s) - Syntactic Error") {
    Query query = R"(assign a; stmt s; Select BOOLEAN pattern a(_,s))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, r) - Syntactic Error") {
    Query query = R"(assign a; read s; Select BOOLEAN pattern a(_,r))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, pn) - Syntactic Error") {
    Query query = R"(assign a; print pn; Select BOOLEAN pattern a(_,pn))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, a1) - Syntactic Error") {
    Query query = R"(assign a; assign a1; Select BOOLEAN pattern a(_,a1))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, ifs) - Syntactic Error") {
    Query query = R"(assign a; if ifs; Select BOOLEAN pattern a(_,ifs))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, w) - Syntactic Error") {
    Query query = R"(assign a; while w; Select BOOLEAN pattern a(_,w))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, cl) - Syntactic Error") {
    Query query = R"(assign a; call cl; Select BOOLEAN pattern a(_,cl))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, v) - Syntactic Error") {
    Query query = R"(assign a; variable v; Select BOOLEAN pattern a(_,v))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_, p) - Syntactic Error") {
    Query query = R"(assign a; procedure p; Select BOOLEAN pattern a(_,p))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern a(_,_,_) - Syntactic Error") {
    Query query = R"(assign a; procedure p; Select BOOLEAN pattern a(_,_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Empty full pattern - Syntactic Error") {
    Query query = R"(assign a; Select BOOLEAN pattern a(_,""))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Invalid full pattern - Syntactic Error") {
    Query query = R"(assign a; Select BOOLEAN pattern a(_,"_"))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Empty full pattern - Syntactic Error") {
    Query query = R"(assign a; Select BOOLEAN pattern a(_,_""_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("Invalid full pattern - Syntactic Error") {
    Query query = R"(assign a; Select BOOLEAN pattern a(_,_"_"_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

  SECTION("stmt syn pattern - Semantic Error") {
    Query query = R"(stmt pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("read syn pattern - Semantic Error") {
    Query query = R"(read pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("print syn pattern - Semantic Error") {
    Query query = R"(print pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("call syn pattern - Semantic Error") {
    Query query = R"(call pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("while syn pattern") {
    Query query = R"(while pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    REQUIRE(results == expected_results);
  }

  SECTION("if syn pattern ") {
    Query query = R"(if pattern; Select BOOLEAN pattern pattern(_,_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"FALSE"};
    REQUIRE(results == expected_results);
  }

  SECTION("if syn pattern ") {
    Query query = R"(if pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("var syn pattern ") {
    Query query = R"(variable pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("const syn pattern ") {
    Query query = R"(constant pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("procedure syn pattern ") {
    Query query = R"(procedure pattern; Select BOOLEAN pattern pattern(_,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SemanticError"};
    REQUIRE(results == expected_results);
  }

  SECTION("assign syn wildcard pattern - tuple ") {
    Query query = R"(assign a; variable v; Select <a,v> pattern a(v,_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"1 y", "2 y", "3 x", "4 z", "5 factor", "6 FacTor"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("assign syn full pattern - tuple ") {
    Query query = R"(assign a; variable v; Select <a,v> pattern a(v,"(x + 1) * (x + 2) * (x + 3) * (x - 1) * (x - 2) *
      (x - 3) * (2 * x + 1) * (2 * hello - 1) / (64 * x) "))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"5 factor", "6 FacTor"};
    REQUIRE(results == expected_results);
  }

  SECTION("assign syn sub pattern - tuple ") {
    Query query = R"(assign a; variable v; Select <a,v> pattern a(v,_"(64 * x) "_))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"5 factor", "6 FacTor"};
    REQUIRE(results == expected_results);
  }

  SECTION("Pattern w (v, _, _) - syntactic error ") {
    Query query = R"(while w; variable v; Select BOOLEAN pattern w (v, _, _) ))";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"SyntaxError"};
    REQUIRE(results == expected_results);
  }

//  Check why failing
//  SECTION("Pattern a (v, _) - overload subpattern - ideal ") {
//    Query query = R"(assign BOOLEAN; variable v; Select BOOLEAN pattern BOOLEAN (v, _"(2 * hello - 1) "_)))";
//
//    Results results;
//    Qps::ProcessQuery(query, results, pkb_read);
//
//    Results expected_results{"5", "6"};
//    REQUIRE(results == expected_results);
//  }

//  SECTION("Pattern ifs (v, _, _) - select ifs ") {
//    Query query = R"(if ifs; variable v; Select v pattern ifs (v,_, _))";
//
//    Results results;
//    Qps::ProcessQuery(query, results, pkb_read);
//
//    Results expected_results{"5 factor", "6 FacTor"};
//    REQUIRE(results == expected_results);
//  }
}
