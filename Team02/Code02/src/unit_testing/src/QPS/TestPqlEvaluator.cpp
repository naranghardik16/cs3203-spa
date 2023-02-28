#include "catch.hpp"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Evaluator/PqlEvaluator.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "QPS/QueryParser.h"
#include "StubPKB/StubPKBReadFacade.h"
#include <memory>


TEST_CASE("Check if PQLEvaluator works for basic select statements") {
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<StubPkbReadFacade>(pkb_);
  auto qp = std::make_shared<QueryParser>();

  SECTION("Test on variable synonym") {
    std::string query = "variable v;Select v";
    auto output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"a","x", "y", "g"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on statement synonym") {
    std::string query = "stmt s;Select s";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1", "2", "3", "4", "5", "6", "7", "8", "9"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on read synonym") {
    std::string query = "read r;Select r";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on print synonym") {
    std::string query = "print p;Select p";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"4", "9"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on call synonym") {
    std::string query = "call c;Select c";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"3"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on while synonym") {
    std::string query = "while w;Select w";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"8"});
    REQUIRE(eval_result == correct_set);
  }


  SECTION("Test on if synonym") {
    std::string query = "if i;Select i";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"5"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test on assign synonym") {
    std::string query = "assign a;Select a";

    auto output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
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
    REQUIRE(eval_result == correct_set);
  }
}


TEST_CASE("Make sure Evaluation of Modifies Statement works") {
  auto qp = std::make_shared<QueryParser>();
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<StubPkbReadFacade>(pkb_);

  //! test are based on stmt 1 : read x
  //stub->GetVariablesModifiedByStatement(1) will not be empty so get all var
  SECTION("INT, WILDCARD, Return True from PKB so get all variables") {
    std::string query = "variable v;Select v such that Modifies(1,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"a", "x", "y", "g"});
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
    std::unordered_set<std::string> correct_set({"a","x", "y", "g"});
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

  // Should return the read statements that have a Modifies relationship with any variable
  // stub->GetStatementsThatModify(StatementType::READ) will return {"1"} e.g. read x;
  SECTION("SYN, Wildcard, Returns a set") {
    std::string query = "read read;Select read such that Modifies(read,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(read,v)
  // stub->GetModifiesStatementVariablePairs(READ) will return {<1,x>}
  SECTION("STMT-SYN, VAR-SYN, Returns a set") {
    std::string query = "read read;   variable pattern;     Select read   such   that  Modifies( read , pattern)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(read,”count”) -- get read statements that modify count
  //stub->GetStatementsModifiesVariable("count", READType) --> return {}
  SECTION("STMT-SYN, IDENT, Returns a empty set") {
      std::string query = "read read;Select read such that Modifies(read,\"count\")";
      auto correct_output = qp->ParseQuery(query);

      auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
      auto eval_result = eval->Evaluate();

      std::unordered_set<std::string> correct_set({});
      REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(c, "x") -- get call statements that modify x
  //stub->GetStatementsModifiesVariable("x", CallType) --> return {}
  SECTION("CALL-SYN, IDENT, Return empty set") {
    std::string query = "call c;Select c such that Modifies(c, \"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  //e.g.Select read r such that Modifies(r1,”x”)
  //stub->GetStatementsModifiesVariable("x", READ) --> return {1}
  SECTION("IRRELEVANT-SYN, IDENT, Return empty set") {
    std::string query = "read r,r1; Select r such that Modifies(r1, \"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

}

TEST_CASE("Make sure Modifies Procedure Works") {
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<StubPkbReadFacade>(pkb_);
  auto qp = std::make_shared<QueryParser>();


  //! Test case is based on procedure execute which modifies y, and procedure anya which does not modify any var
  //Modifies("anya", _) -- does the procedure anya modify any variables?
  // stub->GetVariablesModifiedByProcedure("anya") will return empty so we return empty set
  SECTION("IDENT, WILDCARD, Returns a empty set") {
    std::string query = "call c;Select c such that Modifies(\"anya\", _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  //e.g.Select v such that Modifies("anya",v) -- what variables are modified by anya
  //stub->GetVariablesModifiedByProcedure("anya") will return empty;
  SECTION("IDENT, SYN, Returns a empty set") {
    std::string query = "variable v;Select v such that Modifies(\"anya\", v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  //Modifies("anya", "y") -- does the procedure anya modify "count"?
  //stub->HasModifiesProcedureRelationship("anya", "y") --> returns false so we should get empty set
  SECTION("IDENT, IDENT, Returns a empty set") {
    std::string query = "variable v;Select v such that Modifies(\"anya\", \"y\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
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
    REQUIRE(eval_result == correct_set);
  }

  // e.g. Modifies(p,v)
  // stub->GetModifiesProcedureVariablePairs() will return {<"execute","x">}
  SECTION("SYN, wildcard, Returns a set") {
    std::string query = "procedure p;variable v;Select p such that Modifies(p,v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"execute"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Modifies(p,”y”) -- get procedures that modify count
  // single_constraint = pkb->GetProceduresModifiesVariable("y") will return "execute"
  SECTION("SYN, IDENT, Returns a empty set") {
    std::string query = "procedure p;variable v;Select p such that Modifies(p,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"execute"});
    REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Test Uses Statement Clause Evaluator") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  SECTION("Uses(2, _), boolean check passes") {
    std::string query = "assign a;Select a such that Uses(2,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(1, _), boolean check fails") {
    std::string query = "assign a;Select a such that Uses(1,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(2, \"x\"), boolean check passes") {
    std::string query = "assign a;Select a such that Uses(2,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(1, \"x\"), boolean check fails") {
    std::string query = "assign a;Select a such that Uses(1,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(2, v)") {
    std::string query = "variable v;Select v such that Uses(2,v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"x", "y"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(an, _)") {
    std::string query = "assign an;Select an such that Uses(an,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(an, \"x\")") {
    std::string query = "assign an;Select an such that Uses(an,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(an, v)") {
    std::string query = "assign an;variable v;Select an such that Uses(an,v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Test Uses Procedure Clause Evaluator") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  SECTION("Uses(\"anya\", _), boolean check passes") {
    std::string query = "assign a;Select a such that Uses(\"anya\",_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(\"Main\", _), boolean check fails") {
    std::string query = "assign a;Select a such that Uses(\"Main\",_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(\"anya\", \"x\"), boolean check passes") {
    std::string query = "assign a;Select a such that Uses(\"anya\",\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(\"Main\", \"x\"), boolean check fails") {
    std::string query = "assign a;Select a such that Uses(\"Main\",\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(\"anya\", v)") {
    std::string query = "variable v;Select v such that Uses(\"anya\",v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"x", "y"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(p, _)") {
    std::string query = "procedure p;Select p such that Uses(p,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"anya"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(p, \"x\")") {
    std::string query = "procedure p;Select p such that Uses(p,\"x\")";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"anya"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Uses(p, v)") {
    std::string query = "procedure p;variable v;Select p such that Uses(p,v)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"anya"});
    REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Make sure Follows Clause Evaluator Works") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  //! Boolean Constraints

  //e.g. Follows(_,_) -- return all Follows relationships between statements
  //stub->IsAnyFollowsRelationshipPresent() will return true so all the assign statements will be returned {2}
  SECTION("WILDCARD, WILDCARD, Returns a empty set") {
    std::string query = "assign a;Select a such that Follows(_,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

    //e.g. Follows(_,"3") --> Get all types of statements that stmt 3 follows
    //stub->GetStatementFollowedBy(3, StatementType::STATEMENT) --> returns {2} --> since not empty we return all assign statements
  SECTION("WILDCARD, INT, Returns a set") {
    std::string query = "assign a;Select a such that Follows(_,3)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

    //e.g. Follows("1", _) --> Get all types of statements that follow "1"
    //return !pkb->GetStatementFollowing(1, StatementType::STATEMENT) --> returns {2} so not empty --> return all assign
  SECTION("INT, WILDCARD, Returns a set") {
    std::string query = "assign a;Select a such that Follows(1,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

    //e.g. Follows(5, 6)
    //return pkb->HasFollowsRelationship(1,2) will be true so return all assign
  SECTION("INT, INT, Returns a set") {
    std::string query = "assign a;Select a such that Follows(1,2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

    //! Non Boolean Constraints

    //e.g. Follows("1", a) --> Get statement that follow 5 of type assignment
    //stub>GetStatementFollowing(1, ASSIGN) will give 2
  SECTION("INT, SYN, Returns a set") {
    std::string query = "assign a;Select a such that Follows(1,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(_, a) --> Get assignments that follow another statement
  //stub->GetStatementThatAreFollowers(a) --> {2}
  SECTION("WILDCARD, SYN, Returns a set") {
    std::string query = "assign a;Select a such that Follows(_,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(c, _) --> Get call statements that have followers
  //stub->GetStatementsWithFollowers(CALL) will return {}
  SECTION("SYN, WILDCARD, Returns a set") {
    std::string query = "call c;Select c such that Follows(c,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(p,a)
  //stub->GetFollowPairs(read,ASSIGN) -> {<1,2>}
  SECTION("SYN, SYN, Returns a set") {
    std::string query = "read r;assign a;Select r such that Follows(r,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Follows(a,"2") --> Get statement that 2 follows of type assignment
  //stub->GetStatementFollowedBy(2, ASSIGN) -> {}
  SECTION("SYN, INT, Returns a set") {
    std::string query = "read r;assign a;Select a such that Follows(a, 2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Test FollowsStar Clause Evaluator") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  SECTION("Follows*(_, _), boolean check passes") {
    std::string query = "assign a;Select a such that Follows*(_, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(1, _), boolean check passes") {
    std::string query = "assign a;Select a such that Follows*(1, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(4, _), boolean check fails") {
    std::string query = "assign a;Select a such that Follows*(_, 4)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(_, 2), boolean check passes") {
    std::string query = "assign a;Select a such that Follows*(_, 2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(_, 1), boolean check fails") {
    std::string query = "assign a;Select a such that Follows*(_, 1)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(1, 2), boolean check passes") {
    std::string query = "assign a;Select a such that Follows*(1, 2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({{"2", "6", "7"}});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(1, 4), boolean check fails") {
    std::string query = "assign a;Select a such that Follows*(1, 4)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(s1, s2)") {
    std::string query = "stmt s1, s2;Select s1 such that Follows*(s1, s2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1", "2"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(s1, _)") {
    std::string query = "stmt s1, s2;Select s1 such that Follows*(s1, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1", "2"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(_, s2)") {
    std::string query = "stmt s1, s2;Select s2 such that Follows*(_, s2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "3"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(s1, 2)") {
    std::string query = "stmt s1, s2;Select s1 such that Follows*(s1, 2)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Follows*(2, s1)") {
    std::string query = "stmt s1, s2;Select s1 such that Follows*(2, s1)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"3"});
    REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Make sure Parent Clause Evaluator Works") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  //! Boolean Constraints
  //e.g. Select r such that Parent(_,_) -- are there any Parent-Child relationships between assignments --> returns all r
  //stub->IsAnyParentRelationshipPresent() returns true so get all read statements
  SECTION("Wildcard, Wildcard, Returns a set") {
    std::string query = "read r,r1;assign a;Select r such that Parent(_, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }
  //e.g. Parent(_,"5") --> Get all types of statements that "5" is child of
  //stub->GetStatementThatIsParentOf(5, StatementType::STATEMENT) -> {} so return {}
  SECTION("SYN, INT, Returns a set") {
    std::string query = "read r,r1;assign a;Select r such that Parent(_,5)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent("5", _) --> Get all types of statements that are child of"5"
  //stub->GetStatementsThatAreChildrenOf(5, StatementType::STATEMENT) --> {6,7} --> return all read statements
  SECTION("INT, Wildcard, Returns a set") {
    std::string query = "read r,r1;assign a;Select r such that Parent(5,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent(5, 6) --> Check if 5 is parent of 6
  //stub->HasParentChildRelationship(5,6) is true so get all read statements
  SECTION("INT, INT, Returns a set") {
    std::string query = "read r,r1;assign a;Select r such that Parent(5,6)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"1"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent(r, _) --> Get read statements that are parents
  //stub->GetStatementsThatAreParents(READ) will return {} so return empty
  SECTION("INT, INT, Returns a set") {
    std::string query = "read r,r1;assign a;Select r such that Parent(r,_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  //! Non boolean constraints

  //e.g. Parent("5", a) --> Get assign statements that are children of 5
  //single_constraint = pkb->GetStatementsThatAreChildrenOf(5, assign) will return {"6", "7"}
  SECTION("INT, STMT-SYN, Returns a set") {
    std::string query = "if if;assign a;Select a such that Parent(5,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"6","7"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent(_, a) --> Get statements are child of any other statement
  //single_constraint = pkb->GetStatementsThatAreChildren(Assign) --> {5,6} --> return all if statements
  SECTION("Wildcard STMT-SYN, Returns a set") {
    std::string query = "if if;assign a;Select if such that Parent(_,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"5"});
    REQUIRE(eval_result == correct_set);
  }


  //e.g. Parent(if,a) --> get (assign stmt parent, print stmt child) pairs
  //stub->GetParentChildPairs(if, assign) --> {(5,6), (5,7)}
  SECTION("STMT-SYN, STMT-SYN, Returns a set") {
    std::string query = "if if;assign a;Select if such that Parent(if,a)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"5"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent(a,"5") --> Get assign statement that is parent of 5
  //stub->GetStatementThatIsParentOf(5, STATEMENT) --> {};
  SECTION("STMT-SYN, STMT-SYN, Returns a set") {
    std::string query = "if if;assign a;Select if such that Parent(a,5)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

}

TEST_CASE("Make sure ParentStar Clause Evaluator Works") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  //! Boolean Constraints
  //e.g. Parent*(_,_) -- return all Parent*-Descendant relationships between statements
  //return stub->IsAnyAncestorDescendantRelationshipPresent() is true so return all print statements
  SECTION("Wildcard, Wildcard, Returns a set") {
    std::string query = "if if;print p;Select p such that Parent*(_, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"4", "9"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent*(_,"9") --> Get all types of statements that "9" is descendant to
  //return !pkb->GetStatementsThatAreAncestorOf(9, StatementType::STATEMENT) will return {5} so return all print statements
  SECTION("Wildcard, INT, Returns a set") {
    std::string query = "if if;print p;Select p such that Parent*(_, 9)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"4", "9"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent*("5", _) --> Get all types of statements that are descendants of "5"
  //stub->GetStatementsThatAreDescendantsOf("5", StatementType::STATEMENT) will return 9 so return all print statements
  SECTION("INT, Wildcard, Returns a set") {
    std::string query = "if if;print p;Select p such that Parent*(5,_)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"4", "9"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent*(5, 6) --> Check if 5 is parent of 6
  //stub->HasAncestorDescendantRelationship(5,9) will return true
  SECTION("INT, INT, Returns a set") {
    std::string query = "if if;print p;Select p such that Parent*(5,9)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"4", "9"});
    REQUIRE(eval_result == correct_set);
  }

  //! Non Boolean Constraints

  //e.g. Parent("5", a) --> Get assign statements that are descendants of 5
  //stub-> will gGetStatementsThatAreDescendantsOf(5, p) give 9
  SECTION("INT, STMT-SYN, Returns a set") {
    std::string query = "if if;print p;Select p such that Parent*(5,p)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"9"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent*(_, p) --> Get print statements that are descendant of any other statement type
  //stub->GetStatementsThatAreDescendants(print) will give 9
  SECTION("Wildcard, STMT-SYN, Returns a set") {
    std::string query = "if if;print p;Select p such that Parent*(_,p)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"9"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent*(if, _) --> Get if statements that are ancestors
  //stub->GetStatementsThatAreAncestors(if);
  SECTION("SYN, Wildcard, Returns a set") {
    std::string query = "if if;print p;Select if such that Parent*(if,_)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"5"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent*(a,p) --> get (if stmt parent, assign stmt descendant) pairs
  //stub->GetAncestorDescendantPairs(if, print) will give {(5,9)}
  SECTION("SYN, SYN, Returns a set") {
    std::string query = "if if;print p;Select if such that Parent*(if,p)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"5"});
    REQUIRE(eval_result == correct_set);
  }

  //e.g. Parent*(if,"5") --> Get if statements that are ancestors of 9
  //stub->GetStatementsThatAreAncestorOf(9, if);
  SECTION("SYN, INT, Returns a set") {
    std::string query = "if if;print p;Select if such that Parent*(if,9)";
    auto correct_output = qp->ParseQuery(query);
    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();
    std::unordered_set<std::string> correct_set({"5"});
    REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Test pattern evaluator") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  SECTION("pattern a(_, _)") {
    std::string query = "assign a;Select a pattern a(_, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("pattern a(v, _), Select a") {
    std::string query = "assign a;variable v;Select a pattern a(v, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("pattern a(v, _), Select v") {
    std::string query = "assign a;variable v;Select v pattern a(v, _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"a", "y" });
    REQUIRE(eval_result == correct_set);
  }

  SECTION("pattern a(\"a\", _)") {
    std::string query = "assign a;Select a pattern a(\"a\", _)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("pattern a(_, _\"x\"_)") {
    std::string query = "assign a;Select a pattern a(_, _\"x\"_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("pattern a(v, _\"x\"_), Select a") {
    std::string query = "assign a; variable v;Select a pattern a(v, _\"x\"_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("pattern a(\"a\", _\"x\"_), Select v") {
    std::string query = "assign a; variable v;Select a pattern a(\"a\", _\"x\"_)";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2"});
    REQUIRE(eval_result == correct_set);
  }
}

TEST_CASE("Multi-clause tests") {
  PKB pkb_ = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade_ = std::make_shared<StubPkbReadFacade>(pkb_);
  auto qp = std::make_shared<QueryParser>();


  //query = "assign a; variable v; Select v such that Uses(a, v) pattern a(_,_\"g\"_)";
  std::string query = "assign a; variable v; Select v such that Uses(a, v) pattern a(\"a\",_)";
  auto correct_output = qp->ParseQuery(query);
  auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  auto eval_result = eval->Evaluate();
  std::unordered_set<std::string> correct_set = {"a", "y"};
  REQUIRE(eval_result == correct_set);


  //2 syn that are shared in both clauses/4 synonyms
  // {{"2", "x"}, {"2", "y"}}; --> uses(a,v); do for assign {{"2", "a"}, {"2", "y"}, {6,"g"}, {"7", "y"}}
  //Get assign modifies var pairs --> ("2", "a"), ("6", "y"), ("7", "y")}; --> pattern a(v,_)

  query = "assign a; variable v;Select a such that Uses(a, v) pattern a(v,_)";
  correct_output = qp->ParseQuery(query);
  eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  eval_result = eval->Evaluate();
  correct_set ={"2", "7"};
  REQUIRE(eval_result == correct_set);

  query = "assign a; variable v;Select v such that Uses(a, v) pattern a(v,_)";
  correct_output = qp->ParseQuery(query);
  eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  eval_result = eval->Evaluate();
  correct_set = {"a", "y"};
  REQUIRE(eval_result == correct_set);

  //1 syn that is shared between both clauses/3 synonyms
  query = "assign a; variable v; Select a such that Uses(a, v) pattern a(_,_\"g\"_)";
  correct_output = qp->ParseQuery(query);
  eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  eval_result = eval->Evaluate();
  correct_set = {"6"};
  REQUIRE(eval_result == correct_set);

  //1 syn that is shared between both clauses/2 synonyms
  //Uses(a, "g") --> return 6
  //all assign --> 2,6,7
  //pattern(_,_g_) --> 6

  query = "assign a; variable v; Select a such that Uses(a, \"g\") pattern a(_, _\"g\"_)";
  correct_output = qp->ParseQuery(query);
  eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  eval_result = eval->Evaluate();
  correct_set = {"6"};
  REQUIRE(eval_result == correct_set);

  query = "assign a; variable v; Select v such that Uses(6, v) pattern a(_,_)";
  correct_output = qp->ParseQuery(query);
  eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  eval_result = eval->Evaluate();
  correct_set = {"g"};
  REQUIRE(eval_result == correct_set);

  // 0 syn that is shared between both clauses/1 synonyms
  query = "assign Select,pattern; variable v; Select Select such that Uses(6, \"g\") pattern Select(_,_)";
  correct_output = qp->ParseQuery(query);
  eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  eval_result = eval->Evaluate();
  correct_set = {"2", "6", "7"};
  REQUIRE(eval_result == correct_set);

  //select all var
  query = "assign Select,pattern; variable v; Select v such that Uses(6, \"g\") pattern Select(_,_)";
  correct_output = qp->ParseQuery(query);
  eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade_);
  eval_result = eval->Evaluate();
  correct_set =  {"a", "y", "x", "g"};
  REQUIRE(eval_result == correct_set);

}


TEST_CASE("Test With Clause Evaluator") {
  PKB pkb = PKB();
  std::shared_ptr<PkbReadFacade> pkb_read_facade = std::make_shared<StubPkbReadFacade>(pkb);
  auto qp = std::make_shared<QueryParser>();

  SECTION("Test Boolean case -- INT = INT") {
    std::string query = "assign a;Select a with 5=5";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({"2", "6", "7"});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- INT != INT") {
    std::string query = "assign a;Select a with 5=6";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- INT = IDENT") {
    std::string query = "assign a;Select a with 5=\"x\"";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- IDENT = INT") {
    std::string query = "assign a;Select a with \"x\"=5";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- INT = IDENT") {
    std::string query = "assign a;Select a with 5=\"x\"";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- ident return value attrName = .value") {
    std::string query = "procedure p; constant c; assign a; Select a with p.procName = c.value";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);

    query = "variable v; constant c; assign a; Select a with v.varName = c.value";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);

    query = "read r; constant c;  assign a; Select a with r.varName = c.value";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);

    query = "print p; constant c;  assign a; Select a with p.varName = c.value";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- ident return value attrName = .stmt#") {
    std::string query = "procedure p; assign a; Select a with p.procName = a.stmt#";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);

    query = "variable v; assign a; Select a with v.varName = a.stmt#";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);

    query = "read r; assign a; Select a with r.varName = a.stmt#";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);

    query = "print p; assign a; Select a with p.varName = a.stmt#";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- attr-ref that returns IDENT = int") {
    std::string query = "procedure p; assign a; Select a with p.procName = 5";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);

    query = "variable v; assign a; Select a with v.varName = 5";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);

    query = "read r; assign a; Select a with r.varName = 5";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);

    query = "print p; assign a; Select a with p.varName = 5";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);
  }

  SECTION("Test Boolean case -- attr-ref that returns INT = IDENT") {
    std::string query = "procedure p; assign a; Select a with \"x\"=a.stmt#";
    auto correct_output = qp->ParseQuery(query);

    auto eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    auto eval_result = eval->Evaluate();

    std::unordered_set<std::string> correct_set({});
    REQUIRE(eval_result == correct_set);

    query = "assign a; Select a with a.stmt#=\"x\"";
    correct_output = qp->ParseQuery(query);

    eval = std::make_shared<PqlEvaluator>(correct_output, pkb_read_facade);
    eval_result = eval->Evaluate();

    correct_set = {};
    REQUIRE(eval_result == correct_set);
  }
}
