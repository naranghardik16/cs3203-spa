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

    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}

TEST_CASE("A bit more complex") {
  try {
    string input = "procedure main {\n"
                   "  x = 1;"
                   "  flag = 0;"
                   "  if (x==1) then {"
                   "    flag = 1;"
                   "    y = 10;"
                   "    if(y > 10) then {"
                   "       z = 100;"
                   "    } else {"
                   "       z = 10; "
                   "    }"
                   "  } else {"
                   "    flag = 0;"
                   "  }\n"
                   "  y = 20;"
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
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "9") == true);
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}

TEST_CASE("A bit bit more complex") {
  try {
    string input = "procedure main {\n"
                   "  x = 1;"
                   "  flag = 0;"
                   "  while (x==1) {"
                   "    flag = 1;"
                   "    while( flag == 1 ) {"
                   "        flag = 2;"
                   "    }"
                   "  } "
                   "  y = 20;"
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
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "5") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "5") == true);
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}

TEST_CASE("Test Next with Bumblebee") {
  try {
    string input = "procedure Bumblebee {\n"
                   "  read x;"
                   "  y = 2 * z;"
                   "  call Megatron;"
                   "  z = p - y;"
                   "  if (q!=1) then {"
                   "      z = x + 24;"
                   "      call Ironhide;}"
                   "  else {"
                   "      while (z>0) {"
                   "          y = x * q - 5;"
                   "          z = z - 1;}"
                   "      y = x + y * z + p * q;"
                   "      call Ironhide;}"
                   "  i = x + j + z;"
                   "  call Barricade;"
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
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "5") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "8") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("7", "13") == true);
    REQUIRE(pkb_read_facade_->IsNext("8", "9") == true);
    REQUIRE(pkb_read_facade_->IsNext("8", "11") == true);
    REQUIRE(pkb_read_facade_->IsNext("9", "10") == true);
    REQUIRE(pkb_read_facade_->IsNext("10", "8") == true);
    REQUIRE(pkb_read_facade_->IsNext("11", "12") == true);
    REQUIRE(pkb_read_facade_->IsNext("12", "13") == true);
    REQUIRE(pkb_read_facade_->IsNext("13", "14") == true);
    REQUIRE(pkb_read_facade_->HasNext("14") == false);
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}

TEST_CASE("Test Next with while at the start of the procedure") {
  try {
    string input = "procedure main {\n"
                   "  while (x==1) {"
                   "    flag = 1;"
                   "    while( flag == 1 ) {"
                   "        flag = 2;"
                   "    }"
                   "    count = count + 1;"
                   "  } "
                   "  y = 20;"
                   "  while (x==1) {"
                   "    flag = 1;"
                   "    while( flag == 1 ) {"
                   "        flag = 2;"
                   "    }"
                   "  }"
                   "  count = count - 1; "
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
    REQUIRE(pkb_read_facade_->IsNext("2", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "4") == true);
    REQUIRE(pkb_read_facade_->IsNext("4", "3") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "5") == true);
    REQUIRE(pkb_read_facade_->IsNext("5", "1") == true);
    REQUIRE(pkb_read_facade_->IsNext("1", "6") == true);
    REQUIRE(pkb_read_facade_->IsNext("6", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("7", "8") == true);
    REQUIRE(pkb_read_facade_->IsNext("8", "9") == true);
    REQUIRE(pkb_read_facade_->IsNext("9", "10") == true);
    REQUIRE(pkb_read_facade_->IsNext("10", "9") == true);
    REQUIRE(pkb_read_facade_->IsNext("9", "7") == true);
    REQUIRE(pkb_read_facade_->IsNext("3", "8") == false);
    REQUIRE(pkb_read_facade_->IsNext("5", "3") == false);
    REQUIRE(pkb_read_facade_->IsNext("10", "11") == false);
    REQUIRE(pkb_read_facade_->IsNext("10", "8") == false);
    REQUIRE(pkb_read_facade_->IsNext("11", "12") == false);
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}


