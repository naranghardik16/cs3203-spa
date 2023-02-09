
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
    std::unordered_set<std::string> correct_set({"a","x", "y"});
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

    std::unordered_set<std::string> correct_set({"4"});
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

    std::unordered_set<std::string> correct_set({"2"});
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

    std::unordered_set<std::string> correct_set({"execute", "anya"});
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

    std::unordered_set<std::string> correct_set({"a","x", "y"});
    //REQUIRE(eval_result == correct_set);
  }

  //stub->GetVariablesModifiedByStatement(20) will be empty
  SECTION("INT, WILDCARD, Return False from PKB so get empty set") {
    std::string query = "variable v;Select v such that Modifies(20,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g.Select v such that Modifies(1,v)
  //stub->GetVariablesModifiedByStatement(1) will give "x";
  SECTION("INT, SYN") {
    std::string query = "variable v;Select v such that Modifies (1, v)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"x"});
    //REQUIRE(eval_result == correct_set);
  }

  // Modifies(1, "x") -- does 1 modify "x"?
  // stub->HasModifiesStatementRelationship(first_arg_, second_arg_) --> stub will return true for (1, "x")
  SECTION("INT, IDENT, Return True from PKB so get all variables") {
    std::string query = "variable v;Select v such that Modifies(1,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);

    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"a","x", "y"});
    //REQUIRE(eval_result == correct_set);
  }

  // Stub->HasModifiesStatementRelationship will return false for stmt num 20
  SECTION("INT, IDENT, Return False from PKB so get empty set") {
    std::string query = "variable v;Select v such that Modifies(20,\"v\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }

  // Should return the print statements that have a Modifies relationship with any variable
  // stub->GetStatementsThatModify(StatementType::Print) will return {"1"} e.g. print x;
  SECTION("SYN, Wildcard, Returns a set") {
    std::string query = "print print;Select print such that Modifies(print,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(print,v)
  // stub->GetModifiesStatementVariablePairs(print) will return {<1,x>}
  SECTION("SYN, Wildcard, Returns a set") {
    std::string query = "print print;   variable pattern;     Select print   such   that  Modifies( print , pattern)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(print,”count”) -- get print statements that modify count
  //stub->GetStatementsModifiesVariable("count", PrintType) --> return {}
  SECTION("SYN, IDENT, Returns a empty set") {
    std::string query = "print print;Select print such that Modifies(print,\"count\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }

}

TEST_CASE("Make sure Modifies Procedure Works") {
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<PkbReadFacade>(pkb_);
  auto qp = std::make_shared<QueryParser>();


  //! Test case is based on procedure execute which modifies y, and procedure anya which does not modify any var
  //Modifies("anya", _) -- does the procedure anya modify any variables?
  // stub->GetVariablesModifiedByProcedure("anya") will return empty;
  SECTION("IDENT, WILDCARD, Returns a empty set") {
    std::string query = "print print;Select print such that Modifies(\"anya\", _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g.Select v such that Modifies("anya",v) -- what variables are modified by anya
  //stub->GetVariablesModifiedByProcedure("anya") will return empty;
  SECTION("IDENT, SYN, Returns a empty set") {
    std::string query = "variable v;Select v such that Modifies(\"anya\", v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }

  //Modifies("anya", "y") -- does the procedure anya modify "count"?
  //stub->HasModifiesProcedureRelationship("anya", "y") --> returns false so we should get empty set
  SECTION("IDENT, IDENT, Returns a empty set") {
    std::string query = "variable v;Select v such that Modifies(\"anya\", \"y\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Select p such that Modifies(p, _) / Select p1 such that Modifies(p1,_)
  // Should return the procedure that have a Modifies relationship with any variable
  //stub->GetProceduresThatModify() will return {"execute"} --> the procedure execute modifies x
  SECTION("SYN, wildcard, Returns a set") {
    std::string query = "procedure p;Select p such that Modifies(p,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"execute"});
   //REQUIRE(eval_result == correct_set);
  }

  // e.g. Modifies(p,v)
  // stub->GetModifiesProcedureVariablePairs() will return {<"execute","x">}
  SECTION("SYN, wildcard, Returns a set") {
    std::string query = "procedure p;variable v;Select p such that Modifies(p,v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"execute"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(p,”y”) -- get procedures that modify count
  // single_constraint = pkb->GetProceduresModifiesVariable("y") will return "execute"
  SECTION("SYN, IDENT, Returns a empty set") {
    std::string query = "procedure p;variable v;Select p such that Modifies(p,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"execute"});
    //REQUIRE(eval_result == correct_set);
  }
}


TEST_CASE("Make sure Follows Clause Evaluator Works") {
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<PkbReadFacade>(pkb_);
  auto qp = std::make_shared<QueryParser>();

  //! Boolean Constraints

  //e.g. Follows(_,_) -- return all Follows relationships between statements
  //stub->IsAnyFollowsRelationshipPresent() will return true so all the assign statements will be returned {2}
  SECTION("WILDCARD, WILDCARD, Returns a empty set") {
    std::string query = "assign a;Select a such that Follows(_,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(_,"3") --> Get all types of statements that stmt 3 follows
  //stub->GetStatementsFollowedBy(3, StatementType::ALL) --> returns {1,2} --> since not empty we return all assign statements
  SECTION("WILDCARD, INT, Returns a set") {
    std::string query = "assign a;Select a such that Follows(_,3)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows("1", _) --> Get all types of statements that follow "1"
  //return !pkb->GetStatementsFollowing(1, StatementType::ALL) --> returns {2,3} so not empty --> return all assign
  SECTION("INT, WILDCARD, Returns a set") {
    std::string query = "assign a;Select a such that Follows(1,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(5, 6)
  //return pkb->HasFollowsRelationship(1,2) will be true so return all assign
  SECTION("INT, INT, Returns a set") {
    std::string query = "assign a;Select a such that Follows(1,2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    //REQUIRE(eval_result == correct_set);
  }

  //! Non Boolean Constraints

  //e.g. Follows("1", a) --> Get statement that follow 5 of type assignment
  //stub>GetStatementsFollowing(1, ASSIGN) will give 2
  SECTION("INT, SYN, Returns a set") {
    std::string query = "assign a;Select a such that Follows(1,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(_, a) --> Get assignmnents that follow another statement
  //stub->GetStatementThatAreFollowers(a) --> {2}
  SECTION("WILDCARD, SYN, Returns a set") {
    std::string query = "assign a;Select a such that Follows(_,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(c, _) --> Get call statements that have followers
  //pkb->GetStatementsWithFollowers(CALL) will return {}
  SECTION("SYN, WILDCARD, Returns a set") {
    std::string query = "call c;Select c such that Follows(c,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(p,a)
  //pkb->GetFollowPairs(PRINT,ASSIGN) -> {<1,2>}
  SECTION("SYN, SYN, Returns a set") {
    std::string query = "print p;assign a;Select p such that Follows(p,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    //REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(a,"2") --> Get statement that 2 follows of type assignment
  //stub->GetStatementsFollowedBy(2, ASSIGN) -> {}
  SECTION("SYN, INT, Returns a set") {
    std::string query = "print p;assign a;Select a such that Follows(a, 2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    //REQUIRE(eval_result == correct_set);
  }


}