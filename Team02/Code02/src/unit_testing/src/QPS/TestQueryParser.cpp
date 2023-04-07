#include "catch.hpp"

#include "QPS/QueryParser.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Clause/PatternClauseSyntax.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "QPS/Clause/WithClauseSyntax.h"

SyntaxPair CreateCorrectSyntaxPairParser(std::string entity, std::string first_parameter,
                                         std::string second_parameter) {
  ParameterVector parameter_vec = {first_parameter, second_parameter};
  SyntaxPair syntax;
  syntax.first = entity;
  syntax.second = parameter_vec;
  return syntax;
}

SyntaxPair CreateCorrectThreeArgSyntaxPairParser(std::string entity, std::string first_parameter,
                                                 std::string second_parameter, std::string third_parameter) {
  ParameterVector parameter_vector = {first_parameter, second_parameter, third_parameter};
  SyntaxPair syntax;
  syntax.first = entity;
  syntax.second = parameter_vector;
  return syntax;
}

TEST_CASE("Test Invalid Multi Clause") {
  auto qp = std::make_shared<QueryParser>();
  SECTION("extra with_syntax error") {
    std::string query("assign a; while w; Select a such that Parent* (w, a) with and Modifies "
                      "(a, \"x\") and such that Modifies (a, \"y\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("extra and_syntax error") {
    std::string query("assign a; while w; Select a and such that Parent* (w, a) and Modifies "
                      "(a, \"x\") such that Modifies (a, \"y\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("extra such that_syntax error") {
    std::string query("assign a; while w; Select a such that Parent* (w, a) such that such that Modifies (a, \"x\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("extra pattern_syntax error") {
    std::string query("assign a; while w; Select a such that Parent* (w, a) such that Modifies (a, \"x\") pattern ");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("extra characters_syntax error") {
    // extra char at end
    std::string query("assign a; while w; Select a such that Parent* (w, a) such that Modifies (a, \"x\") and ");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // extra )
    query = "assign a; while w; Select a such that Parent* (w, a)) such that Modifies (a, \"x\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // extra <
    query = "assign a; while w; Select a <such that Parent* (w, a) such that Modifies (a, \"x\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }
}

TEST_CASE("Test Invalid And Clause") {
  auto qp = std::make_shared<QueryParser>();
  SECTION("And with such that_syntax error") {
    std::string query("assign a; while w; Select a such that Parent* (w, a) and Modifies (a, \"x\") "
                      "and such that Modifies (a, \"y\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("And with pattern_Throw syntax error") {
    std::string query("assign a; while w; Select a such that Parent* (w, a) and pattern a (\"x\", _) "
                      "such that Modifies (a, \"y\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("And with different clause_Throw syntax error") {
    // pattern + and such that
    std::string query("assign a; while w; Select a such that Parent* (w, a) pattern a (\"x\", _) "
                      "and Modifies (a, \"x\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);

    // pattern + and with
    query = "assign a; while w; Select a such that Parent* (w, a) pattern a (\"x\", _) and a.stmt#=w.stmt#";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // such that + and pattern
    query = "assign a; while w; Select a such that Parent* (w, a) and a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // such that + and with
    query = "assign a; while w; Select a such that Parent* (w, a) and a.stmt#=w.stmt#";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // with + and pattern
    query = "assign a; while w; Select a such that Parent* (w, a) with a.stmt#=w.stmt# and pattern a (\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // with + and such that
    query = "assign a; while w; Select a such that Parent* (w, a) with a.stmt#=w.stmt# and Parent* (w, a)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("And with no previous clause_Throw syntax error") {
    std::string query("assign a; while w; Select a and Modifies (a, \"x\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("And with extra character_Throw syntax error") {
    std::string query("assign a; while w; Select a such that Modifies (a, \"x\") and 1 Modifies (a, \"x\")");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
    query = "procedure p; Select p with p.procName=\"x\" and 1 5=6";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "procedure p;Select p with p.procName=\"x\" and \"x\" \"x\"=6";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "procedure p; Select p with p.procName=\"x\" and = s.stmt#=6";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "procedure p;Select p with p.procName=\"x\" and s.stmt#=6 5=6";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }
}


TEST_CASE("Test multi-clause queries") {
  auto qp = std::make_shared<QueryParser>();

  SECTION("Multi clause -- chain of withs") {
    std::string query = "read r; print p;Select r.varName with p.varName = r.varName and 5=5 "
                        "and \"x\"=\"x\" and p.varName = \"number\"";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto vector = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair correct_with1_syntax = CreateCorrectSyntaxPairParser("", "p.varName", "r.varName");
    SyntaxPair correct_with2_syntax = CreateCorrectSyntaxPairParser("", "5", "5");
    SyntaxPair correct_with3_syntax = CreateCorrectSyntaxPairParser("", "\"x\"", "\"x\"");
    SyntaxPair correct_with4_syntax = CreateCorrectSyntaxPairParser("", "p.varName", "\"number\"");
    std::shared_ptr<ClauseSyntax>
        with1_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with1_syntax);
    std::shared_ptr<ClauseSyntax>
        with2_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with2_syntax);
    std::shared_ptr<ClauseSyntax>
        with3_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with3_syntax);
    std::shared_ptr<ClauseSyntax>
        with4_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with4_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {with1_clause_ptr, with2_clause_ptr,
                                                                 with3_clause_ptr, with4_clause_ptr};
    Map correct_declaration_map = {{"r", "read"}, {"p", "print"}};
    SelectedSynonymTuple correct_synonym_tuple = {"r.varName"};
    for (int i = 0; i < correct_vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Multi clause query with tuple") {
    std::string query = "assign with, Parent; while w; Select < with. stmt#, w . stmt#, Parent > pattern Parent(_,_) "
                        "and with(_,_) with Parent.stmt#=with.stmt# and 6 = 5 such that Parent(w,Parent)";
    auto parser_output = qp->ParseQuery(query);

    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto vector = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair correct_if_syntax =
        CreateCorrectSyntaxPairParser("Parent", "_", "_");
    SyntaxPair correct_parent_syntax =
        CreateCorrectSyntaxPairParser("with", "_", "_");
    SyntaxPair correct_with_syntax =
        CreateCorrectSyntaxPairParser("", "Parent.stmt#", "with.stmt#");
    SyntaxPair correct_with2_syntax =
        CreateCorrectSyntaxPairParser("", "6", "5");
    SyntaxPair correct_parent2_syntax =
        CreateCorrectSyntaxPairParser("Parent", "w", "Parent");
    std::shared_ptr<ClauseSyntax>
        pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_if_syntax);
    std::shared_ptr<ClauseSyntax>
        parent_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_parent_syntax);
    std::shared_ptr<ClauseSyntax>
        with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::shared_ptr<ClauseSyntax>
        with2_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with2_syntax);
    std::shared_ptr<ClauseSyntax>
        parent2_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parent2_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>>
        correct_vector = {pattern_clause_ptr, parent_clause_ptr, with_clause_ptr, with2_clause_ptr, parent2_clause_ptr};
    Map correct_declaration_map = {{"Parent", "assign"}, {"with", "assign"},
                                   {"w", "while"}};
    SelectedSynonymTuple correct_synonym_tuple = {"with.stmt#", "w.stmt#", "Parent"};
    for (int i = 0; i < correct_vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Multi clause query with BOOLEAN") {
    std::string query = "assign with, Parent; while w; Select BOOLEAN pattern Parent(_,_) and with(_,_) "
                        "with Parent.stmt#=with.stmt# and 6 = 5 such that Parent(w,Parent)";
    auto parser_output = qp->ParseQuery(query);

    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto vector = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair correct_if_syntax =
        CreateCorrectSyntaxPairParser("Parent", "_", "_");
    SyntaxPair correct_parent_syntax =
        CreateCorrectSyntaxPairParser("with", "_", "_");
    SyntaxPair correct_with_syntax =
        CreateCorrectSyntaxPairParser("", "Parent.stmt#", "with.stmt#");
    SyntaxPair correct_with2_syntax =
        CreateCorrectSyntaxPairParser("", "6", "5");
    SyntaxPair correct_parent2_syntax =
        CreateCorrectSyntaxPairParser("Parent", "w", "Parent");
    std::shared_ptr<ClauseSyntax>
        pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_if_syntax);
    std::shared_ptr<ClauseSyntax>
        parent_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_parent_syntax);
    std::shared_ptr<ClauseSyntax>
        with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::shared_ptr<ClauseSyntax>
        with2_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with2_syntax);
    std::shared_ptr<ClauseSyntax>
        parent2_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parent2_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>>
        correct_vector = {pattern_clause_ptr, parent_clause_ptr, with_clause_ptr, with2_clause_ptr, parent2_clause_ptr};
    Map correct_declaration_map = {{"Parent", "assign"}, {"with", "assign"},
                                   {"w", "while"}};
    SelectedSynonymTuple correct_synonym_tuple = {};
    for (int i = 0; i < correct_vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Multi clause query with BOOLEAN as syn") {
    std::string query = "assign with, BOOLEAN; while w; Select BOOLEAN pattern BOOLEAN(_,_) and "
                        "with(_,_) with BOOLEAN.stmt#=with.stmt# and 6 = 5 such that Parent(w,BOOLEAN)";
    auto parser_output = qp->ParseQuery(query);

    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto vector = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair correct_if_syntax = CreateCorrectSyntaxPairParser("BOOLEAN", "_", "_");
    SyntaxPair correct_parent_syntax = CreateCorrectSyntaxPairParser("with", "_", "_");
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPairParser("", "BOOLEAN.stmt#", "with.stmt#");
    SyntaxPair correct_with2_syntax = CreateCorrectSyntaxPairParser("", "6", "5");
    SyntaxPair correct_parent2_syntax = CreateCorrectSyntaxPairParser("Parent", "w", "BOOLEAN");
    std::shared_ptr<ClauseSyntax>
        pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_if_syntax);
    std::shared_ptr<ClauseSyntax>
        parent_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_parent_syntax);
    std::shared_ptr<ClauseSyntax>
        with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::shared_ptr<ClauseSyntax>
        with2_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with2_syntax);
    std::shared_ptr<ClauseSyntax>
        parent2_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parent2_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>>
        correct_vector = {pattern_clause_ptr, parent_clause_ptr, with_clause_ptr, with2_clause_ptr, parent2_clause_ptr};
    Map correct_declaration_map = {{"BOOLEAN", "assign"}, {"with", "assign"},
                                   {"w", "while"}};
    SelectedSynonymTuple correct_synonym_tuple = {"BOOLEAN"};
    for (int i = 0; i < correct_vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Multi clause query with attr-ref") {
    std::string query = "assign with, Parent; while w; Select with . stmt# pattern Parent(_,_) and "
                        "with(_,_) with Parent.stmt#=with.stmt# and 6 = 5 such that Parent(w,Parent)";
    auto parser_output = qp->ParseQuery(query);

    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto vector = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair correct_if_syntax =
        CreateCorrectSyntaxPairParser("Parent", "_", "_");
    SyntaxPair correct_parent_syntax =
        CreateCorrectSyntaxPairParser("with", "_", "_");
    SyntaxPair correct_with_syntax =
        CreateCorrectSyntaxPairParser("", "Parent.stmt#", "with.stmt#");
    SyntaxPair correct_with2_syntax =
        CreateCorrectSyntaxPairParser("", "6", "5");
    SyntaxPair correct_parent2_syntax =
        CreateCorrectSyntaxPairParser("Parent", "w", "Parent");
    std::shared_ptr<ClauseSyntax>
        pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_if_syntax);
    std::shared_ptr<ClauseSyntax>
        parent_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_parent_syntax);
    std::shared_ptr<ClauseSyntax>
        with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::shared_ptr<ClauseSyntax>
        with2_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with2_syntax);
    std::shared_ptr<ClauseSyntax>
        parent2_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parent2_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>>
        correct_vector = {pattern_clause_ptr, parent_clause_ptr, with_clause_ptr, with2_clause_ptr, parent2_clause_ptr};
    Map correct_declaration_map = {{"Parent", "assign"}, {"with", "assign"},
                                   {"w", "while"}};
    SelectedSynonymTuple correct_synonym_tuple = {"with.stmt#"};
    for (int i = 0; i < correct_vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }
}

TEST_CASE("Test Valid Simple Query Parser") {
  auto qp = std::make_shared<QueryParser>();

  SECTION("Attr-ref as synonym with repeated terminal names with with clause") {
    std::string query = "assign with; Select    with. stmt# with with.  stmt#=5";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_syntax_ptr_list = {};
    SyntaxPair with_syntax_pair = CreateCorrectSyntaxPairParser("", "with.stmt#", "5");
    std::shared_ptr<ClauseSyntax> with_syntax_ptr = std::make_shared<WithClauseSyntax>(with_syntax_pair);
    correct_syntax_ptr_list.push_back(with_syntax_ptr);
    Map correct_declaration_map = {{"with", "assign"}};
    SelectedSynonymTuple correct_synonym_tuple = {"with.stmt#"};
    for (int i = 0; i < correct_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Attr-ref as synonym with repeated terminal names") {
    std::string query = "assign pattern; Select    pattern  . stmt# pattern pattern(_,_)";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_syntax_ptr_list = {};
    SyntaxPair pattern_syntax_pair = CreateCorrectSyntaxPairParser("pattern", "_", "_");
    std::shared_ptr<ClauseSyntax> pattern_syntax_ptr = std::make_shared<PatternClauseSyntax>(pattern_syntax_pair);
    correct_syntax_ptr_list.push_back(pattern_syntax_ptr);
    Map correct_declaration_map = {{"pattern", "assign"}};
    SelectedSynonymTuple correct_synonym_tuple = {"pattern.stmt#"};
    for (int i = 0; i < correct_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Valid_MultipleSyn_WithSpaces") {
    std::string query("assign a; while w; if if, if1;variable v; Select <  a  .  stmt#   , w  .  stmt#   , "
                      "if  .  stmt#     , if1  .  stmt#      > such that Modifies(a,v)");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_syntax_ptr_list = {};
    SyntaxPair such_that_syntax_pair = CreateCorrectSyntaxPairParser("Modifies", "a", "v");
    std::shared_ptr<ClauseSyntax> such_that_syntax_ptr = std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    Map correct_declaration_map = {{"a", "assign"}, {"w", "while"}, {"if", "if"},
                                   {"if1", "if"}, {"v", "variable"}};
    SelectedSynonymTuple correct_synonym_tuple = {"a.stmt#", "w.stmt#", "if.stmt#", "if1.stmt#"};
    for (int i = 0; i < correct_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Attr-ref as synonym") {
    std::string query = "assign Select; Select Select  . stmt#";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    SelectedSynonymTuple correct_synonym_tuple = {"Select.stmt#"};
    REQUIRE(correct_synonym_tuple == synonym_tuple);

    query = "assign Select; Select Select.stmt#";
    parser_output = qp->ParseQuery(query);
    synonym_tuple = parser_output->GetSynonymTuple();
    correct_synonym_tuple = {"Select.stmt#"};
    REQUIRE(correct_synonym_tuple == synonym_tuple);
  }

  SECTION("Repeated terminal name") {
    std::string query = "if pattern; Select pattern such that Uses(5, \"i\")";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_syntax_ptr_list = {};
    SyntaxPair such_that_syntax_pair =
        CreateCorrectSyntaxPairParser("Uses", "5", "\"i\"");
    std::shared_ptr<ClauseSyntax> such_that_syntax_ptr =
        std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    Map correct_declaration_map = {{"pattern", "if"}};
    SelectedSynonymTuple correct_synonym_tuple = {"pattern"};
    for (int i = 0; i < correct_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Repeated terminal names -- one clause select with spaces") {
    std::string query = "assign pattern, Select; Select          pattern   such that         "
                        "Follows(           pattern,    Select             )";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_syntax_ptr_list = {};
    SyntaxPair such_that_syntax_pair =
        CreateCorrectSyntaxPairParser("Follows", "pattern", "Select");
    std::shared_ptr<ClauseSyntax> such_that_syntax_ptr =
        std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    Map correct_declaration_map = {{"pattern", "assign"}, {"Select", "assign"}};
    SelectedSynonymTuple correct_synonym_tuple = {"pattern"};
    for (int i = 0; i < correct_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
  }

  SECTION("Repeated terminal name -- basic SELECT") {
    std::string query = "assign Select; Select Select";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    SelectedSynonymTuple correct_synonym_tuple = {"Select"};
    REQUIRE(correct_synonym_tuple == synonym_tuple);
  }

  SECTION("Test valid query with basic BOOLEAN - no declarations") {
    std::string query("Select BOOLEAN");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_clause_syntax_ptr_list = {};
    Map correct_declaration_map = {};
    SelectedSynonymTuple correct_synonym_tuple = {};
    REQUIRE(correct_clause_syntax_ptr_list == clause_syntax_ptr_list);
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Valid_BOOLEAN with clause") {
    std::string query = "while w; assign a;Select BOOLEAN such that Parent* (w, a)";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_syntax_ptr_list = {};
    SyntaxPair such_that_syntax_pair =
        CreateCorrectSyntaxPairParser("Parent*", "w", "a");
    std::shared_ptr<ClauseSyntax> such_that_syntax_ptr =
        std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    Map correct_declaration_map = {{"a", "assign"}, {"w", "while"}};
    SelectedSynonymTuple correct_synonym_tuple = {};
    for (int i = 0; i < correct_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("repeated terminal names -- BOOLEAN") {
    std::string query = "assign BOOLEAN; Select BOOLEAN";
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_clause_syntax_ptr_list = {};
    Map correct_declaration_map = {{"BOOLEAN", "assign"}};
    SelectedSynonymTuple correct_synonym_tuple = {"BOOLEAN"};
    REQUIRE(correct_clause_syntax_ptr_list == clause_syntax_ptr_list);
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with a basic select statement in tuple") {
    std::string query("variable k; Select <k>");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_clause_syntax_ptr_list = {};
    Map correct_declaration_map = {{"k", "variable"}};
    SelectedSynonymTuple correct_synonym_tuple = {"k"};
    REQUIRE(correct_clause_syntax_ptr_list == clause_syntax_ptr_list);
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with a basic select statement") {
    std::string query("variable k; Select k");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_clause_syntax_ptr_list = {};
    Map correct_declaration_map = {{"k", "variable"}};
    SelectedSynonymTuple correct_synonym_tuple = {"k"};
    REQUIRE(correct_clause_syntax_ptr_list == clause_syntax_ptr_list);
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with a basic select BOOLEAN statement") {
    std::string query("variable k; Select BOOLEAN");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_clause_syntax_ptr_list = {};
    Map correct_declaration_map = {{"k", "variable"}};
    SelectedSynonymTuple correct_synonym_tuple = {};
    REQUIRE(correct_clause_syntax_ptr_list == clause_syntax_ptr_list);
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with a basic select tuple statement") {
    std::string query("variable v; assign a; Select <a,v>");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    ClauseSyntaxPtrList correct_syntax_ptr_list = {};
    Map correct_declaration_map = {{"v", "variable"}, {"a", "assign"}};
    SelectedSynonymTuple correct_synonym_tuple = {"a", "v"};
    for (int i = 0; i < correct_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }
    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with random spacing") {
    std::string query("assign a;\nSelect a such  that Uses(a, \"   count  \") pattern a(_,   _  \"  y     \" _)");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair pattern_syntax_pair =
        CreateCorrectSyntaxPairParser("a", "_", "_ \" y \" _");
    std::shared_ptr<ClauseSyntax> pattern_syntax_ptr =
        std::make_shared<PatternClauseSyntax>(pattern_syntax_pair);
    SyntaxPair such_that_syntax_pair =
        CreateCorrectSyntaxPairParser("Uses", "a", "\"count\"");
    std::shared_ptr<ClauseSyntax>
        such_that_syntax_ptr = std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    ClauseSyntaxPtrList correct_syntax_ptr_list;
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    correct_syntax_ptr_list.push_back(pattern_syntax_ptr);

    std::string s = clause_syntax_ptr_list[1]->GetSecondParameter();
    for (int i = 0; i < clause_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }

    Map correct_declaration_map = {{"a", "assign"}};
    SelectedSynonymTuple correct_synonym_tuple = {"a"};

    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with 1 pattern and 1 such that with random spacing") {
    std::string query("assign a;\nSelect   a pattern   a (  \"x\"   ,     _\"x\"_   )    "
                      "such that     Uses   (      a,  \"x\" )  ");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair pattern_syntax_pair =
        CreateCorrectSyntaxPairParser("a", "\"x\"", "_\"x\"_");
    std::shared_ptr<ClauseSyntax> pattern_syntax_ptr =
        std::make_shared<PatternClauseSyntax>(pattern_syntax_pair);
    SyntaxPair such_that_syntax_pair =
        CreateCorrectSyntaxPairParser("Uses", "a", "\"x\"");
    std::shared_ptr<ClauseSyntax> such_that_syntax_ptr =
        std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    ClauseSyntaxPtrList correct_syntax_ptr_list;
    correct_syntax_ptr_list.push_back(pattern_syntax_ptr);
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);

    for (int i = 0; i < clause_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }

    Map correct_declaration_map = {{"a", "assign"}};
    SelectedSynonymTuple correct_synonym_tuple = {"a"};

    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query with repeated terminal names") {
    std::string query
        ("    assign     pattern; variable      Select        ;\nSelect Select such that Uses(pattern, Select) "
         "pattern pattern(Select, _\"x\"_)");
    auto parser_output = qp->ParseQuery(query);
    auto synonym_tuple = parser_output->GetSynonymTuple();
    auto declaration_map = parser_output->GetDeclarationMap();
    auto clause_syntax_ptr_list = parser_output->GetClauseSyntaxPtrList();

    SyntaxPair pattern_syntax_pair =
        CreateCorrectSyntaxPairParser("pattern", "Select", "_\"x\"_");
    std::shared_ptr<ClauseSyntax> pattern_syntax_ptr =
        std::make_shared<PatternClauseSyntax>(pattern_syntax_pair);
    SyntaxPair such_that_syntax_pair =
        CreateCorrectSyntaxPairParser("Uses", "pattern", "Select");
    std::shared_ptr<ClauseSyntax>
        such_that_syntax_ptr = std::make_shared<SuchThatClauseSyntax>(such_that_syntax_pair);
    ClauseSyntaxPtrList correct_syntax_ptr_list;
    correct_syntax_ptr_list.push_back(such_that_syntax_ptr);
    correct_syntax_ptr_list.push_back(pattern_syntax_ptr);

    for (int i = 0; i < clause_syntax_ptr_list.size(); i++) {
      REQUIRE(clause_syntax_ptr_list[i]->Equals(*correct_syntax_ptr_list[i]));
    }

    Map correct_declaration_map = {{"pattern", "assign"}, {"Select", "variable"}};
    SelectedSynonymTuple correct_synonym_tuple = {"Select"};

    REQUIRE(correct_synonym_tuple == synonym_tuple);
    REQUIRE(declaration_map == correct_declaration_map);
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }

  SECTION("Test valid query - valid pattern expr") {
    std::string query("assign a; Select a pattern a(_, _)");
    REQUIRE_NOTHROW(qp->ParseQuery(query));
  }
}

TEST_CASE("Test invalid queries") {
  auto qp = std::make_shared<QueryParser>();

  SECTION("Test invalid attrRef as synonym queries") {
    // no full stop
    std::string query = "stmt s;Select s stmt# such that Follows(5,5)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // wrong character
    query = "stmt s;Select s,stmt# such that Follows(5,5)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid Boolean queries") {
    // Extra character at the end
    std::string query = "Select BOOLEAN <";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a; while w;SelectBOOLEAN such that Modifies (a, \"x\") and Parent* (w, a)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign Select; while BOOLEAN;SelectSelect such that Modifies(Select, \"x\") and Parent* "
            "(BOOLEAN, Select) pattern Select(_,_) with Select.stmt# = 5";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "Select <BOOLEAN>";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);

    // misspelling/wrong casing
    query = "Select BOOLEAn";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);

    // misspelling/wrong casing
    query = "Select BOOLEANs";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);

    // Extra character at the start
    query = "Select <BOOLEAN";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "Select ;BOOLEAN";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "Select a BOOLEAN";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "Select pattern BOOLEAN";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid Multiple Syn Select Synonym Tuple") {
    // Extra closing bracket
    std::string query = "assign a;variable v;Select <a,v>> such that Parent* (w, a) pattern a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // No comma
    query = "assign a;variable v;while w;Select < a v w > such that Parent* (w, a) pattern a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // No opening bracket
    query = "assign a;variable v;Select a,v > such that Parent* (w, a) pattern a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // No closing bracket
    query = "assign a;variable v;Select < a,v such that Parent* (w, a) pattern a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Extra comma
    query ="assign a;variable v;Select < a , , v > such that Parent* (w, a) pattern a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Extra opening bracket
    query = "assign a;variable v;Select < < a , v > such that Parent* (w, a) pattern a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Wrong placement of bracket
    query = "assign a;variable v;<Select a,v> such that Parent* (w, a) pattern a(\"x\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with invalid pattern") {
    std::string query("assign a;Select a such that Modifies(a,_) pattern a(,)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query ="assign a;Select a such that Modifies(a,\"count\") pattern ";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select a such that Modifies(a,\"count\") pattern a(,)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select a such that Modifies(a,\"count\") patterna(\"count\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select a pattern a(\"count   \", \"   1y       \")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // invalid pattern expr - throw syntax error
    query = "assign a; Select a such that Follows(a, _) pattern a(_, _\"\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // invalid pattern expr due to lack of syn assign - throw syntax error
    query = "stmt a; Select a pattern a(_, _\"x\"_)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
  }

  SECTION("Test invalid query with invalid such that") {
    std::string query("assign a;Select a suchthatModifies(a,\"count\") pattern a(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "variables v; Select a such that (1,";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query =  "assign a;Select a such that such that Modifies(a,\"count\") pattern a(\"count\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Extra chars
    query ="assign a;Select a such that Uses((a,\"count\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select assign such that Uses(a,\"count\"))";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select a such that Uses(a,\"count\"))";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select a such that a Uses(a,\"count\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select a such that pattern a(_, _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;Select a pattern a(_, _) such that ";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "variable v; Select a such that Follo(1,3)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // no IDENT as first arg
    query = "variable v; Select a such that Follow(\"anya\",3)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Extra arg
    query = "variable v; Select a such that Follow(\"anya\",3,4)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with 2 syntactically invalid subclauses") {
    std::string query("assign pattern;Select pattern such thatModifies(pattern,\"count\") "
                      "patternpattern(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with Select statement problems") {
    std::string query("assign a;");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a; Select";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a; SelectSelect";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query ="assign Select;Select such that Modifies(Select,\"count\") pattern Select(\"count\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;a such that Modifies(a,\"count\") pattern a(\"count\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "assign a;such that Select a such that Modifies(a,\"count\") pattern a(\"count\", _)";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with synonym problems") {
    // Missing syn
    std::string query("assign a;Select such that Modifies(a,\"count\") pattern a(\"count\", _)");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Invalid syn
    query ="assign 1a,b;Select 1a";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Invalid syn
    query ="assign a_,b;Select a_";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Invalid syn
    query ="assign 123;Select 123";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }

  SECTION("Test invalid query with declaration problems") {
    // extra semicolon
    std::string query("assign a;;Select a");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    query = "a assign a; variable v;\nSelect a";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // Missing syn
    query = "assign a; stmt; Select a";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // invalid design entity
    query = "statement s;Select s such that Parent*(s,\"count\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);

    // No comma
    query = "statement s s1;Select s such that Parent*(s,\"count\")";
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SyntaxErrorException);
  }


  SECTION("Test invalid query with no declarations") {
    std::string query("Select a");
    REQUIRE_THROWS_AS(qp->ParseQuery(query), SemanticErrorException);
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
}

TEST_CASE("Test remove duplicate clauses") {
  auto qp = std::make_shared<QueryParser>();

  SECTION("Remove duplicates 1") {
    std::string query = "stmt s1, s2;Select s1 such that Follows(s1,s2) "
                        "and Follows(s1,s2) and Follows(s1,s2) and Follows(s1,s2) ";
    auto parser_output = qp->ParseQuery(query);
    REQUIRE(parser_output->GetClauseSyntaxPtrList().size() == 1);
  }

  SECTION("Remove duplicates 2") {
    std::string query = "stmt s;Select s such that Next(_, _) and Next(_, _) and "
                        "Next(_, _) and Next*(s, s) and Next*(s, s) and "
                        "Next(_, _) and Next(_, _) and Affects(_, _) and Affects(_, _) and Affects(_, _)";
    auto parser_output = qp->ParseQuery(query);
    REQUIRE(parser_output->GetClauseSyntaxPtrList().size() == 3);
  }

  SECTION("Remove duplicates 3") {
    std::string query = "stmt s;Select s such that Affects(s, _) and Affects(s, _) "
                        "and Affects(s, s) and Affects(s, s) and Affects(1, s) and Affects(1, s) "
                        "and Affects*(s, s) and Affects*(s, s) and Affects*(s, s)";
    auto parser_output = qp->ParseQuery(query);
    REQUIRE(parser_output->GetClauseSyntaxPtrList().size() == 4);
  }

  SECTION("Remove duplicates 4") {
    std::string query("assign a, a1, a2, a3; stmt s1, s2, s3; variable v1, v2; Select <s1, a, a1, v2> "
                      "pattern a1(v1,_) pattern a1(v1,_) pattern a1(v1,_)"
                      "such that Modifies (s3, \"x\") and Follows (s1, s2) and Modifies (s3, \"x\")"
                      "with s3.stmt#=5 such that Uses (s2, v1) and Uses (s2, v1)");
    auto parser_output = qp->ParseQuery(query);
    REQUIRE(parser_output->GetClauseSyntaxPtrList().size() == 5);
  }
}
