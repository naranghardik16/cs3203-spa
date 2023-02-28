#pragma once
#include "QPS/QpsTokenizer.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "catch.hpp"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "QPS/Clause/PatternClauseSyntax.h"
#include "QPS/Clause/WithClauseSyntax.h"

auto tokenizer = std::make_shared<QpsTokenizer>();

SyntaxPair CreateCorrectSyntaxPair(std::string entity, std::string first_parameter, std::string second_parameter) {
  ParameterVector parameter_vector = {first_parameter, second_parameter};
  SyntaxPair syntax;
  syntax.first = entity;
  syntax.second = parameter_vector;
  return syntax;
}

SyntaxPair CreateCorrectThreeArgSyntaxPair(std::string entity, std::string first_parameter, std::string second_parameter, std::string third_parameter) {
  ParameterVector parameter_vector = {first_parameter, second_parameter, third_parameter};
  SyntaxPair syntax;
  syntax.first = entity;
  syntax.second = parameter_vector;
  return syntax;
}

TEST_CASE("Check if ParseSubclauses works with Multi-clauses") {
  SECTION("Valid Query: And + With clauses + repeated terminal names") {
    std::string statement = "pattern if(_,_,_) and Parent(_,_,_) and Parent(_,_) with if.stmt#=a.stmt# and 6 = 5 such that Parent(w,if)";
    SyntaxPair correct_if_syntax = CreateCorrectThreeArgSyntaxPair("if", "_", "_", "_");
    SyntaxPair correct_parentT_syntax = CreateCorrectThreeArgSyntaxPair("Parent", "_", "_", "_");
    SyntaxPair correct_parent_syntax = CreateCorrectSyntaxPair("Parent", "_", "_");
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "if.stmt#", "a.stmt#");
    SyntaxPair correct_with2_syntax = CreateCorrectSyntaxPair("", "6", "5");
    SyntaxPair correct_parent2_syntax = CreateCorrectSyntaxPair("Parent", "w", "if");
    std::shared_ptr<ClauseSyntax>
        pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_if_syntax);
    std::shared_ptr<ClauseSyntax>
        parentT_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_parentT_syntax);
    std::shared_ptr<ClauseSyntax>
        parent_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_parent_syntax);
    std::shared_ptr<ClauseSyntax>
        with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::shared_ptr<ClauseSyntax>
        with2_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with2_syntax);
    std::shared_ptr<ClauseSyntax>
        parent2_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parent2_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>>
        correct_vector = {pattern_clause_ptr, parentT_clause_ptr, parent_clause_ptr, with_clause_ptr, with2_clause_ptr, parent2_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);

    for (int i = 0; i < correct_vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("Valid Query: And + With clauses") {
    std::string statement = "such that Parent* (w, a) and Modifies (60, s) pattern a(\"x\", _) with a.stmt# = s.stmt#";
    SyntaxPair correct_parent_syntax = CreateCorrectSyntaxPair("Parent*", "w", "a");
    SyntaxPair correct_next_syntax = CreateCorrectSyntaxPair("Modifies", "60", "s");
    SyntaxPair correct_pattern_syntax = CreateCorrectSyntaxPair("a", "\"x\"", "_");
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "a.stmt#", "s.stmt#");
    std::shared_ptr<ClauseSyntax>
        parent_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parent_syntax);
    std::shared_ptr<ClauseSyntax>
        next_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_next_syntax);
    std::shared_ptr<ClauseSyntax>
        pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::shared_ptr<ClauseSyntax>
        with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>>
        correct_vector = {parent_clause_ptr, next_clause_ptr, pattern_clause_ptr, with_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);

    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("Valid Query: And + With clauses + random spacing") {
    std::string statement = "such           that     Parent*    (w,      c) and Parent    (w,      c) with       c.procName =   p.procName and 6 = 5";
    SyntaxPair correct_parentT_syntax = CreateCorrectSyntaxPair("Parent*", "w", "c");
    SyntaxPair correct_parent_syntax = CreateCorrectSyntaxPair("Parent", "w", "c");
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "c.procName", "p.procName");
    SyntaxPair correct_with2_syntax = CreateCorrectSyntaxPair("", "6", "5");
    std::shared_ptr<ClauseSyntax>
        parentT_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parentT_syntax);
    std::shared_ptr<ClauseSyntax>
        parent_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_parent_syntax);
    std::shared_ptr<ClauseSyntax>
        with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::shared_ptr<ClauseSyntax>
        with2_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with2_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>>
        correct_vector = {parentT_clause_ptr, parent_clause_ptr, with_clause_ptr, with2_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);

    for (int i = 0; i < correct_vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

}

TEST_CASE("Check if ParseSubclauses work for With clause") {
  SECTION ("INT = INT") {
    std::string statement = "with 6=5" ;
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "6", "5");
    std::shared_ptr<ClauseSyntax> with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {with_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION ("IDENT = IDENT") {
    std::string statement = "with \"x\"=\"y\"";
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "\"x\"", "\"y\"");
    std::shared_ptr<ClauseSyntax> with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {with_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION ("ATTRREF = ATTRREF") {
    std::string statement = "with     c.    procName =      p.procName";
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "c.procName", "p.procName");
    std::shared_ptr<ClauseSyntax> with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {with_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION ("ATTRREF = IDENT") {
    std::string statement = "with c.procName    =     \" x   \"" ;
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "c.procName", "\"x\"");
    std::shared_ptr<ClauseSyntax> with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {with_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION ("ATTRREF = INT") {
    std::string statement = "with s.stmt#=5" ;
    SyntaxPair correct_with_syntax = CreateCorrectSyntaxPair("", "s.stmt#", "5");
    std::shared_ptr<ClauseSyntax> with_clause_ptr = std::make_shared<WithClauseSyntax>(correct_with_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {with_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }
}

TEST_CASE("Check if ParseSubclauses work for If pattern clause") {

  SECTION("random spacing") {
    std::string statement = "               pattern ifs      (   v  ,_  ,_    )     " ;
    SyntaxPair correct_pattern_syntax = CreateCorrectThreeArgSyntaxPair("ifs", "v", "_", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};
    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("All wildcard") {
    std::string statement = "pattern ifs(_,_,_)";
    SyntaxPair correct_pattern_syntax = CreateCorrectThreeArgSyntaxPair("ifs", "_", "_", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("first arg is ident") {
    std::string statement = "pattern ifs(\"x\",_,_)" ;
    SyntaxPair correct_pattern_syntax = CreateCorrectThreeArgSyntaxPair("ifs", "\"x\"", "_", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("first arg is syn") {
    std::string statement = "pattern ifs (v,_ ,_)" ;
    SyntaxPair correct_pattern_syntax = CreateCorrectThreeArgSyntaxPair("ifs", "v", "_", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }
}

TEST_CASE("Check if ParseSubclauses work for While pattern clause") {
  SECTION("All wildcard") {
    std::string statement = "pattern w(_,_)";
    SyntaxPair correct_pattern_syntax = CreateCorrectSyntaxPair("w", "_", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("first arg is ident") {
    std::string statement = "pattern w(\"x\",_)" ;
    SyntaxPair correct_pattern_syntax = CreateCorrectSyntaxPair("w", "\"x\"", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("first arg is syn") {
    std::string statement = "pattern w(v,_)" ;
    SyntaxPair correct_pattern_syntax = CreateCorrectSyntaxPair("w", "v", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("random spacing") {
    std::string statement = "               pattern w      (   v  ,_  ,_    )     " ;
    SyntaxPair correct_pattern_syntax = CreateCorrectSyntaxPair("w", "v", "_");
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

}


TEST_CASE("Check if ParseSubClauses works as expected") {
  SECTION("Test if ParseSubClauses works on repeated terminal names with keyword pattern_ReturnList") {
    std::string statement = "such that Parent* (  w  ,pattern) pattern pattern    (\"count\",   _   )  ";

    //we trim before searching for keywords so the returned string will be a trimmed version
    SyntaxPair correct_such_that_syntax = CreateCorrectSyntaxPair("Parent*", "w", "pattern");
    SyntaxPair correct_pattern_syntax = CreateCorrectSyntaxPair("pattern", "\"count\"", "_");
    std::shared_ptr<ClauseSyntax>
        such_that_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_such_that_syntax);
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {such_that_clause_ptr, pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("Test if ParseSubClauses can handle terminal names being synonyms_ReturnList") {
    std::string statement = "such     that       Parent*        (pattern,   such)   pattern   such (\"count\", _) ";
    SyntaxPair correct_such_that_syntax = CreateCorrectSyntaxPair("Parent*", "pattern", "such");
    SyntaxPair correct_pattern_syntax = CreateCorrectSyntaxPair("such", "\"count\"", "_");
    std::shared_ptr<ClauseSyntax>
        such_that_clause_ptr = std::make_shared<SuchThatClauseSyntax>(correct_such_that_syntax);
    std::shared_ptr<ClauseSyntax> pattern_clause_ptr = std::make_shared<PatternClauseSyntax>(correct_pattern_syntax);
    std::vector<std::shared_ptr<ClauseSyntax>> correct_vector = {such_that_clause_ptr, pattern_clause_ptr};

    auto vector = tokenizer->ParseSubClauses(statement);
    for (int i = 0; i < vector.size(); i++) {
      REQUIRE(vector[i]->Equals(*correct_vector[i]));
    }
  }

  SECTION("Test if ParseSubClauses can handle invalid relationship reference_ThrowSyntaxErrorException") {
    try {
      std::string statement = "such     that       Parent  *        (pattern,   such)   pattern   such (\"count\", _) ";
      auto vector = tokenizer->ParseSubClauses(statement);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }
}


TEST_CASE("Check if ExtractAbstractSyntaxFromWithClause works as expected") {
  SECTION("Test on With_Clause_AttrRef_Int") {
    std::string clause = "s1.stmt#=10";
    SyntaxPair correct_syntax = CreateCorrectSyntaxPair("", "s1.stmt#", "10");
    SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromWithClause(clause);

    REQUIRE(correct_syntax == syntax);
  }
}

TEST_CASE("Check if ExtractAbstractSyntaxFromClause works as expected") {
  SECTION("Test on Pattern Clause_ReturnSyntaxPair") {
    std::string clause = "a (\"count\", _)";
    SyntaxPair correct_syntax = CreateCorrectSyntaxPair("a", "\"count\"", "_");
    SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause);

    REQUIRE(correct_syntax == syntax);
  }

  SECTION("Test on Such That Clause_ReturnSyntaxPair") {
    std::string clause = "Uses (a, v)";
    SyntaxPair correct_syntax = CreateCorrectSyntaxPair("Uses", "a", "v");
    SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause);
    REQUIRE(correct_syntax == syntax);
  }

  SECTION("Test on clause with extra brackets_ReturnSyntaxPair") {
    std::string clause = "a (\"(count)\", _)";
    SyntaxPair correct_syntax = CreateCorrectSyntaxPair("a", "\"(count)\"", "_");
    SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause);
    REQUIRE(correct_syntax == syntax);
  }

  SECTION("Test on empty clause_ThrowSyntaxErrorException") {
    std::string clause = "";
    try {
      SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(true);
    }
  }

  SECTION("Test on invalid clause with extra characters_ThrowSyntaxErrorException") {
    std::string clause ="Uses (a, v) a";
    try {
      SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(true);
    }
  }

  SECTION("Test on invalid pattern clause with invalid concrete syntax_ThrowSyntaxErrorException") {
    std::string invalid_pattern_clause = "a (\"count\" _)"; //invalid clause without comma
    try {
         auto pair  = tokenizer->ExtractAbstractSyntaxFromClause(invalid_pattern_clause);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }

  SECTION("Test on invalid such that clause with invalid concrete syntax_ThrowSyntaxErrorException") {
    std::string invalid_such_that_clause = "a, v)"; //invalid clause without (
    try {
      auto pair = tokenizer->ExtractAbstractSyntaxFromClause(invalid_such_that_clause);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }


  SECTION("Test on clause with missing abstract syntax_ThrowSyntaxErrorException") {
    std::string invalid_such_that_clause = "(,)"; //checks will be done by validator to throw exception
    try {
      auto pair = tokenizer->ExtractAbstractSyntaxFromClause(invalid_such_that_clause);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }
}

//Split declaration statements from Select Statement
TEST_CASE("Check if SplitQuery works") {
  SECTION("ValidCases_ReturnPair") {
    std::vector<std::string> queries = {"variable v, v1;procedure p, p1;\nSelect v",
                                        "  assign a  ; while w; \n  Select a such that Parent* (w, a) pattern a (\"count\", _)"};
    std::vector<std::vector<std::string>>
        correct_declaration_clauses{{"variable v, v1", "procedure p, p1"}, {"assign a", "while w"}};
    std::vector<std::string>
        correct_select_statements = {"Select v", "Select a such that Parent* (w, a) pattern a (\"count\", _)"};

    for (int i = 0; i < queries.size(); i++) {
      std::string query = queries[i];
      auto correct_clauses = correct_declaration_clauses[i];
      std::string correct_select_statement = correct_select_statements[i];

      auto declaration_select_pair = tokenizer->SplitQuery(query);
      std::vector<std::string> declaration_statements = declaration_select_pair.first;
      std::string select_statement = declaration_select_pair.second;
      REQUIRE(correct_clauses == declaration_statements);
      REQUIRE(correct_select_statement == select_statement);
    }
  }

  SECTION("InvalidDeclaration_ThrowSyntaxErrorException") {
    std::vector<std::string> invalid_queries = {"variable v;", "Select v", "variable v Select v", "variable v, v1;    such that"};
    for (auto invalid_query : invalid_queries) {
      try {
        auto declaration_select_pair = tokenizer->SplitQuery(invalid_query);
      } catch (const SyntaxErrorException e) {
        REQUIRE(true);
      }
    }
  }
}

TEST_CASE("Test if ParseSynonym works") {
  Map declaration{{"a", "assign"}, {"v" , "variable"}, {"proc", "procedure"},
                  {"r", "read"}, {"p", "print"}, {"ca", "call"}, {"i", "if"},
                  {"w", "while"}, {"c", "constant"}, {"s", "stmt"}};

  SECTION("SpaceInAttrRef_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "a.   stmt# such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("InvalidSynonym_ThrowsSyntaxErrorException") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "     1a      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_THROWS_AS(tk->ParseSynonym(select_keyword_removed_query, map), SyntaxErrorException);
  }

  SECTION("InvalidAttrNameInRef_ThrowsSyntaxErrorException") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "r.varname      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_THROWS_AS(tk->ParseSynonym(select_keyword_removed_query, map), SyntaxErrorException);
  }

  SECTION("InvalidSynInRef_ThrowsSyntaxErrorException") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "1r.varName      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_THROWS_AS(tk->ParseSynonym(select_keyword_removed_query, map), SyntaxErrorException);
  }

  SECTION("InvalidAttrRef_ThrowsSyntaxErrorException") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "r.varName.varName      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_THROWS_AS(tk->ParseSynonym(select_keyword_removed_query, map), SyntaxErrorException);
  }

  SECTION("BOOLEANInTupleNotDeclared_HasSemanticError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<BOOLEAN>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("InvalidAttrForSyn_HasSemanticError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<c.varName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("BOOLEANNotInTuple_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "BOOLEAN      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("NoCloseBracket_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<r.varName      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_THROWS_AS(tk->ParseSynonym(select_keyword_removed_query, map), SyntaxErrorException);
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("read.varName_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<r.varName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("read.stmt#_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<r.stmt#> such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("print.varName_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<p.varName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("print.stmt#_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<p.stmt#> such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("procedure.procName_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<proc.procName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("variable.varName_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<v.varName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("constant.value_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<c.value>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("statement.stmt#_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<s.stmt#>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("while.stmt#_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<w.stmt#>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("if.stmt#_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<i.stmt#>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("call.stmt#_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<ca.stmt#>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("call.procName_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<ca.procName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("assign.stmt#_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<a.stmt#>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("MultipleAttrRef_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<a.stmt#,c.value,ca.procName,r.varName,p.varName,v.varName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }

  SECTION("SpaceInAttrRef_NoError") {
    auto tk = std::make_shared<QpsTokenizer>();
    tk->semantic_validator_->declaration_ = declaration;
    Map map = {};
    std::string select_keyword_removed_query = "<a.   stmt#,c   .value,     ca   .   procName>      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_NOTHROW(tk->ParseSynonym(select_keyword_removed_query, map));
    REQUIRE_FALSE(tk->semantic_validator_->has_semantic_error_);
  }
}

TEST_CASE("Check if FindIndexesOfClauseStart works as expected") {
  SECTION("ValidSuchThatMatch_ReturnIndex") {
    std::string query_substr = "pattern a (\"such that \", _) such that parent* (w, pattern )";
    auto index = tokenizer->FindStartOfSubClauseStart(query_substr, pql_constants::kSuchThatRegex);
    REQUIRE(index == 28);
  }

  SECTION("ValidPatternMatch_ReturnIndex") {
    std::string query_substr = "such that parent* (w, pattern ) pattern a (\"count\", _)";
    auto index = tokenizer->FindStartOfSubClauseStart(query_substr, pql_constants::kPatternRegex);
    REQUIRE(index == 32);
  }

  SECTION("CannotFindMatch_ReturnNPOS") {
    std::string query_substr = "pattern a (\"count\", _)";
    auto index = tokenizer->FindStartOfSubClauseStart(query_substr, pql_constants::kSuchThatRegex);
    REQUIRE(index == std::string::npos);
  }
}

TEST_CASE("Check if GetIndexListOfClauses works as expected") {
  SECTION("ValidCase_ReturnSortedVectorOfSizeT") {
    std::string query_substr = "pattern a (\"such that \", _) such that parent* (w, pattern )";
    auto index = tokenizer->GetIndexListOfClauses(query_substr);
    std::vector<size_t> correct_vector = {0,28};
    REQUIRE(index == correct_vector);
  }

  SECTION("InvalidCase_ReturnEmptyVector") {
    std::string query_substr = "patterna(\"such that \",_) such that parent* (w, pattern )";
    REQUIRE_THROWS_AS(tokenizer->GetIndexListOfClauses(query_substr), SyntaxErrorException);
  }
}

//Check if design entities and corresponding synonyms can be extracted from declarations
TEST_CASE("Check if ExtractAbstractSyntaxFromDeclaration works as expected") {
  SECTION("Test simple case of one design entity and one synonym_ReturnMap") {
    std::vector<std::string> declarations{"variable v"};
    std::unordered_map<std::string, std::string> correct_synonym_to_design_entity_map = {{"v", "variable"}};

    std::unordered_map<std::string, std::string> map = tokenizer->ExtractAbstractSyntaxFromDeclarations(declarations);

    REQUIRE(map == correct_synonym_to_design_entity_map);
  }

  SECTION("Test if exception is thrown for one invalid design entity and one synonym_ThrowSyntaxErrorException") {
    std::vector<std::string> declarations{"variablexyz v"};

    try {
      std::unordered_map<std::string, std::string> map = tokenizer->ExtractAbstractSyntaxFromDeclarations(declarations);
    } catch (SyntaxErrorException e) {
      REQUIRE(1);
    }
  }

  SECTION("Test if exception is thrown for invalid synonym_ThrowSyntaxErrorException") {
    std::vector<std::string> declarations{"variable 1v"};
    try {
      std::unordered_map<std::string, std::string> map = tokenizer->ExtractAbstractSyntaxFromDeclarations(declarations);
    } catch (SyntaxErrorException e) {
      REQUIRE(1);
    }
  }

  SECTION("Test if exception is thrown for missing comma_ThrowSyntaxErrorException") {
    std::vector<std::string> declarations{"procedure  p1  , such that ,  p3"};
    try {
      std::unordered_map<std::string, std::string> map = tokenizer->ExtractAbstractSyntaxFromDeclarations(declarations);
    } catch (SyntaxErrorException e) {
      REQUIRE(1);
    }
  }

  SECTION("Test case of repeated synonyms_ThrowSemanticErrorException") {
    std::vector<std::string> declarations{"variable v,v"};
    try {
      std::unordered_map<std::string, std::string> map = tokenizer->ExtractAbstractSyntaxFromDeclarations(declarations);
    } catch (const SemanticErrorException &rse) {
      REQUIRE(1);
    }
  }

  SECTION("Test case of one design entity and multiple synonyms with random spaces in between_ReturnMap") {
    std::vector<std::string> declarations{"procedure  p1  ,    p2   ,  p3"};
    std::unordered_map<std::string, std::string> correct_synonym_to_design_entity_map = {{"p1", "procedure"},
                                                                                         {"p2", "procedure"},
                                                                                         {"p3", "procedure"}};

    std::unordered_map<std::string, std::string> map = tokenizer->ExtractAbstractSyntaxFromDeclarations(declarations);
    REQUIRE(map == correct_synonym_to_design_entity_map);
  }

  SECTION("Test case of multiple design entity and multiple synonyms with random spacing_ReturnMap") {
    std::vector<std::string> declarations{"variable v,v1,v2", "procedure  p1  ,    p2   ,   p3  "};
    std::unordered_map<std::string, std::string> correct_synonym_to_design_entity_map = {{"v", "variable"},
                                                                                         {"v1", "variable"},
                                                                                         {"v2", "variable"},
                                                                                         {"p1", "procedure"},
                                                                                         {"p2", "procedure"},
                                                                                         {"p3", "procedure"}};
    std::unordered_map<std::string, std::string> map = tokenizer->ExtractAbstractSyntaxFromDeclarations(declarations);
    REQUIRE(map == correct_synonym_to_design_entity_map);
  }
}


