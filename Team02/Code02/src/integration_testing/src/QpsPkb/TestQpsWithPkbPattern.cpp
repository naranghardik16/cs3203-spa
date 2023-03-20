#include "catch.hpp"

#include <memory>

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

  SECTION("Test Exact Match Assign Statement") {
    TokenList token_list{make_shared<IntegerToken>("11"), make_shared<ArithmeticOperatorToken>("+", PLUS),
                         make_shared<NameToken>("x")};

    pkb_write->AddStatementOfAType("1", ASSIGN);
    pkb_write->AddStatementModifyingVariable("1", "y");
    pkb_write->AddAssignmentStatementAndExpression("1", egs->GetExpressionFromInput(token_list, "assign"));

    Query query = "assign a; variable v; Select a pattern a (v, _\"x\"_)";

    Results results;
    Qps::ProcessQuery(query, results, pkb_read);

    Results expected_results{"1"};
    REQUIRE(results == expected_results);
  }
}