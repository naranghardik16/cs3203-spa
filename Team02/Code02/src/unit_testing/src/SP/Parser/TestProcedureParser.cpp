#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"
#include "SP/Parser/ProcedureParser.h"

#include "catch.hpp"
#include <string>
#include "SP/NameToken.h"
#include "SP/PunctuationToken.h"

TEST_CASE("Check if IsProcedureEnd works") {
  Parser::Line end_line{new PunctuationToken("}", RIGHT_BRACE)};
  REQUIRE(ProcedureParser::IsProcedureEnd(end_line) == true);
}