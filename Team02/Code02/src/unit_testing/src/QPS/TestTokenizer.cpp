#pragma once
#include "QPS/QpsTokenizer.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "catch.hpp"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "QPS/Clause/PatternClauseSyntax.h"

auto tokenizer = std::make_shared<QpsTokenizer>();

SyntaxPair CreateCorrectSyntaxPair(std::string entity, std::string first_parameter, std::string second_parameter) {
  auto parameter_pair = std::pair<std::string, std::string>(first_parameter, second_parameter);
  SyntaxPair syntax;
  syntax.first = entity;
  syntax.second = parameter_pair;
  return syntax;
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

TEST_CASE("Check if ExtractAbstractSyntaxFromClause works as expected") {
  SECTION("Test on Pattern Clause_ReturnSyntaxPair") {
    std::string clause = "pattern a (\"count\", _)";
    SyntaxPair correct_syntax = CreateCorrectSyntaxPair("a", "\"count\"", "_");
    SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause, pql_constants::kPatternStartIndicator);
    REQUIRE(correct_syntax == syntax);
  }

  SECTION("Test on Such That Clause_ReturnSyntaxPair") {
    std::string clause = "such that Uses (a, v)";
    SyntaxPair correct_syntax = CreateCorrectSyntaxPair("Uses", "a", "v");
    SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause, pql_constants::kSuchThatStartIndicator);
    REQUIRE(correct_syntax == syntax);
  }

  SECTION("Test on clause with extra brackets_ReturnSyntaxPair") {
    std::string clause = "pattern a (\"(count)\", _)";
    SyntaxPair correct_syntax = CreateCorrectSyntaxPair("a", "\"(count)\"", "_");
    SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause, pql_constants::kPatternStartIndicator);
    REQUIRE(correct_syntax == syntax);
  }

  SECTION("Test on empty clause_ThrowSyntaxErrorException") {
    std::string clause = "";
    try {
      SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause, pql_constants::kSuchThatStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(true);
    }
  }

  SECTION("Test on invalid clause with extra characters_ThrowSyntaxErrorException") {
    std::string clause ="such that Uses (a, v) a";
    try {
      SyntaxPair syntax = tokenizer->ExtractAbstractSyntaxFromClause(clause, pql_constants::kSuchThatStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(true);
    }
  }

  SECTION("Test on invalid pattern clause with invalid concrete syntax_ThrowSyntaxErrorException") {
    std::string invalid_pattern_clause = "pattern a (\"count\" _)"; //invalid clause without comma
    try {
         auto pair  = tokenizer->ExtractAbstractSyntaxFromClause(invalid_pattern_clause, pql_constants::kPatternStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }

  SECTION("Test on invalid such that clause with invalid concrete syntax_ThrowSyntaxErrorException") {
    std::string invalid_such_that_clause = "such that a, v)"; //invalid clause without (
    try {
      auto pair = tokenizer->ExtractAbstractSyntaxFromClause(invalid_such_that_clause, pql_constants::kSuchThatStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }


  SECTION("Test on clause with missing abstract syntax_ThrowSyntaxErrorException") {
    std::string invalid_such_that_clause = "such that (,)"; //checks will be done by validator to throw exception
    try {
      auto pair = tokenizer->ExtractAbstractSyntaxFromClause(invalid_such_that_clause, pql_constants::kSuchThatStartIndicator);
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
  SECTION("Valid_MultipleSyn_WithSpaces") {
    std::string select_keyword_removed_query = "  < a     , w     , if      , if1       > such that Calls (\"Second\", \"Third\")";
    auto synonym_tuple = tokenizer->ParseSynonym(select_keyword_removed_query);
    SelectedSynonymTuple correct_tuple = {"a", "w", "if", "if1"};
    REQUIRE(synonym_tuple == correct_tuple);
  }

  SECTION("Valid_MultipleSyn") {
    std::string select_keyword_removed_query = "<a, w, if, if1> such that Calls (\"Second\", \"Third\")";
    auto synonym_tuple = tokenizer->ParseSynonym(select_keyword_removed_query);
    SelectedSynonymTuple correct_tuple = {"a", "w", "if", "if1"};
    REQUIRE(synonym_tuple == correct_tuple);
  }

  SECTION("Valid_BOOLEAN_Syn") {
    std::string select_keyword_removed_query = "BOOLEAN such that Parent* (w, a)";
    auto synonym_tuple = tokenizer->ParseSynonym(select_keyword_removed_query);
    REQUIRE(synonym_tuple.empty());
  }

  SECTION("ValidSynonym_ReturnString") {
    std::string select_keyword_removed_query = "Select such that Parent* (w, a) pattern a (\"count\", _)";
    auto synonym_tuple = tokenizer->ParseSynonym(select_keyword_removed_query);
    REQUIRE(synonym_tuple[0] == "Select");
  }

  SECTION("InvalidSynonym_ThrowsSyntaxErrorException") {
    std::string select_keyword_removed_query = "     1a      such  that   Parent* (w, a) pattern a (\"count\", _)";
    REQUIRE_THROWS_AS(tokenizer->ParseSynonym(select_keyword_removed_query), SyntaxErrorException);
  }
}

TEST_CASE("Check if FindStartOfSubClauseIndex works as expected") {
  SECTION("ValidSuchThatMatch_ReturnIndex") {
    std::string query_substr = "pattern a (\"such that \", _) such that parent* (w, pattern )";
    auto index = tokenizer->FindStartOfSubClauseIndex(query_substr, pql_constants::kSuchThatRegex);
    REQUIRE(index == 28);
  }

  SECTION("ValidPatternMatch_ReturnIndex") {
    std::string query_substr = "such that parent* (w, pattern ) pattern a (\"count\", _)";
    auto index = tokenizer->FindStartOfSubClauseIndex(query_substr, pql_constants::kPatternRegex);
    REQUIRE(index == 32);
  }

  SECTION("CannotFindMatch_ReturnNPOS") {
    std::string query_substr = "pattern a (\"count\", _)";
    auto index = tokenizer->FindStartOfSubClauseIndex(query_substr, pql_constants::kSuchThatRegex);
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


