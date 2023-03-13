#include "catch.hpp"
#include <string>
#include <sstream>
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/PKB.h"
#include "SP/SP.h"
#include <utility>

TEST_CASE("Check if Next Abstractions are correct") {
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
    shared_ptr<CfgExtractor> cfg_extractor = make_shared<CfgExtractor>(cfg);

    Program::ProcListContainer procedures = program->GetProcedureList();

    for (shared_ptr<Procedure> &p : procedures) {
      p->Accept(cfg_extractor);
      auto statements = p->GetStatementList();
      for (auto const &s : statements) {
        s->Accept(cfg_extractor);
      }
    }

    PkbWriteFacade *pkb_write_facade_;
    pkb_write_facade_ = new PkbWriteFacade(*pkb);

    pkb_write_facade_->AddCfg(cfg);

    PkbReadFacade *pkb_read_facade_;
    pkb_read_facade_ = new PkbReadFacade(*pkb);

    REQUIRE(pkb_read_facade_->IsNext("1", "2") == true);
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}

TEST_CASE("") {

}