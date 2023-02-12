#include "catch.hpp"

#include "QPS/QueryParser.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Clause/PatternClauseSyntax.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"

SyntaxPair CreateCorrectSyntaxPairParser(std::string entity, std::string first_parameter, std::string second_parameter) {
  auto parameter_pair = std::pair<std::string, std::string>(first_parameter, second_parameter);
  SyntaxPair syntax;
  syntax.first = entity;
  syntax.second = parameter_pair;
  return syntax;
}

TEST_CASE("Test Query Parser") {
  auto qp = std::make_shared<QueryParser>();

  SECTION("Test valid query with random spacing") {
    std::string query("assign a;\nSelect a such that Uses(a, \"count\") pattern a(_,       _  \"  y\" _)");
    auto parser_output = qp->ParseQuery(query);
    auto synonym = parser_output->GetSynonym();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair pattern_syntax_pair = CreateCorrectSyntaxPairParser("a", "_", "_y_");
    std::shared_ptr<ClauseSyntax> pattern_syntax_ptr = std::make_shared<PatternClauseSyntax>(pattern_syntax_pair);
    SyntaxPair such_that_syntax_pair = CreateCorrectSyntaxPairParser("Uses", "a", "\"count\"");
    std::shared_ptr<ClauseSyntax>
        such_that_syntax_ptr = std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    ClauseSyntaxPtrList correct_syntax_ptr_list;
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    correct_syntax_ptr_list.push_back(pattern_syntax_ptr);

    for (int i = 0; i < clause_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }

    Map correct_declaration_map = {{"a", "assign"}};
    Synonym correct_synonym = "a";

    REQUIRE(correct_synonym == synonym);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }


  SECTION("Test valid query with 1 pattern and 1 such that with random spacing") {
    std::string query("assign a;\nSelect   a pattern   a (  \"x\"   ,     _\"x\"_   )    such that      Uses   (      a,  \"x\" )  ");
    auto parser_output = qp->ParseQuery(query);
    auto synonym = parser_output->GetSynonym();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair pattern_syntax_pair = CreateCorrectSyntaxPairParser("a", "\"x\"", "_x_");
    std::shared_ptr<ClauseSyntax> pattern_syntax_ptr = std::make_shared<PatternClauseSyntax>(pattern_syntax_pair);
    SyntaxPair such_that_syntax_pair = CreateCorrectSyntaxPairParser("Uses", "a", "\"x\"");
    std::shared_ptr<ClauseSyntax> such_that_syntax_ptr = std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    ClauseSyntaxPtrList correct_syntax_ptr_list;
    correct_syntax_ptr_list.push_back(pattern_syntax_ptr);
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);

    for (int i = 0; i < clause_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }

    Map correct_declaration_map = {{"a", "assign"}};
    Synonym correct_synonym = "a";

    REQUIRE(correct_synonym == synonym);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with repeated terminal names") {
    std::string query
        ("    assign     pattern; variable      Select        ;\nSelect Select such that Uses(pattern, Select) pattern pattern(Select, _\"x\"_)");
    auto parser_output = qp->ParseQuery(query);
    auto synonym = parser_output->GetSynonym();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair pattern_syntax_pair = CreateCorrectSyntaxPairParser("pattern", "Select", "_x_");
    std::shared_ptr<ClauseSyntax> pattern_syntax_ptr = std::make_shared<PatternClauseSyntax>(pattern_syntax_pair);
    SyntaxPair such_that_syntax_pair = CreateCorrectSyntaxPairParser("Uses", "pattern", "Select");
    std::shared_ptr<ClauseSyntax>
        such_that_syntax_ptr = std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    ClauseSyntaxPtrList correct_syntax_ptr_list;
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    correct_syntax_ptr_list.push_back(pattern_syntax_ptr);

    for (int i = 0; i < clause_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }

    Map correct_declaration_map = {{"pattern", "assign"}, {"Select", "variable"}};
    Synonym correct_synonym = "Select";

    REQUIRE(correct_synonym == synonym);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }


  SECTION("Test valid query with a basic select statement") {
    std::string query("variable k; Select k");
    auto parser_output = qp->ParseQuery(query);
    auto synonym = parser_output->GetSynonym();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_clause_syntax_ptr_list = {};
    Map correct_declaration_map = {{"k", "variable"}};
    Synonym correct_synonym = "k";
    REQUIRE(correct_clause_syntax_ptr_list == clause_syntax_ptr_list);
    REQUIRE(correct_synonym == synonym);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }


  SECTION("Test invalid query with invalid such that") {
    std::string query("assign a;Select assign suchthatModifies(assign,\"count\") pattern a(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }


  SECTION("Test invalid query with invalid such that due to multiple extra characters") {
    std::string query("assign a;Select assign such that Uses((assign,\"count\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select assign such that Uses(assign,\"count\"))";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select assign such that Uses(assign,\"count\"))";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select assign such that a Uses(assign,\"count\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }



  SECTION("Test invalid query with invalid pattern") {
    std::string query("assign a;Select assign such that Modifies(assign,\"count\") patterna(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with 2 syntactically invalid subclauses") {
    std::string query("assign pattern;Select pattern such thatModifies(pattern,\"count\") patternpattern(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }


  SECTION("Test invalid query with no declarations") {
    std::string query("Select a");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }


  SECTION("Test invalid query with no Select statement") {
    std::string query("assign a;");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with only Select keyword") {
    std::string query("assign a; Select");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }


  SECTION("Test invalid query with missing select statement") {
    std::string query("assign Select;Select such that Modifies(Select,\"count\") pattern Select(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;a such that Modifies(a,\"count\") pattern a(\"count\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with missing synonym") {
    std::string query("assign a;Select such that Modifies(a,\"count\") pattern a(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with syntactically wrong synonym") {
    std::string query("assign 1a,b;Select 1a such that Follows*(1a,b) pattern a(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with no declarations") {
    std::string query("Select assign suchthat;Modifies(assign,\"count\") pattern a(\"count\", _);");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with syntactically invalid design entity") {
    std::string query("statement s;Select s such that Parent*(s,\"count\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with no comma") {
    std::string query("statement s s1;Select s such that Parent*(s,\"count\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with extra characters at the end") {
    std::string query("assign a;Select assign suchthat;Modifies(assign,\"count\") pattern a(\"count\", _);");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query") {
    std::string query("variables v; Select a");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query") {
    std::string query("variables v; Select a such that (1,)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query") {
    std::string query("variable v; Select a such that Follo(1,)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query_v is not stmt ref_throw semantic error") {
    std::string query("variable v; assign a; Select a such that Follows(1,v)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }

  SECTION("Test invalid query_synonym not declared_throw semantic error") {
    std::string query("assign a; Select a such that Follows(_,s)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }

  SECTION("Test invalid query - invalid wildcard - throw semantic error") {
    std::string query("variable a; Select a such that Uses(_,a)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }

  SECTION("Test valid query - valid pattern expr") {
    std::string query("assign a; Select a pattern a(_, _)");
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test invalid query - invalid pattern expr - throw syntax error") {
    std::string query("assign a; Select a such that Follows(a, _) pattern a(_, _\"\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query - invalid pattern expr - throw syntax error") {
    std::string query("stmt a; Select a pattern a(_, _\"x\"_)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }
}
