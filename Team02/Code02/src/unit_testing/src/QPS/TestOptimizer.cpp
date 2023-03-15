#include "catch.hpp"

#include "QPS/QueryParser.h"
#include "QPS/Optimizer/Optimizer.h"

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
