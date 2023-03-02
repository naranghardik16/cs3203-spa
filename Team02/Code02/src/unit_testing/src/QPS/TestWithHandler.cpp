#include "catch.hpp"

#include "QPS/ValidationHandler/WithHandler.h"
#include "QPS/Clause/WithClauseSyntax.h"
#include "General/SpaException/SemanticErrorException.h"
#include "General/SpaException/SyntaxErrorException.h"

TEST_CASE("Test WithHandler HandleSyntax") {
  WithHandler handler;

  SECTION("Test valid clause syntax both attrRef - no exception") {
    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a.stmt#", "v.varName"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }


  SECTION("Test valid clause syntax arg1 attrRef - no exception") {
    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.procName", "\"main\""}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test valid clause syntax arg2 attrRef - no exception") {
    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"1", "c.value"}}});

    REQUIRE_NOTHROW(handler.HandleSyntax(clause));
  }

  SECTION("Test invalid clause syntax - synonym only") {
    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }

  SECTION("Test invalid clause syntax - invalid attr name") {
    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a.test", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSyntax(clause), SyntaxErrorException);
  }
}

TEST_CASE("Test WithHandler HandleSemantic") {
  WithHandler handler;

  SECTION("Test valid clause semantic (read.varName") {
    Map declaration{{"r", "read"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"r.varName", "\"x\""}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (read.stmt#") {
    Map declaration{{"r", "read"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"r.stmt#", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (print.varName") {
    Map declaration{{"p", "print"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.varName", "\"x\""}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (print.stmt#") {
    Map declaration{{"p", "print"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.stmt#", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (assign.stmt#") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a.stmt#", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (while.stmt#") {
    Map declaration{{"w", "while"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"w.stmt#", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (if.stmt#") {
    Map declaration{{"i", "if"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"i.stmt#", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (stmt.stmt#") {
    Map declaration{{"s", "stmt"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"s.stmt#", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (call.stmt#") {
    Map declaration{{"c", "call"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.stmt#", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (call.procName") {
    Map declaration{{"c", "call"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.procName", "\"v\""}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (procedure.procName") {
    Map declaration{{"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.procName", "\"v\""}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (constant.value") {
    Map declaration{{"c", "constant"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.value", "1"}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test valid clause semantic (variable.varName") {
    Map declaration{{"v", "variable"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"v.varName", "\"v\""}}});

    REQUIRE_NOTHROW(handler.HandleSemantic(clause, declaration));
  }

  SECTION("Test invalid clause semantic, synonym not declared") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"v.varName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, synonym not declared") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"v.varName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (assign.varName)") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a.varName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (assign.procName)") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a.procName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (assign.value)") {
    Map declaration{{"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a.value", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (read.value)") {
    Map declaration{{"r", "read"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"r.value", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (read.procName)") {
    Map declaration{{"r", "read"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"r.procName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (print.value)") {
    Map declaration{{"p", "print"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.value", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (print.procName)") {
    Map declaration{{"p", "print"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.procName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (proc.value)") {
    Map declaration{{"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.value", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (proc.varName)") {
    Map declaration{{"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.varName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (proc.stmt#)") {
    Map declaration{{"p", "procedure"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.stmt#", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (constant.procName)") {
    Map declaration{{"c", "constant"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.procName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (constant.varName)") {
    Map declaration{{"c", "constant"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.varName", "\"v\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid attr (constant.stmt#)") {
    Map declaration{{"c", "constant"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.stmt#", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid comparison (proc.procName, assign.stmt#)") {
    Map declaration{{"p", "procedure"},
                    {"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.procName", "a.stmt#"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid comparison (proc.procName, INT)") {
    Map declaration{{"p", "procedure"},
                    {"a", "assign"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"p.procName", "1"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid comparison (variable.varName, constant.value)") {
    Map declaration{{"v", "variable"},
                    {"c", "constant"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"v.varName", "c.value"}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid comparison (constant.value, STRING)") {
    Map declaration{{"v", "variable"},
                    {"c", "constant"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"c.value", "\"x\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, invalid comparison (INT, STRING)") {
    Map declaration{{"v", "variable"},
                    {"c", "constant"}};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"1", "\"x\""}}});

    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }

  SECTION("Test invalid clause semantic, empty declaration map") {
    Map declaration{};

    std::shared_ptr<ClauseSyntax> clause(new WithClauseSyntax{{"", {"a.stmt#", "v.varName"}}});


    REQUIRE_THROWS_AS(handler.HandleSemantic(clause, declaration), SemanticErrorException);
  }
}