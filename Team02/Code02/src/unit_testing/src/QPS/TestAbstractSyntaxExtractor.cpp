#include "catch.hpp"
#include "QPS/AbstractSyntaxExtractor.h"
#include "QPS/PqlException/SemanticErrorException.h"

auto extractor = std::shared_ptr<AbstractSyntaxExtractor>();

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