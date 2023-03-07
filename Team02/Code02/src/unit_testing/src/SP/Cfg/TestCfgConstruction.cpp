#include <sstream>
#include "catch.hpp"
#include <string>
#include "SP/Parser/Parser.h"
#include "SP/Parser/AssignStatementParser.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"
#include "SP/SP.h"

void dfs(shared_ptr<CfgNode> node,
         int lvl,
         std::unordered_set<int> &visited,
         std::unordered_map<int, vector<vector<int>>> &stmts_at_lvl,
         vector<string> &node_representations) {
  vector<int> stmt_numbers = node->GetNodeStmts();
  stmts_at_lvl[lvl].push_back(stmt_numbers);
  for (auto const stmt : stmt_numbers) {
    visited.insert(stmt);
  }
  node_representations.emplace_back(node->GetStringRepresentation());
  for (auto &[key, child] : node->GetNodeTrans()) {
    vector<int> stmt_numbers = child->GetNodeStmts();
    for (auto const kStmt : stmt_numbers) {
      if (visited.find(kStmt) != visited.end()) {
        continue;
      }
      dfs(child, lvl + 1, visited, stmts_at_lvl, node_representations);
    }
  }
}

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
    shared_ptr<CfgExtractor> cfg_extractor = make_shared<CfgExtractor>(cfg);

    Program::ProcListContainer procedures = program->GetProcedureList();

    for (shared_ptr<Procedure> &p : procedures) {
      p->Accept(cfg_extractor);
      auto statements = p->GetStatementList();
      for (auto const &s : statements) {
        s->Accept(cfg_extractor);
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

TEST_CASE("Check if CFG is created correctly for a procedure starting with if") {
  try {
    string input = "procedure main {\n"
                   "  if (x==1) then {\n"
                   "      count = 1;\n"
                   "  } else {\n"
                   "     count = 0;\n"
                   "  }\n"
                   "  if (x == 2 ) then {"
                   "      count =2;"
                   "  } else {"
                   "    count = 3;"
                   "  }"
                   " count = 4;"
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
    auto cfg_main = cfg->GetCfgRootNodes()["main"];
    std::unordered_set<int> visited;
    std::unordered_map<int, vector<vector<int>>> stmts_at_lvl;
    vector<string> node_representations;

    dfs(cfg_main, 0, visited, stmts_at_lvl, node_representations);

    vector<vector<vector<int>>>
        answer = {{{1}}, {{2}, {3}}, {{4}}, {{5}, {6}}, {{7}}};

    for (int i = 0; i < answer.size(); i++) {
      REQUIRE(stmts_at_lvl[i].size() == answer[i].size());
      if (stmts_at_lvl[i] != answer[i]) {
        FAIL("Wrong number of stmts at a lvl");
      }
    }

    std::unordered_set<string>
        expected_representations =
        {"{1}", "{2}", "{3}", "{4}", "{5}", "{6}", "{7}"};
    REQUIRE(node_representations.size() == expected_representations.size());
    for (auto s : node_representations) {
      if (expected_representations.find(s)
          == expected_representations.end()) {
        FAIL(s + " is an unexpected representation");
      }
    }
  } catch (SpaException &e) {
    FAIL(string("Unexpectedly failed: ") + string(e.what()));
  }
}

TEST_CASE("Check if CFG is created correctly for if statements") {
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
    auto cfg_main = cfg->GetCfgRootNodes()["main"];
    std::unordered_set<int> visited;
    std::unordered_map<int, vector<vector<int>>> stmts_at_lvl;
    vector<string> node_representations;

    dfs(cfg_main, 0, visited, stmts_at_lvl, node_representations);
    vector<vector<vector<int>>>
        answer = {{{1, 2}}, {{3}}, {{4, 5}, {9}}, {{6}, {10}}, {{7}, {8}}};

    for (int i = 0; i < answer.size(); i++) {
      REQUIRE(stmts_at_lvl[i].size() == answer[i].size());
      if (stmts_at_lvl[i] != answer[i]) {
        FAIL("Wrong number of stmts at a lvl");
      }
    }

    std::unordered_set<string>
        expected_representations =
        {"{1,2}", "{3}", "{4,5}", "{6}", "{7}", "{8}", "{9}", "{10}"};
    REQUIRE(node_representations.size() == expected_representations.size());
    for (auto s : node_representations) {
      if (expected_representations.find(s)
          == expected_representations.end()) {
        FAIL(s + " is an unexpected representation");
      }
    }

  } catch (SpaException &e) {
    FAIL(string("Unexpectedly failed: ") + string(e.what()));
  }
}
