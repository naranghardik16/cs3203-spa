#include "catch.hpp"
#include "QPS/AbstractSyntaxExtractor.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "QPS/PQLConstants.h"

auto extractor = std::shared_ptr<AbstractSyntaxExtractor>();

//Check if design entities and corresponding synonyms can be extracted from declarations
TEST_CASE("Check if ExtractAbstractSyntaxFromDeclaration works as expected") {
  SECTION("Test simple case of one design entity and one synonym") {
    std::vector<std::string> declarations{"variable v"};
    std::unordered_map<std::string, std::string> correct_synonym_to_design_entity_map = {{"v", "variable"}};

    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromDeclarations(declarations);

    REQUIRE(map == correct_synonym_to_design_entity_map);
  }

  SECTION("Test if exception is thrown for one invalid design entity and one synonym") {
    std::vector<std::string> declarations{"variablexyz v"};

    try {
    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromDeclarations(declarations);
    } catch (SyntaxErrorException e) {
      REQUIRE(1);
    }
  }

  SECTION("Test if exception is thrown for invalid synonym") {
    std::vector<std::string> declarations{"variable 1v"};
    try {
      std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromDeclarations(declarations);
    } catch (SyntaxErrorException e) {
      REQUIRE(1);
    }
  }

  SECTION("Test case of one design entity and multiple synonyms with random spaces in between") {
    std::vector<std::string> declarations{"procedure  p1  ,    p2   ,   p3  "};
    std::unordered_map<std::string, std::string> correct_synonym_to_design_entity_map = {{"p1", "procedure"},
                                                                                         {"p2", "procedure"},
                                                                                         {"p3", "procedure"}};

    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromDeclarations(declarations);
    REQUIRE(map == correct_synonym_to_design_entity_map);
  }

  SECTION("Test case of multiple design entity and multiple synonyms with random spacing") {
    std::vector<std::string> declarations{"variable v,v1,v2", "procedure  p1  ,    p2   ,   p3  "};
    std::unordered_map<std::string, std::string> correct_synonym_to_design_entity_map = {{"v", "variable"},
                                                                                         {"v1", "variable"},
                                                                                         {"v2", "variable"},
                                                                                         {"p1", "procedure"},
                                                                                         {"p2", "procedure"},
                                                                                         {"p3", "procedure"}};
    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromDeclarations(declarations);
    REQUIRE(map == correct_synonym_to_design_entity_map);
  }

  SECTION("Test case of repeated synonyms") {
    std::vector<std::string> declarations{"variable v,v"};
    try {
      std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromDeclarations(declarations);
    } catch (const SemanticErrorException& rse) {
      REQUIRE(1);
    }
  }
}

TEST_CASE("Check if ExtractAbstractSyntaxFromClause works as expected") {
  SECTION("Test on Such That Clause") {
    std::string clause = "such that Uses (a, v)";
    std::unordered_map<std::string, std::string> correct_map = {{pql_constants::kEntityKey, "Uses"},
                                                                                         {pql_constants::kFirstParameterKey, "a"},
                                                                                         {pql_constants::kSecondParameterKey, "v"}};

    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromClause(clause, pql_constants::kSuchThatStartIndicator);

    REQUIRE(map == correct_map);
  }

  SECTION("Test on Pattern Clause") {
    std::string clause = "pattern a (\"count\", _)";
    std::unordered_map<std::string, std::string> correct_map = {{pql_constants::kEntityKey, "a"},
                                                                {pql_constants::kFirstParameterKey, "\"count\""},
                                                                {pql_constants::kSecondParameterKey, "_"}};

    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromClause(clause, pql_constants::kPatternStartIndicator);

    REQUIRE(map == correct_map);
  }

  SECTION("Test on empty Clause") {
    std::string clause = "";
    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromClause(clause, pql_constants::kPatternStartIndicator);
    REQUIRE(map.empty());
  }

  SECTION("Test on invalid pattern clause with invalid concrete syntax") {
    std::string invalid_pattern_clause = "pattern a (\"count\" _)"; //invalid clause without comma
    try {
      std::unordered_map<std::string, std::string>
          map = extractor->ExtractAbstractSyntaxFromClause(invalid_pattern_clause, pql_constants::kPatternStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }

  SECTION("Test on invalid such that clause with invalid concrete syntax") {
    std::string invalid_such_that_clause = "such that a, v)"; //invalid clause without (
    try {
      std::unordered_map<std::string, std::string>
          map = extractor->ExtractAbstractSyntaxFromClause(invalid_such_that_clause, pql_constants::kSuchThatStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }


  SECTION("Test on clause with missing abstract syntax") {
    std::string invalid_such_that_clause = "such that (,)"; //checks will be done by validator to throw exception
    try {
      std::unordered_map<std::string, std::string>
          map = extractor->ExtractAbstractSyntaxFromClause(invalid_such_that_clause, pql_constants::kSuchThatStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }
}