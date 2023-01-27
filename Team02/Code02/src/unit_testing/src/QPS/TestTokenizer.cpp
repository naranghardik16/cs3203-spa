#pragma once
#include "QPS/Tokenizer.h"
#include "QPS/PqlException/SemanticErrorException.h"
#include "QPS/PqlException/SyntaxErrorException.h"
#include "catch.hpp"

auto tokenizer = std::shared_ptr<Tokenizer>();
std::string kDeclarationKey = "Declarations";
std::string select_statement_key = "Select";
std::string kSynonymKey = "Synonym";
std::string kSuchThatKey = "Such That";
std::string kPatternKey = "Pattern";

//Split declaration statements from Select Statement
TEST_CASE("Check if AddDeclarationsAndStatementsIntoMap works") {
  std::vector<std::string> queries = {"variable v, v1;procedure p, p1;\nSelect v", "  assign a  ; while w; \n  Select a such that Parent* (w, a) pattern a (\"count\", _)", "variable v;", "Select v"};
  std::vector<std::vector<std::string>> correct_declaration_clauses {{"variable v, v1", "procedure p, p1"}, {"assign a", "while w"}, {"variable v"}, {}};
  std::vector<std::string> correct_select_statements = {"Select v", "Select a such that Parent* (w, a) pattern a (\"count\", _)", "", "Select v"};

  for (int i = 0; i < queries.size(); i++) {
    std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
    std::string query = queries[i];
    auto correct_clauses = correct_declaration_clauses[i];
    std::string correct_select_statement = correct_select_statements[i];

    subclauses_map = tokenizer->AddDeclarationsAndStatementsIntoMap(query, subclauses_map);
    std::vector<std::string> declaration_statements = subclauses_map[kDeclarationKey];
    //will always have at least an "" string
    std::string select_statement = subclauses_map[select_statement_key][0];
    REQUIRE(correct_clauses == declaration_statements);
    REQUIRE(correct_select_statement == select_statement);
  }
}

TEST_CASE("Check if AddSelectSubclausesIntoMap works as expected") {
  SECTION("Test if AddSelectSubclausesIntoMap can handle terminal names being synonyms") {
    std::string statement = "Select such such that Parent* (pattern, such) pattern such (\"count\", _)";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kSynonymKey, {"such"}},
                                                                             {kSuchThatKey, {"such that Parent* (pattern, such)"}},
                                                                             {kPatternKey, {"pattern such (\"count\", _)"}}};

    std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
    auto map = tokenizer->AddSelectSubclausesIntoMap(statement, subclauses_map);
    REQUIRE(map == correct_map);
  }

  SECTION("Test if AddSelectSubclausesIntoMap works without any such that or pattern clause") {
    std::string statement = "Select v";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kSynonymKey, {"v"}},
                                                                             {kSuchThatKey, {}},
                                                                             {kPatternKey, {}}};

    std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
    auto map = tokenizer->AddSelectSubclausesIntoMap(statement, subclauses_map);
    REQUIRE(map == correct_map);
  }

  SECTION("Test if AddSelectSubclausesIntoMap works on 1 such that and 1 pattern") {
    std::string statement = "Select a such that Parent* (w, a) pattern a (\"count\", _)";
    std::string reversed_conditions_statement = "Select a pattern a (\"count\", _) such that Parent* (w, a)";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kSynonymKey, {"a"}},
                                                                     {kSuchThatKey, {"such that Parent* (w, a)"}},
                                                                     {kPatternKey, {"pattern a (\"count\", _)"}}};

    std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
    auto map = tokenizer->AddSelectSubclausesIntoMap(statement, subclauses_map);
    std::unordered_map<std::string, std::vector<std::string>> reversed_conditions_subclauses_map;
    auto reversed_conditions_map = tokenizer->AddSelectSubclausesIntoMap(reversed_conditions_statement,
                                                                         reversed_conditions_subclauses_map);
    REQUIRE(map == correct_map);
    REQUIRE(reversed_conditions_map == correct_map);
  }

  SECTION("Test if AddSelectSubclausesIntoMap throws exception when there is no Select keyword") {
    std::string statement;
    try {
      std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
      auto map = tokenizer->AddSelectSubclausesIntoMap(statement, subclauses_map);
    } catch (const SyntaxErrorException& e) {
      REQUIRE(1);
    }
  }

  SECTION("Test if AddSelectSubclausesIntoMap throws exception when there is no synonym") {
    std::string statement = "Select ";
    try {
      std::unordered_map<std::string, std::vector<std::string>> subclauses_map;
      auto map = tokenizer->AddSelectSubclausesIntoMap(statement, subclauses_map);
    } catch (const SyntaxErrorException& se) {
      REQUIRE(1);
    }
  }
}

TEST_CASE("Test if TokenizeQuery works as expected") {
  SECTION("Repeated terminal names") {
    std::string query = "assign pattern; while w;\nSelect w such that Parent* (w, pattern) pattern pattern(_, \"(count)\")";
    std::string reversed_conditions_query = "assign pattern; while w;\nSelect w pattern pattern(_, \"(count)\") such that Parent* (w, pattern)";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kDeclarationKey, {"assign pattern", "while w"}},
                                                                             {select_statement_key,
                                                                              {"Select w such that Parent* (w, pattern) pattern pattern(_, \"(count)\")"}},
                                                                             {kSynonymKey, {"w"}},
                                                                             {kSuchThatKey, {"such that Parent* (w, pattern)"}},
                                                                             {kPatternKey, {"pattern pattern(_, \"(count)\")"}}};

    std::unordered_map<std::string, std::vector<std::string>> correct_reversed_map = {{kDeclarationKey, {"assign pattern", "while w"}},
                                                                                      {select_statement_key,
                                                                                       {"Select w pattern pattern(_, \"(count)\") such that Parent* (w, pattern)"}},
                                                                                      {kSynonymKey, {"w"}},
                                                                                      {kSuchThatKey, {"such that Parent* (w, pattern)"}},
                                                                                      {kPatternKey, {"pattern pattern(_, \"(count)\")"}}};
    auto map = tokenizer->TokenizeQuery(query);
    auto reversed_map = tokenizer->TokenizeQuery(reversed_conditions_query);

    REQUIRE(map == correct_map);
    REQUIRE(reversed_map == correct_reversed_map);
  }

  SECTION("Invalid clause without closing bracket") {
    std::string query = "assign a; while w;\nSelect w such that Parent* (w, a pattern a (\"count\", _";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kDeclarationKey, {"assign a", "while w"}},
                                                                             {select_statement_key,
                                                                              {"Select w such that Parent* (w, a pattern a (\"count\", _"}},
                                                                             {kSynonymKey, {"w"}},
                                                                             {kSuchThatKey,
                                                                              {"such that Parent* (w, a"}},
                                                                             {kPatternKey,
                                                                              {"pattern a (\"count\", _"}}};
    auto map = tokenizer->TokenizeQuery(query);

    REQUIRE(map == correct_map);
  }


  SECTION("Select statement with 1 Such That clause") {
    std::string query = "variable v; procedure p;\nSelect p such that Modifies (p, \"x\")";
    std::unordered_map<std::string, std::vector<std::string>>
        correct_map = {{kDeclarationKey, {"variable v", "procedure p"}},
                       {select_statement_key, {"Select p such that Modifies (p, \"x\")"}},
                       {kSynonymKey, {"p"}},
                       {kSuchThatKey, {"such that Modifies (p, \"x\")"}},
                       {kPatternKey, {}}};
    auto map = tokenizer->TokenizeQuery(query);
    REQUIRE(map == correct_map);
  }

  SECTION("Select statement with 1 Pattern clause") {
    std::string query = "assign Select;\nSelect Select pattern Select ( \"normSq\" , _\"cenX * cenX\"_)";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kDeclarationKey, {"assign Select"}},
                                                                             {select_statement_key,
                                                                              {R"(Select Select pattern Select ( "normSq" , _"cenX * cenX"_))"}},
                                                                             {kSynonymKey, {"Select"}},
                                                                             {kSuchThatKey, {}},
                                                                             {kPatternKey,
                                                                              {R"(pattern Select ( "normSq" , _"cenX * cenX"_))"}}};
    auto map = tokenizer->TokenizeQuery(query);
    REQUIRE(map == correct_map);
  }

  SECTION("Basic select statement with 1 declaration") {
    std::string query = "procedure p;\nSelect p";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kDeclarationKey, {"procedure p"}},
                                                                             {select_statement_key, {"Select p"}},
                                                                             {kSynonymKey, {"p"}},
                                                                             {kSuchThatKey, {}},
                                                                             {kPatternKey, {}}};
    auto map = tokenizer->TokenizeQuery(query);
    REQUIRE(map == correct_map);
  }

  SECTION("Select statement with 1 Pattern and 1 Such That Clause") {
    std::string query = "assign a; while w;\nSelect a such that Parent* (w, a) pattern a (\"count\", _)";
    std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kDeclarationKey, {"assign a", "while w"}},
                                                                             {select_statement_key,
                                                                              {"Select a such that Parent* (w, a) pattern a (\"count\", _)"}},
                                                                             {kSynonymKey, {"a"}},
                                                                             {kSuchThatKey,
                                                                              {"such that Parent* (w, a)"}},
                                                                             {kPatternKey,
                                                                              {"pattern a (\"count\", _)"}}};
    auto map = tokenizer->TokenizeQuery(query);
    REQUIRE(map == correct_map);
  }


   SECTION("Brackets inside a clause") {
  std::string query = "assign a; while w;\nSelect w such that Parent* (w, a) pattern a (\"(count)\", _)";
  std::unordered_map<std::string, std::vector<std::string>> correct_map = {{kDeclarationKey, {"assign a", "while w"}},
                                                                           {select_statement_key,
                                                                            {"Select w such that Parent* (w, a) pattern a (\"(count)\", _)"}},
                                                                           {kSynonymKey, {"w"}},
                                                                           {kSuchThatKey,
                                                                            {"such that Parent* (w, a)"}},
                                                                           {kPatternKey,
                                                                            {"pattern a (\"(count)\", _)"}}};
  auto map = tokenizer->TokenizeQuery(query);
  REQUIRE(map == correct_map);
}

}
