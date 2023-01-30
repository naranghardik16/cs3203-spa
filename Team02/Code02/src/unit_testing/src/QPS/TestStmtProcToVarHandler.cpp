#include "catch.hpp"

#include "QPS/ValidationHandler/StmtProcToVarHandler.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

const std::string kEntityKey = "Entity";
const std::string kAssignEntity = "assign";
const std::string kVariableEntity = "variable";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

TEST_CASE("Test StmtProcToVarHandler") {
  StmtProcToVarHandler handler;

  SECTION("Test valid clause") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "v"}};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }

  SECTION("Test valid clause, arg_2 is underscore") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "_"}};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }

  SECTION("Test invalid clause, arg_1 is underscore") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "_"},
               {kSecondParameterKey, "_"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_1 is not stmtRef/entRef") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "1b"},
               {kSecondParameterKey, "v"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_2 is not entRef") {
    Map declaration{{"a", "assign"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "1"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause, arg_1 is not invalid design entity") {
    Map declaration{{"a", "constant"},
                    {"v", "variable"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "v"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause, arg_2 is not invalid design entity") {
    Map declaration{{"a", "constant"},
                    {"v", "stmt"}};

    Map clause{{kEntityKey, "Uses"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "v"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }
}
