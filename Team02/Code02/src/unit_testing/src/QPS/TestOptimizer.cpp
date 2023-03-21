#include "catch.hpp"

#include "QPS/QueryParser.h"
#include "QPS/Optimizer/Optimizer.h"
#include "QPS/Clause/PatternClauseSyntax.h"
#include "QPS/Clause/SuchThatClauseSyntax.h"
#include "QPS/Clause/WithClauseSyntax.h"

SyntaxPair CreateCorrectSyntaxPair(std::string entity, std::vector<std::string> parameter_vec) {
  SyntaxPair syntax;
  syntax.first = entity;
  syntax.second = parameter_vec;
  return syntax;
}

TEST_CASE("Test Clause Sorting") {
  auto qp = std::make_shared<QueryParser>();
  auto opt = std::make_shared<Optimizer>();

  SECTION("Test argument level sorting -- statements") {
    std::string query = "stmt s1,s2; assign a1; Select <s1,s2> such that Follows(s1,s2) and Follows(s2,a1)";
    auto group = std::make_shared<ClauseGroup>();
    auto parser_output = qp->ParseQuery(query);
    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());

    Map declaration_map = {{"s2",  "stmt"}, {"s1",  "stmt"}, {"a1", "assign"}};
    std::shared_ptr<ClauseSyntax> follows_syntax_stmt = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Follows", {"s1", "s2"}));
    std::shared_ptr<ClauseSyntax> follows_syntax_assign = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Follows", {"s2", "a1"}));
    std::vector<ClauseSyntaxPtrList> correct_vector = {{follows_syntax_assign, follows_syntax_stmt}};

    for (int i = 0; i < correct_vector.size(); i++) {
      auto correct_clause_lst = correct_vector[i];
      auto parsed_lst = groups[i]->GetSortedClauses(declaration_map);
      for (int j = 0; j < correct_clause_lst.size(); j++) {
        REQUIRE(correct_clause_lst[j]->Equals(*parsed_lst[j]));
      }
    }
  }

  SECTION("Test argument level sorting -- Modifies") {
    std::string query = "procedure p; variable v; stmt s; Select p such that Modifies(p, v) and Modifies(s,v)";
    auto group = std::make_shared<ClauseGroup>();
    auto parser_output = qp->ParseQuery(query);
    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());

    Map declaration_map = {{"p",  "procedure"}, {"v",  "variable"}, {"s", "stmt"}};
    std::shared_ptr<ClauseSyntax> modifies_p = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Modifies", {"p", "v"}));
    std::shared_ptr<ClauseSyntax> modifies_s = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Modifies", {"s", "v"}));
    std::vector<ClauseSyntaxPtrList> correct_vector = {{modifies_p, modifies_s}};

    for (int i = 0; i < correct_vector.size(); i++) {
      auto correct_clause_lst = correct_vector[i];
      auto parsed_lst = groups[i]->GetSortedClauses(declaration_map);
      for (int j = 0; j < correct_clause_lst.size(); j++) {
        REQUIRE(correct_clause_lst[j]->Equals(*parsed_lst[j]));
      }
    }
  }


  SECTION("Test synonym level sorting") {
    std::string query = "stmt s2; variable v1; Select v1 such that Uses(s2,v1) and Uses(s2,\"v\")";
    auto group = std::make_shared<ClauseGroup>();
    auto parser_output = qp->ParseQuery(query);
    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());

    Map declaration_map = {{"s2",  "stmt"}, {"v1",   "variable"}};
    std::shared_ptr<ClauseSyntax> uses_syntax = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Uses", {"s2", "v1"}));
    std::shared_ptr<ClauseSyntax> uses_syntax_less_syn = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Uses", {"s2", "\"v\""}));
    std::vector<ClauseSyntaxPtrList> correct_vector = {{uses_syntax_less_syn, uses_syntax}};

    for (int i = 0; i < correct_vector.size(); i++) {
      auto correct_clause_lst = correct_vector[i];
      auto parsed_lst = groups[i]->GetSortedClauses(declaration_map);
      for (int j = 0; j < correct_clause_lst.size(); j++) {
        REQUIRE(correct_clause_lst[j]->Equals(*parsed_lst[j]));
      }
    }
  }

  SECTION("Test clause type level sorting") {
    std::string query = "stmt s2; variable v1; assign a1,a2; Select v1 such that Affects(a1,a2) and Follows(s2,"
                        "a1) pattern a1(v1,_)"
                        "with"
                        " v1.varName = \"assign\"";
    auto group = std::make_shared<ClauseGroup>();
    auto parser_output = qp->ParseQuery(query);
    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());

    Map declaration_map = {{"s2", "stmt"}, {"a2",  "assign"}, {"a1", "assign"},
                           {"v1",   "variable"}};
    std::shared_ptr<ClauseSyntax> affects_syntax = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Affects", {"a1", "a2"}));
    std::shared_ptr<ClauseSyntax> follows_syntax = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Follows", {"s2", "a1"}));
    std::shared_ptr<ClauseSyntax> pattern_syntax = std::make_shared<PatternClauseSyntax>(CreateCorrectSyntaxPair
                                                                                             ("a1",
                                                                                              {"v1", "_"}));
    std::shared_ptr<ClauseSyntax> with_syntax = std::make_shared<WithClauseSyntax>(
        CreateCorrectSyntaxPair("", {"v1.varName", "\"assign\""}));
    std::vector<ClauseSyntaxPtrList> correct_vector = {{with_syntax, pattern_syntax, follows_syntax , affects_syntax}};

    for (int i = 0; i < correct_vector.size(); i++) {
      auto correct_clause_lst = correct_vector[i];
      auto parsed_lst = groups[i]->GetSortedClauses(declaration_map);
      for (int j = 0; j < correct_clause_lst.size(); j++) {
        REQUIRE(correct_clause_lst[j]->Equals(*parsed_lst[j]));
      }
    }
  }

  SECTION("Sort group") {
    std::string query("assign a, a1, a2, a3; stmt s1, s2, s3; variable v1, v2; Select <s1, a, a1, v2> "
                      "pattern a1(v1,_)"
                      "such that Modifies (s3, \"x\") and Follows (s1, s2) "
                      "with s3.stmt#=5 such that Uses (s2, v1)");
    auto parser_output = qp->ParseQuery(query);
    Map declaration_map = {{"a", "assign"}, {"a1",  "assign"}, {"a2", "assign"},
                           {"a3",  "assign"}, {"s1",  "stmt"}
        , {"s2", "stmt"}, {"s3", "stmt"}, {"v1", "variable"}, {"v2", "variable"}};
    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());
    std::shared_ptr<ClauseSyntax> pattern_syntax = std::make_shared<PatternClauseSyntax>(CreateCorrectSyntaxPair
        ("a1",  {"v1", "_"}));
    std::shared_ptr<ClauseSyntax> modifies_syntax = std::make_shared<SuchThatClauseSyntax>(CreateCorrectSyntaxPair
        ("Modifies", {"s3", "\"x\""}));
    std::shared_ptr<ClauseSyntax> follows_syntax = std::make_shared<SuchThatClauseSyntax>(CreateCorrectSyntaxPair
                                                                                               ("Follows",
                                                                                                {"s1",
                                                                                                         "s2"}));
    std::shared_ptr<ClauseSyntax> with_syntax = std::make_shared<WithClauseSyntax>(
        CreateCorrectSyntaxPair("", {"s3.stmt#", "5"}));
    std::shared_ptr<ClauseSyntax> uses_syntax = std::make_shared<SuchThatClauseSyntax>(
        CreateCorrectSyntaxPair("Uses", {"s2", "v1"}));
    std::vector<ClauseSyntaxPtrList> correct_vector = {{with_syntax, modifies_syntax}, {pattern_syntax,  uses_syntax,
                                                                           follows_syntax}};

    for (int i = 0; i < correct_vector.size(); i++) {
      auto correct_clause_lst = correct_vector[i];
      auto parsed_lst = groups[i]->GetSortedClauses(declaration_map);
      for (int j = 0; j < correct_clause_lst.size(); j++) {
        REQUIRE(correct_clause_lst[j]->Equals(*parsed_lst[j]));
      }
    }
  }
}

TEST_CASE("Test divided clause into groups") {
  auto qp = std::make_shared<QueryParser>();
  auto opt = std::make_shared<Optimizer>();

  SECTION("Test divide clause into groups 1") {
    std::string query("assign a, a1, a2; stmt s1, s2, s3; variable v1, v2; Select <s1, a, a1, v2> "
                      "such that Uses (5, \"y\") and Uses (s1, v1) and "
                      "Affects (a1, a2) with a1.stmt# = 20 "
                      "such that Parent (s1, s2) "
                      "pattern a2 (\"a\", _) such that Next (s2, s3) "
                      "and Modifies (s1, \"x\") and Modifies (a, v2) pattern a (v1, \"x\")");
    auto parser_output = qp->ParseQuery(query);

    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());
    REQUIRE(groups.size() == 3);
  }

  SECTION("Test divide clause into groups 2") {
    std::string query("assign a, a1, a2, a3; stmt s1, s2, s3; variable v1, v2; Select <s1, a, a1, v2> "
                      "such that Uses (5, \"y\") and Uses (s1, \"x\") and "
                      "Affects (4, a2) with a1.stmt# = 20 "
                      "such that Parent (1, s2) "
                      "pattern a2 (\"a\", _) such that Next (9, s3) "
                      "and Modifies (s1, \"x\") and Modifies (a3, v2) pattern a (v1, \"x\")");
    auto parser_output = qp->ParseQuery(query);

    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());
    REQUIRE(groups.size() == 8);
  }

  SECTION("Test divide clause into groups 3") {
    std::string query("assign a, a1, a2, a3; stmt s1, s2, s3; variable v1, v2; Select <s1, a, a1, v2> "
                      "such that Uses (s3, v1) "
                      "and Modifies (s3, \"x\") and Follows (s1, s2) "
                      "and Parent (s3, s1) and Uses (s2, v1)");
    auto parser_output = qp->ParseQuery(query);

    auto groups = opt->GetClauseGroups(parser_output->GetClauseSyntaxPtrList());
    REQUIRE(groups.size() == 1);
  }
}
