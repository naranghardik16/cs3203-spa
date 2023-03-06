#include <sstream>
#include "catch.hpp"
#include <string>
#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"
#include "SP/SP.h"

TEST_CASE("Check if CFG is created for a simple procedure") {
  try {
    string input = "procedure main {\n"
                   "  flag = flag + 1;\n"
                   "}\n"
                   "procedure main2 {\n"
                   " count = count - 1;"
                   " count = count + 1;"
                   "}\n";
    std::istringstream is;
    is.str(input);

    shared_ptr<PKB> pkb = make_shared<PKB>();
    shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
    shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(is);

    shared_ptr<Parser> parser = make_shared<Parser>();
    shared_ptr<Program> program = parser->ParseSource(*tokens);

    auto cfg = make_shared<Cfg>();
    shared_ptr<CfgExtractor> cfg_extracter = make_shared<CfgExtractor>(cfg);

    Program::ProcListContainer procedures = program->GetProcedureList();

    for (shared_ptr<Procedure> &p : procedures) {
      p->Accept(cfg_extracter);
      auto statements = p->GetStatementList();
      for (auto const &s : statements) {
        s->Accept(cfg_extracter);
      }
    }

    SECTION("Check if Procedure name stored is correct") {
      REQUIRE(cfg->GetCfgRootNodes()["main"] != nullptr);
      REQUIRE(cfg->GetCfgRootNodes()["main2"] != nullptr);
      REQUIRE(cfg->GetCfgRootNodes()["proc"] == nullptr);
    }

    SECTION("Check if right non branching statements are stored") {
      auto assign_node_main = cfg->GetStmtToCfg()[1];
      REQUIRE(assign_node_main->GetNodeStmts().size() == 1);
      REQUIRE(assign_node_main->GetNodeStmts()[0] == 1);

      auto assign_node_main2 = cfg->GetCfgRootNodes()["main2"];
      REQUIRE(assign_node_main2->GetNodeStmts().size() == 2);
    }

  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}