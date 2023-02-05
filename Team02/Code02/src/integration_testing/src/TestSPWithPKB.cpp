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

TEST_CASE("Check if SP works with PKB") {
  try {
    Tokenizer *tokenizer = new Tokenizer();
    string input = "procedure main {\n"
                   "  flag = 1;\n"
                   "}\n"
                   "procedure computeCentroid {\n"
                   "  count = 5;\n"
                   "  cenX = 10;\n"
                   "  cenY = 15;\n"
                   "  read input;\n"
                   "  print output;\n"
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
      KeyValueStore<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE_STORE_INDEX>
          procedure_store = pkb_read_facade->GetProcedureStore();
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

    SECTION("Check if Variables are stored correctly in the pkb") {
      KeyValueStore<PkbTypes::VARIABLE, PkbTypes::VARIABLE_STORE_INDEX>
          var_store = pkb_read_facade->GetVariableStore();
      std::vector<std::string_view>
          var_names{"flag", "count", "cenX", "cenY", "input", "output"};
      for (auto var_name : var_names) {
        auto it = std::find_if(var_store.map.begin(),
                               var_store.map.end(),
                               [&var_name](pair<PkbTypes::VARIABLE,
                                                PkbTypes::VARIABLE_STORE_INDEX> const &pair_var) {
                                 return pair_var.first == var_name;
                               });
        if (it == var_store.map.end()) {
          FAIL();
        }
      }
      SUCCEED();
    }

    SECTION("Check if Constants are stored correctly in the pkb") {
      auto const_store = pkb_read_facade->GetConstantStore();
      std::vector<std::string> constants{"1", "5", "10", "15"};
      for (auto const &constant : constants) {
        auto it = const_store.find(constant);
        if (it == const_store.end()) {
          FAIL(constant + " should be in the pkb");
        }
      }
      SUCCEED();
      const std::string kNonExistingConst = "123";
      auto it = const_store.find(kNonExistingConst);
      if (it == const_store.end()) {
        SUCCEED();
      } else {
        FAIL(kNonExistingConst + " should not be in the pkb");
      }

    }
  } catch (SpaException &e) {
    cout << e.what();
  }
}