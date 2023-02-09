
#include "catch.hpp"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Evaluator/PqlEvaluator.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/QueryParser.h"
#include <memory>

TEST_CASE("Check if PQLEvaluator works for basic select statements") {
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<PkbReadFacade>(pkb_);
  auto qp = std::make_shared<QueryParser>();

  SECTION("Test on variable synonym") {
    std::string query = "variable v;Select v";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);

    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"a", "b", "c", "x", "y"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on statement synonym") {
    std::string query = "stmt s;Select s";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1", "2", "3"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on read synonym") {
    std::string query = "read r;Select r";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"4", "5", "6"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on print synonym") {
    std::string query = "print p;Select p";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on call synonym") {
    std::string query = "call c;Select c";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"9", "10", "11"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on while synonym") {
    std::string query = "while w;Select w";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"12", "13", "14"});
    //REQUIRE(eval_result == correct_set);
  }


  SECTION("Test on if synonym") {
    std::string query = "if i;Select i";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"15", "16", "18"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on assign synonym") {
    std::string query = "assign a;Select a";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"19", "20", "21"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on constant synonym") {
    std::string query = "constant c;Select c";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"22", "23", "24"});
    //REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on procedure synonym") {
    std::string query = "procedure p; Select p";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"eval", "parse", "validate"});
    //REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Make sure Evaluation of Modifies Statement works") {
  auto qp = std::make_shared<QueryParser>();
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<PkbReadFacade>(pkb_);

  //! test are based on stmt 1 : print x
  //stub->GetVariablesModifiedByStatement(1) will not be empty
  SECTION("INT, WILDCARD, Return True from PKB so get all variables") {
    std::string query = "variable v;Select v such that Modifies(1,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"a", "b", "c", "x", "y"});
    REQUIRE(eval_result == correct_set);
  }

  //stub->GetVariablesModifiedByStatement(20) will be empty
  SECTION("INT, WILDCARD, Return False from PKB so get empty set") {
    std::string query = "variable v;Select v such that Modifies(20,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  //e.g.Select v such that Modifies(1,v)
  //stub->GetVariablesModifiedByStatement(1) will give "x";
  SECTION("INT, SYN") {
    std::string query = "variable v;Select v such that Modifies (1, v)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"x"});
    REQUIRE(eval_result == correct_set);
  }

  // Modifies(1, "x") -- does 1 modify "x"?
  // stub->HasModifiesStatementRelationship(first_arg_, second_arg_) --> stub will return true for (1, "x")
  SECTION("INT, IDENT, Return True from PKB so get all variables") {
    std::string query = "variable v;Select v such that Modifies(1,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);

    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"a", "b", "c", "x", "y"});
    REQUIRE(eval_result == correct_set);
  }

  // Stub->HasModifiesStatementRelationship will return false for stmt num 20
  SECTION("INT, IDENT, Return False from PKB so get empty set") {
    std::string query = "variable v;Select v such that Modifies(20,\"v\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  // Should return the print statements that have a Modifies relationship with any variable
  // stub->GetStatementsThatModify(StatementType::Print) will return {"1"} e.g. print x;
  SECTION("SYN, Wildcard, Returns a set") {
    std::string query = "print print;Select print such that Modifies(print,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(print,v)
  // stub->GetModifiesStatementVariablePairs(print) will return {<1,x>}
  SECTION("SYN, Wildcard, Returns a set") {
    std::string query = "print print;   variable pattern;     Select print   such   that  Modifies( print , pattern)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(print,”count”) -- get print statements that modify count
  //stub->GetStatementsModifiesVariable("count", PrintType) --> return {}
  SECTION("SYN, IDENT, Returns a empty set") {
    std::string query = "print print;Select print such that Modifies(print,\"count\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

}

TEST_CASE("Make sure Modifies Procedure Works") {
  //Modifies("anya", _) -- does the procedure anya modify any variables?
  // return !pkb->GetVariablesModifiedByProcedure(first_arg_).empty();

  //e.g.Select v such that Modifies("anya",v)
  // single_constraint = pkb->GetVariablesModifiedByProcedure(first_arg_);

  //Modifies("anya", "count") -- does the procedure anya modify "count"?
  // return pkb->HasModifiesProcedureRelationship(first_arg_, second_arg_);

  //e.g. Select p such that Modifies(p, _) / Select p1 such that Modifies(p1,_)
  // Should return the procedure that have a Modifies relationship with any variable
  //single_constraint = pkb->GetProceduresThatModify();

  // e.g. Modifies(p,v)
  // pair_constraint = pkb->GetModifiesProcedureVariablePairs();

  //e.g. Modifies(p,”count”) -- get procedures that modify count
  // single_constraint = pkb->GetProceduresModifiesVariable(second_arg_);


}