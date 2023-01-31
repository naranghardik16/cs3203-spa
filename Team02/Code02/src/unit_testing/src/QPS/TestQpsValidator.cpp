#include "catch.hpp"

#include "QPS/QpsValidator.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

const std::string kEntityKey = "Entity";
const std::string kAssignEntity = "assign";
const std::string kVariableEntity = "variable";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

TEST_CASE("Test QpsValidator") {
  SECTION("Test valid query 1") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map such_that_clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "v"}};

    Map pattern_clause{{kEntityKey, "a"},
               {kFirstParameterKey, "v"},
               {kSecondParameterKey, "_\"v\"_"}};

    REQUIRE_NOTHROW(QpsValidator::Validate(declaration, such_that_clause, pattern_clause));
  }

  SECTION("Test valid query 2") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map such_that_clause{{kEntityKey, "Follows"},
                         {kFirstParameterKey, "a"},
                         {kSecondParameterKey, "1"}};

    Map pattern_clause{{kEntityKey, "a"},
                       {kFirstParameterKey, "v"},
                       {kSecondParameterKey, "_\"v\"_"}};

    REQUIRE_NOTHROW(QpsValidator::Validate(declaration, such_that_clause, pattern_clause));
  }

  SECTION("Test invalid query - invalid relationship") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map such_that_clause{{kEntityKey, "Followx"},
                         {kFirstParameterKey, "a"},
                         {kSecondParameterKey, "1"}};

    Map pattern_clause{{kEntityKey, "a"},
                       {kFirstParameterKey, "v"},
                       {kSecondParameterKey, "_\"v\"_"}};

    REQUIRE_THROWS_AS(QpsValidator::Validate(declaration, such_that_clause, pattern_clause), SyntaxErrorException);
  }

  SECTION("Test invalid query - invalid syn-assign") {
    Map declaration{{"a", "stmt"},
                    {"v", "variable"}};

    Map such_that_clause{{kEntityKey, "Follows"},
                         {kFirstParameterKey, "a"},
                         {kSecondParameterKey, "1"}};

    Map pattern_clause{{kEntityKey, "a"},
                       {kFirstParameterKey, "v"},
                       {kSecondParameterKey, "_\"v\"_"}};

    REQUIRE_THROWS_AS(QpsValidator::Validate(declaration, such_that_clause, pattern_clause), SemanticErrorException);
  }

  SECTION("Test invalid query - synonym not declared") {
    Map declaration{{"a", "stmt"},
                    {"v", "variable"}};

    Map such_that_clause{{kEntityKey, "Follows"},
                         {kFirstParameterKey, "p"},
                         {kSecondParameterKey, "1"}};

    Map pattern_clause{{kEntityKey, "a"},
                       {kFirstParameterKey, "v"},
                       {kSecondParameterKey, "_\"v\"_"}};

    REQUIRE_THROWS_AS(QpsValidator::Validate(declaration, such_that_clause, pattern_clause), SemanticErrorException);
  }
}