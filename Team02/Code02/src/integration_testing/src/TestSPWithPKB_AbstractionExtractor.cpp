#include "catch.hpp"
#include <string>
#include <sstream>
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/PKB.h"
#include "PKB/Types/PkbTypes.h"
#include "SP/SP.h"
#include <utility>

TEST_CASE("Check if expressions are parsed correctly for uses") {
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
    auto uses =
        pkb_read_facade->GetUsesStatementVariablePairs(StatementType::ASSIGN);
    REQUIRE(uses == unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER,
                                            PkbTypes::VARIABLE>,
                                  PairHasherUtil::hash_pair>({std::make_pair(
        "1",
        "flag")}));

  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}

TEST_CASE("Check if follows/* are extracted correctly") {
  string input = "procedure computeCentroid {"
                 "  count = 0;"
                 "  cenX = 0;"
                 "  cenY = 0;"
                 "  while ((x != 0) && (y != 0)) {"
                 "    count = count + 1;"
                 "    cenX = cenX + x;"
                 "    cenY = cenY + x;"
                 "  }"
                 "  if (count == 0) then {"
                 "    flag = 1;"
                 "  } else {"
                 "    cenX = cenX / count;"
                 "    cenY = cenY / count;"
                 "  }"
                 "  normSq = cenX * cenX + cenY * cenY;"
                 "}";
  std::istringstream is;
  is.str(input);

  shared_ptr<PKB> pkb = make_shared<PKB>();
  shared_ptr<SP> sp = make_shared<SP>();
  sp->ProcessSIMPLE(is, pkb);

  shared_ptr<PkbReadFacade>
      pkb_read_facade = make_shared<PkbReadFacade>(*pkb);

  SECTION("Check that all follows pair are present") {
    vector<pair<string, string>> expected_follows_pairs = {
        make_pair("1","2"),
        make_pair("2", "3"),
        make_pair("3", "4"),
        make_pair("5", "6"),
        make_pair("6","7"),
        make_pair("4", "8"),
        make_pair("10", "11"),
        make_pair("8", "12")
    };
    for (pair<string, string> fp : expected_follows_pairs) {
      if (!pkb_read_facade->HasFollowsRelationship(fp.first, fp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }

  SECTION("Check that all follows* pair are present") {
    vector<pair<string, string>> expected_follows_star_pairs = {
        // follows
        make_pair("1","2"),
        make_pair("2", "3"),
        make_pair("3", "4"),
        make_pair("5", "6"),
        make_pair("6","7"),
        make_pair("4", "8"),
        make_pair("10", "11"),
        make_pair("8", "12"),
        // follows*
        make_pair("1", "3"),
        make_pair("1", "4"),
        make_pair("1", "8"),
        make_pair("1", "12"),
        make_pair("2", "4"),
        make_pair("2", "8"),
        make_pair("2", "12"),
        make_pair("3", "8"),
        make_pair("3", "12"),
        make_pair("4", "12"),
        make_pair("5", "7")
    };
    for (pair<string, string> fp : expected_follows_star_pairs) {
      if (!pkb_read_facade->IsFollowsStar(fp.first, fp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }
}

TEST_CASE("Check if parent/* are extracted correctly") {
  string input = "procedure computeCentroid {"
                 "  count = 0;"
                 "  cenX = 0;"
                 "  cenY = 0;"
                 "  while ((x != 0) && (y != 0)) {"
                 "    count = count + 1;"
                 "    cenX = cenX + x;"
                 "    while (x == 1) {"
                 "      a = a + 10;"
                 "      b = a + 20;"
                 "    }"
                 "    cenY = cenY + x;"
                 "  }"
                 "  if (count == 0) then {"
                 "    flag = 1;"
                 "    if (x == 2) then {"
                 "      a = 15;"
                 "      b = 25;"
                 "    } else {"
                 "      a = 0;"
                 "    }"
                 "  } else {"
                 "    cenX = cenX / count;"
                 "    cenY = cenY / count;"
                 "  }"
                 "  normSq = cenX * cenX + cenY * cenY;"
                 "}";
  std::istringstream is;
  is.str(input);

  shared_ptr<PKB> pkb = make_shared<PKB>();
  shared_ptr<SP> sp = make_shared<SP>();
  sp->ProcessSIMPLE(is, pkb);

  shared_ptr<PkbReadFacade>
      pkb_read_facade = make_shared<PkbReadFacade>(*pkb);

  SECTION("Check that all parent pair are present") {
    vector<pair<string, string>> expected_parent_pairs = {
        make_pair("4","5"),
        make_pair("4", "6"),
        make_pair("4", "7"),
        make_pair("7", "8"),
        make_pair("7", "9"),
        make_pair("4", "10"),
        make_pair("11","12"),
        make_pair("11", "13"),
        make_pair("13", "14"),
        make_pair("13", "15"),
        make_pair("13", "16"),
        make_pair("11", "17"),
        make_pair("11", "18")
    };
    for (pair<string, string> pp : expected_parent_pairs) {
      if (!pkb_read_facade->HasParentChildRelationship(pp.first, pp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }

  SECTION("Check that all parent* pair are present") {
    vector<pair<string, string>> expected_parent_star_pairs = {
        // parent pairs
        make_pair("4","5"),
        make_pair("4", "6"),
        make_pair("4", "7"),
        make_pair("7", "8"),
        make_pair("7", "9"),
        make_pair("4", "10"),
        make_pair("11","12"),
        make_pair("11", "13"),
        make_pair("13", "14"),
        make_pair("13", "15"),
        make_pair("13", "16"),
        make_pair("11", "17"),
        make_pair("11", "18"),
        // parent* pairs
        make_pair("4", "8"),
        make_pair("4", "9"),
        make_pair("11", "14"),
        make_pair("11", "15"),
        make_pair("11", "16")
    };
    for (pair<string, string> pp : expected_parent_star_pairs) {
      if (!pkb_read_facade->HasAncestorDescendantRelationship(pp.first, pp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }
}