#include "catch.hpp"
#include "QPS/AbstractSyntaxExtractor.h"
#include "QPS/PqlException/SemanticErrorException.h"
#include "QPS/PqlException/SyntaxErrorException.h"

auto extractor = std::shared_ptr<AbstractSyntaxExtractor>();
const std::string kSuchThatStartIndicator = "such that ";
const std::string kPatternStartIndicator = "pattern ";

const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

//Check if design entities and corresponding synonyms can be extracted from declarations
TEST_CASE("Check if ExtractAbstractSyntaxFromDeclaration works as expected") {
  SECTION("Test simple case of one design entity and one synonym") {
    std::vector<std::string> declarations{"variable v"};
    std::unordered_map<std::string, std::string> correct_synonym_to_design_entity_map = {{"v", "variable"}};

    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromDeclarations(declarations);
    REQUIRE(map == correct_synonym_to_design_entity_map);
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
    std::unordered_map<std::string, std::string> correct_map = {{kEntityKey, "Uses"},
                                                                                         {kFirstParameterKey, "a"},
                                                                                         {kSecondParameterKey, "v"}};

    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromClause(clause, kSuchThatStartIndicator);

    REQUIRE(map == correct_map);
  }

  SECTION("Test on Pattern Clause") {
    std::string clause = "pattern a (\"count\", _)";
    std::unordered_map<std::string, std::string> correct_map = {{kEntityKey, "a"},
                                                                {kFirstParameterKey, "\"count\""},
                                                                {kSecondParameterKey, "_"}};

    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromClause(clause, kPatternStartIndicator);

    REQUIRE(map == correct_map);
  }

  SECTION("Test on empty Clause") {
    std::string clause = "";
    std::unordered_map<std::string, std::string> map = extractor->ExtractAbstractSyntaxFromClause(clause, kPatternStartIndicator);
    REQUIRE(map.empty());
  }

  SECTION("Test on invalid pattern clause with invalid concrete syntax") {
    std::string invalid_pattern_clause = "pattern a (\"count\" _)"; //invalid clause without comma
    try {
      std::unordered_map<std::string, std::string>
          map = extractor->ExtractAbstractSyntaxFromClause(invalid_pattern_clause, kPatternStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }

  SECTION("Test on invalid such that clause with invalid concrete syntax") {
    std::string invalid_such_that_clause = "such that a, v)"; //invalid clause without (
    try {
      std::unordered_map<std::string, std::string>
          map = extractor->ExtractAbstractSyntaxFromClause(invalid_such_that_clause, kSuchThatStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }


  SECTION("Test on clause with missing abstract syntax") {
    std::string invalid_such_that_clause = "such that (,)"; //checks will be done by validator to throw exception
    try {
      std::unordered_map<std::string, std::string>
          map = extractor->ExtractAbstractSyntaxFromClause(invalid_such_that_clause, kSuchThatStartIndicator);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }
}