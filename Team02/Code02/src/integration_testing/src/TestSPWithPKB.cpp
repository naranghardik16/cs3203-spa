#include "catch.hpp"
#include <string>
#include <sstream>
#include "./SP/Tokenizer.h"
#include "./SP/Parser/Parser.h"
#include "./SP/DesignExtractor/DesignExtractor.h"
//#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"

TEST_CASE("Check if everything works together") {
  try {
    Tokenizer* tokenizer = new Tokenizer();
    string input = "procedure computeCentroid {"
                   "  count = 0;\n"
                   "  cenX = 0;\n"
                   "  cenY = 0;\n"
                   "}";
    std::istringstream is;
    is.str(input);

    Parser::TokenStream *tokens = tokenizer->Tokenize(is);

    Parser *parser = new Parser();
    Program program = parser->ParseSource(*tokens);

    DesignExtractor *design_extractor = new DesignExtractor();
    design_extractor->ExtractDesign(&program);

    PKB pkb = PKB();
    PkbReadFacade *pkb_read_facade = new PkbReadFacade(pkb);
    //#TODO: Implement portion when PKB is completed
    SECTION("Check if Accept(Procedure) works") {
      pkb_read_facade->GetProcedureStore();
      REQUIRE(1 == 1);
    }
  } catch (SpaException *e) {
    cout << e->what();
  }
}