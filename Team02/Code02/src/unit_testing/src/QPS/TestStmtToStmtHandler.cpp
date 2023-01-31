#include "catch.hpp"

#include "QPS/ValidationHandler/StmtToStmtHandler.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

const std::string kEntityKey = "Entity";
const std::string kAssignEntity = "assign";
const std::string kVariableEntity = "variable";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

TEST_CASE("Test StmtToStmtHandler") {
  StmtToStmtHandler handler;

  SECTION("Test valid clause - ref(assign, print)") {
    Map declaration{{"a", "assign"},
                    {"p", "print"}};

    Map clause{{kEntityKey, "Follows"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "p"}};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }

  SECTION("Test valid clause - ref(stmt, stmt)") {
    Map declaration{{"a", "stmt"},
                    {"p", "stmt"}};

    Map clause{{kEntityKey, "Follows"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "p"}};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }

  SECTION("Test invalid clause - invalid ref (no throw error)") {
    Map declaration{{"a", "stmt"},
                    {"p", "stmt"}};

    Map clause{{kEntityKey, "Followed"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "p"}};

    REQUIRE_NOTHROW(handler.Handle(declaration, clause));
  }

  SECTION("Test invalid clause - arg_1 not stmt ref") {
    Map declaration{{"a", "stmt"},
                    {"p", "stmt"}};

    Map clause{{kEntityKey, "Follows"},
               {kFirstParameterKey, "\"a\""},
               {kSecondParameterKey, "p"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause - arg_2 not stmt ref") {
    Map declaration{{"a", "stmt"},
                    {"p", "stmt"}};

    Map clause{{kEntityKey, "Follows"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "\"p\""}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause - arg_1 not stmt entity") {
    Map declaration{{"a", "variable"},
                    {"p", "stmt"}};

    Map clause{{kEntityKey, "Follows"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "p"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }

  SECTION("Test invalid clause - arg_2 not stmt entity") {
    Map declaration{{"a", "read"},
                    {"p", "variable"}};

    Map clause{{kEntityKey, "Follows"},
               {kFirstParameterKey, "a"},
               {kSecondParameterKey, "p"}};

    REQUIRE_THROWS_AS(handler.Handle(declaration, clause), SemanticErrorException);
  }
}
