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

TEST_CASE("Check if calls/* are extracted correctly") {
  string input = "procedure First {"
                 "read x;"
                 "read z;"
                 "call Second; }"
                 ""
                 "procedure Second {"
                 "    x = 0;"
                 "    i = 5;"
                 "    while (i!=0) {"
                 "        x = x + 2*y;"
                 "        call Third;"
                 "        i = i - 1; }"
                 "    if (x==1) then {"
                 "        x = x+1; }"
                 "    else {"
                 "        z = 1; }"
                 "    z = z + x + i;"
                 "    y = z + 2;"
                 "    x = x * y + z; }"
                 ""
                 "procedure Third {"
                 "    z = 5;"
                 "    v = z;"
                 "    print v; }";
  std::istringstream is;
  is.str(input);

  shared_ptr<PKB> pkb = make_shared<PKB>();
  shared_ptr<SP> sp = make_shared<SP>();
  sp->ProcessSIMPLE(is, pkb);

  shared_ptr<PkbReadFacade>
      pkb_read_facade = make_shared<PkbReadFacade>(*pkb);

  SECTION("Check that all calls pair are present") {
    vector<pair<string, string>> expected_call_pairs = {
        make_pair("First","Second"),
        make_pair("Second", "Third")
    };
    for (pair<string, string> pp : expected_call_pairs) {
      // TODO: Update with PKB retrieve calls relationship method
      if (!pkb_read_facade->HasCallsRelation(pp.first, pp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }

  SECTION("Check that all calls* pair are present") {
    vector<pair<string, string>> expected_call_pairs = {
        make_pair("First","Second"),
        make_pair("Second", "Third"),
        make_pair("First", "Third")
    };
    for (pair<string, string> pp : expected_call_pairs) {
      if (!pkb_read_facade->HasCallsStarRelation(pp.first, pp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }
}

TEST_CASE("Check if modifies are extracted correctly") {
  string input = "    procedure main {\n"
                 "        flag = 0;\n"
                 "        call computeCentroid;\n"
                 "        call printResults;\n"
                 "    }\n"
                 "    procedure readPoint {\n"
                 "        read x;\n"
                 "        read y;\n"
                 "    }\n"
                 "    procedure printResults {\n"
                 "        print flag;\n"
                 "        print cenX;\n"
                 "        print cenY;\n"
                 "        print normSq;\n"
                 "    }\n"
                 "    procedure computeCentroid {\n"
                 "        count = 0;\n"
                 "        cenX = 0;\n"
                 "        cenY = 0;\n"
                 "        call readPoint;\n"
                 "        while ((x != 0) && (y != 0)) {\n"
                 "            count = count + 1;\n"
                 "            cenX = cenX + x;\n"
                 "            cenY = cenY + y;\n"
                 "            if (x == 1) then {\n"
                 "                call readPoint;"
                 "            } else {"
                 "                z = 1;"
                 "            }\n"
                 "         }\n"
                 "        if (count == 0) then {\n"
                 "            flag = 1;\n"
                 "        } else {\n"
                 "            cenX = cenX / count;"
                 "            while (count == 0) {"
                 "                call readPoint;"
                 "                count = 1;"
                 "            }\n"
                 "            cenY = cenY / count;\n"
                 "        }\n"
                 "        normSq = cenX * cenX + cenY * cenY;\n"
                 "    }";
  std::istringstream is;
  is.str(input);

  shared_ptr<PKB> pkb = make_shared<PKB>();
  shared_ptr<SP> sp = make_shared<SP>();
  sp->ProcessSIMPLE(is, pkb);

  shared_ptr<PkbReadFacade>
      pkb_read_facade = make_shared<PkbReadFacade>(*pkb);

  SECTION("Check that all modifiesS pair are present") {
    vector<pair<string, string>> expected_modifies_s_pairs = {
        // Modifies(a, v)
        make_pair("1","flag"),
        // Modifies(re, v)
        make_pair("4", "x"),
        make_pair("5", "y"),
        // Modifies(a, v)
        make_pair("10", "count"),
        make_pair("11", "cenX"),
        make_pair("12", "cenY"),
        make_pair("15", "count"),
        make_pair("16", "cenX"),
        make_pair("17", "cenY"),
        make_pair("20", "z"),
        // Modifies(s, v)
        make_pair("14", "count"),
        make_pair("14", "cenX"),
        make_pair("14", "cenY"),
        make_pair("14", "x"),
        make_pair("14", "y"),
        make_pair("14", "z"),
        make_pair("18", "x"),
        make_pair("18", "y"),
        make_pair("18", "z"),
        // Modifies(a, v)
        make_pair("22", "flag"),
        make_pair("23", "cenX"),
        make_pair("26", "count"),
        make_pair("27", "cenY"),
        // Modifies(s, v)
        make_pair("21", "flag"),
        make_pair("21", "cenX"),
        make_pair("21", "cenY"),
        make_pair("21", "x"),
        make_pair("21", "y"),
        make_pair("21", "count"),
        make_pair("24", "x"),
        make_pair("24", "y"),
        make_pair("24", "count"),
        // Modifies(a, v)
        make_pair("28", "normSq"),
        // Modifies(c, v)
        make_pair("2", "count"),
        make_pair("2", "cenX"),
        make_pair("2", "cenY"),
        make_pair("2", "flag"),
        make_pair("2", "normSq"),
        make_pair("2", "x"),
        make_pair("2", "y"),
        make_pair("13", "x"),
        make_pair("13", "y"),
        make_pair("19", "x"),
        make_pair("19", "y"),
        make_pair("25", "x"),
        make_pair("25", "y")
    };
    auto pairs = pkb_read_facade->GetModifiesStatementVariablePairs(STATEMENT);
    for (pair<string, string> pp : expected_modifies_s_pairs) {
      if (!pkb_read_facade->HasModifiesStatementRelationship(pp.first, pp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }

  SECTION("Check that all modifiesP pair are present") {
    vector<pair<string, string>> expected_modifies_p_pairs = {
        make_pair("main", "flag"),
        make_pair("main", "count"),
        make_pair("main", "cenX"),
        make_pair("main", "cenY"),
        make_pair("main", "normSq"),
        make_pair("main", "x"),
        make_pair("main", "y"),
        make_pair("readPoint", "x"),
        make_pair("readPoint", "y"),
        make_pair("computeCentroid", "count"),
        make_pair("computeCentroid", "cenX"),
        make_pair("computeCentroid", "cenY"),
        make_pair("computeCentroid", "x"),
        make_pair("computeCentroid", "y"),
        make_pair("computeCentroid", "flag"),
        make_pair("computeCentroid", "normSq"),
    };
    for (pair<string, string> pp : expected_modifies_p_pairs) {
      if (!pkb_read_facade->HasModifiesProcedureRelationship(pp.first, pp.second)) {
        FAIL();
      }
    }
    SUCCEED();
  }

}