#include "catch.hpp"
#include <string>
#include <sstream>
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"
#include "SP/SP.h"

TEST_CASE("Check if SP works with PKB for Abstraction Extractor") {
  try {
    string input = "procedure main {\n"
                   "  flag = flag + 1;\n"
                   "}\n";
    std::istringstream is;
    is.str(input);

    shared_ptr<PKB> pkb = make_shared<PKB>();
    shared_ptr<SP> sp = make_shared<SP>();
    sp->ProcessSIMPLE(is, pkb);

    shared_ptr<PkbReadFacade>
        pkb_read_facade = make_shared<PkbReadFacade>(*pkb);
    SECTION("Check if expressions are parsed correctly for uses") {
      auto uses =
          pkb_read_facade->GetUsesStatementVariablePairs(StatementType::ASSIGN);
      REQUIRE(uses == unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                              PkbTypes::VARIABLE>,
                                    PairHasherUtil::hash_pair>({std::make_pair(
          "1",
          "flag")}));
    }
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}