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
    string input = "procedure main {\n"
                   "  flag = 0;\n"
                   "}\n"
                   "procedure computeCentroid {\n"
                   "  count = 0;\n"
                   "  cenX = 0;\n"
                   "  cenY = 0;\n"
                   "}";
    std::istringstream is;
    is.str(input);

    Parser::TokenStream *tokens = tokenizer->Tokenize(is);

    Parser *parser = new Parser();
    Program program = parser->ParseSource(*tokens);

    PKB *pkb = new PKB();
    DesignExtractor *design_extractor = new DesignExtractor(pkb);
    design_extractor->ExtractDesign(&program);

    PkbReadFacade *pkb_read_facade = new PkbReadFacade(*pkb);
    SECTION("Check if Accept(Procedure) works") {
      KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX> procedure_store = pkb_read_facade->GetProcedureStore();
      auto it = procedure_store.map.find("computeCentroid");
      if (it == procedure_store.map.end()) {
        FAIL();
      }

      it = procedure_store.map.find("main");
      if (it == procedure_store.map.end()) {
        FAIL();
      } else {
        SUCCEED();
      }
    }
  } catch (SpaException *e) {
    cout << e->what();
  }
}