#include "catch.hpp"

#include <memory>

#include "core/model/Expression.h"
#include "ExpressionGeneratorStub/ExpressionGeneratorStub.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Interfaces/PkbWriteFacade.h"
#include "PKB/Pkb.h"
#include "QPS/Qps.h"

TEST_CASE("Uses and Modifies testing") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;
  typedef std::shared_ptr<ExpressionGeneratorStub> ExpressionGeneratorPtr;
  typedef std::vector<std::shared_ptr<Token>> TokenList;

  ExpressionGeneratorPtr egs = std::make_shared<ExpressionGeneratorStub>();
  PkbPtr pkb = std::make_shared<Pkb>();
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);

//  procedure procedure {
//    x411 = 2; -> 1
//    y132 = 2 + 2; -> 2
//    x1c2v3b4 = 2 / 2; -> 3
//    x = y132 * 2; -> 4
//    x = 3 % x; -> 5
  //  x = 2 * 2 + 3 % 1 - x411 / 2; -> 6
//    var = 2; -> 7
//    foo = 4; -> 8
//    bar = foo - 4 + 3 * 2; -> 9
//    X=1; -> 10
//    read bar ; -> 11
//    bar= foo   ; -> 12
//    if (a < bar) then { -> 13
//        while (bar > temp) { -> 14
//          oSCar  = 1 * bar + tmp; -> 15
//          while (tmp / tmp == bar * bar) { -> 16
//            oSCar = X - (bar + foo * chArlie); }} -> 17
//        while (x == 1) { -> 18
//          x = x + 1; -> 19
//          if (foo==0) then { -> 20
//              while (bar== 3){ -> 21
//                print A1pH3; -> 22
//                b = 0; -> 23
//                c = x411    + z + A1pH3; }} -> 24
//          else {
//            while (c>1) { -> 25
//              c = c -1;} -> 26
//            x = x+ 1; }}} -> 27
//    else{
//      a= 2;} -> 28
//    while (foo < bar) { -> 29
//      if (var > 0) then { -> 30
//          var = var + 55555555555555555555555555555; -> 31
//          bar = bar + 88888888888888888888888888888; -> 32
//          var = var - 99999999999999999999999999999; -> 33
//        } else {
//        foo = foo + 1; -> 34
//        var = var - 1; -> 35
//        while = 8; -> 36
//        while (while > 1) { -> 37
//          while = 3 * 2 + while / 2 - 6; -> 38
//          read read; -> 39
//          read print; -> 40
//          then = read; -> 41
//          else = print; -> 42
//          if (while < 0) then { -> 43
//              temp = while * 2 - 2; -> 44
//              read while; -> 45
//              while = foo - bar * var + 3 * 2; -> 46
//              print while; -> 47
//              while = (temp + 2) / 2; -> 48
//            } else {
//            read temp; -> 49
//            print temp; -> 50
//          }
//          print read; -> 51
//          print print; -> 52
//        }
//      }
//    }
//    print var; -> 53
//    print foo; -> 54
//    print bar; -> 55
//  }

  pkb_write->AddProcedure("procedure");
  pkb_write->AddStatementOfAType("1", ASSIGN);
  pkb_write->AddStatementOfAType("2", ASSIGN);
  pkb_write->AddStatementOfAType("3", ASSIGN);
  pkb_write->AddStatementOfAType("4", ASSIGN);
  pkb_write->AddStatementOfAType("5", ASSIGN);
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementOfAType("7", ASSIGN);
  pkb_write->AddStatementOfAType("8", ASSIGN);
  pkb_write->AddStatementOfAType("9", ASSIGN);
  pkb_write->AddStatementOfAType("10", ASSIGN);
  pkb_write->AddStatementOfAType("11", READ);
  pkb_write->AddStatementOfAType("12", ASSIGN);
  pkb_write->AddStatementOfAType("13", IF);
  pkb_write->AddStatementOfAType("14", WHILE);
  pkb_write->AddStatementOfAType("15", ASSIGN);
  pkb_write->AddStatementOfAType("16", WHILE);
  pkb_write->AddStatementOfAType("17", ASSIGN);
  pkb_write->AddStatementOfAType("18", WHILE);
  pkb_write->AddStatementOfAType("19", ASSIGN);
  pkb_write->AddStatementOfAType("20", IF);
  pkb_write->AddStatementOfAType("21",  WHILE);
  pkb_write->AddStatementOfAType("22", PRINT);
  pkb_write->AddStatementOfAType("23", ASSIGN);
  pkb_write->AddStatementOfAType("24", ASSIGN);
  pkb_write->AddStatementOfAType("25", WHILE);
  pkb_write->AddStatementOfAType("26", ASSIGN);
  pkb_write->AddStatementOfAType("27", ASSIGN);
  pkb_write->AddStatementOfAType("28", ASSIGN);
  pkb_write->AddStatementOfAType("29", WHILE);
  pkb_write->AddStatementOfAType("30", IF);
  pkb_write->AddStatementOfAType("31", ASSIGN);
  pkb_write->AddStatementOfAType("32", ASSIGN);
  pkb_write->AddStatementOfAType("33", ASSIGN);
  pkb_write->AddStatementOfAType("34", ASSIGN);
  pkb_write->AddStatementOfAType("35", ASSIGN);
  pkb_write->AddStatementOfAType("36", WHILE);
  pkb_write->AddStatementOfAType("37", WHILE);
  pkb_write->AddStatementOfAType("38", WHILE);
  pkb_write->AddStatementOfAType("39", READ);
  pkb_write->AddStatementOfAType("40", READ);
  pkb_write->AddStatementOfAType("41", ASSIGN);
  pkb_write->AddStatementOfAType("42", ASSIGN);
  pkb_write->AddStatementOfAType("43", IF);
  pkb_write->AddStatementOfAType("44", ASSIGN);
  pkb_write->AddStatementOfAType("45", READ);
  pkb_write->AddStatementOfAType("46", WHILE);
  pkb_write->AddStatementOfAType("47", PRINT);
  pkb_write->AddStatementOfAType("48", WHILE);
  pkb_write->AddStatementOfAType("49", READ);
  pkb_write->AddStatementOfAType("50", PRINT);
  pkb_write->AddStatementOfAType("51", PRINT);
  pkb_write->AddStatementOfAType("52", PRINT);
  pkb_write->AddStatementOfAType("53", PRINT);
  pkb_write->AddStatementOfAType("54", PRINT);
  pkb_write->AddStatementOfAType("55", PRINT);



  pkb_write->AddVariable("x411");
  pkb_write->AddVariable("y132");
  pkb_write->AddVariable("x1c2v3b4");
  pkb_write->AddVariable("x");
  pkb_write->AddVariable("var");
  pkb_write->AddVariable("foo");
  pkb_write->AddVariable("bar");
  pkb_write->AddVariable("X");
  pkb_write->AddConstant("2");
  pkb_write->AddConstant("3");
  pkb_write->AddConstant("1");
  pkb_write->AddConstant("4");

  // a < bar
  TokenList token_list_statement_13{
      make_shared<NameToken>("a"),
      make_shared<RelationalOperatorToken>("<", LT),
      make_shared<NameToken>("bar"),
  };

  pkb_write->AddIfStatementAndCondition("13",
                                        egs->GetExpressionFromInput(token_list_statement_13, "if"));

  // bar > temp
  TokenList token_list_statement_14{
      make_shared<NameToken>("bar"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<NameToken>("temp"),
  };

  pkb_write->AddWhileStatementAndCondition(
      "14", egs->GetExpressionFromInput(token_list_statement_14, "while"));

  // 1 * bar + temp
  TokenList token_list_statement_15{
      make_shared<IntegerToken>("1"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("bar"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("temp"),
  };


  // tmp / tmp == bar * bar
  TokenList token_list_statement_16{
      make_shared<NameToken>("tmp"),
      make_shared<ArithmeticOperatorToken>("/", DIV),
      make_shared<NameToken>("tmp"),
      make_shared<RelationalOperatorToken>("==", DOUBLE_EQUALS),
      make_shared<NameToken>("bar"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("bar"),
  };

  // X - (bar + foo * chArlie)
  TokenList token_list_statement_17{
      make_shared<NameToken>("X"),
      make_shared<RelationalOperatorToken>("-", MINUS),
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("bar"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<NameToken>("foo"),
      make_shared<RelationalOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("chArlie"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
  };

  // x == 1
  TokenList token_list_statement_18{
      make_shared<NameToken>("x"),
      make_shared<RelationalOperatorToken>("==", DOUBLE_EQUALS),
      make_shared<IntegerToken>("1"),
  };

  // x + 1
  TokenList token_list_statement_19{
      make_shared<NameToken>("x"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
  };

  // foo == 0
  TokenList token_list_statement_20{
      make_shared<NameToken>("foo"),
      make_shared<RelationalOperatorToken>("==", DOUBLE_EQUALS),
      make_shared<IntegerToken>("0"),
  };

  // bar == 3
  TokenList token_list_statement_21{
      make_shared<NameToken>("bar"),
      make_shared<RelationalOperatorToken>("==", DOUBLE_EQUALS),
      make_shared<IntegerToken>("3"),
  };

  // A1pH3
  TokenList token_list_statement_22{
      make_shared<NameToken>("A1pH3"),
  };

  // 0
  TokenList token_list_statement_23{
      make_shared<IntegerToken>("0"),
  };

  // x411 + z + A1pH3
  TokenList token_list_statement_24{
      make_shared<NameToken>("x411"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<NameToken>("z"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<NameToken>("A1pH3"),
  };

  // c > 1
  TokenList token_list_statement_25{
      make_shared<NameToken>("c"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<IntegerToken>("1"),
  };

  // c - 1
  TokenList token_list_statement_26{
      make_shared<NameToken>("c"),
      make_shared<RelationalOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
  };

  // x + 1
  TokenList token_list_statement_27{
      make_shared<NameToken>("x"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
  };

  // 2
  TokenList token_list_statement_28{
      make_shared<IntegerToken>("2"),
  };

  // foo < bar
  TokenList token_list_statement_29{
      make_shared<NameToken>("foo"),
      make_shared<RelationalOperatorToken>("<", LT),
      make_shared<NameToken>("bar"),
  };

  // var > 0
  TokenList token_list_statement_30{
      make_shared<NameToken>("var"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<IntegerToken>("0"),
  };

  // var + 55555555555555555555555555555
  TokenList token_list_statement_31{
      make_shared<NameToken>("var"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("55555555555555555555555555555"),
  };

  // bar + 88888888888888888888888888888
  TokenList token_list_statement_32{
      make_shared<NameToken>("bar"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("88888888888888888888888888888"),
  };

  // var - 99999999999999999999999999999
  TokenList token_list_statement_33{
      make_shared<NameToken>("var"),
      make_shared<RelationalOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("99999999999999999999999999999"),
  };

  // foo + 1
  TokenList token_list_statement_34{
      make_shared<NameToken>("foo"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
  };

  // var - 1
  TokenList token_list_statement_35{
      make_shared<NameToken>("var"),
      make_shared<RelationalOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
  };

  // 8
  TokenList token_list_statement_36{
      make_shared<IntegerToken>("8"),
  };

  // while > 1
  TokenList token_list_statement_37{
      make_shared<NameToken>("while"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<IntegerToken>("1"),
  };

  // 3 * 2 + while / 2 - 6
  TokenList token_list_statement_38{
      make_shared<IntegerToken>("3"),
      make_shared<RelationalOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("2"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<NameToken>("while"),
      make_shared<RelationalOperatorToken>("/", DIV),
      make_shared<IntegerToken>("2"),
      make_shared<RelationalOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("6"),
  };

  // read
  TokenList token_list_statement_39{
      make_shared<NameToken>("read"),
  };

  // print
  TokenList token_list_statement_40{
      make_shared<NameToken>("print"),
  };

  // read
  TokenList token_list_statement_41{
      make_shared<NameToken>("read"),
  };

  // print
  TokenList token_list_statement_42{
      make_shared<NameToken>("print"),
  };

  // while < 0
  TokenList token_list_statement_43{
      make_shared<NameToken>("while"),
      make_shared<RelationalOperatorToken>("<", LT),
      make_shared<IntegerToken>("0"),
  };

  // while * 2 - 2
  TokenList token_list_statement_44{
      make_shared<NameToken>("while"),
      make_shared<RelationalOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("2"),
      make_shared<RelationalOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("2"),
  };

  // while
  TokenList token_list_statement_45{
      make_shared<NameToken>("while"),
  };

  // foo - bar * var + 3 * 2
  TokenList token_list_statement_46{
      make_shared<NameToken>("foo"),
      make_shared<RelationalOperatorToken>("-", MINUS),
      make_shared<NameToken>("bar"),
      make_shared<RelationalOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("var"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("3"),
      make_shared<RelationalOperatorToken>("*", MULTIPLY),
      make_shared<IntegerToken>("2"),
  };

  // while
  TokenList token_list_statement_47{
      make_shared<NameToken>("while"),
  };

  // (temp + 2) / 2
  TokenList token_list_statement_48{
      make_shared<PunctuationToken>("(", LEFT_PARENTHESIS),
      make_shared<NameToken>("temp"),
      make_shared<RelationalOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2"),
      make_shared<PunctuationToken>(")", RIGHT_PARENTHESIS),
      make_shared<RelationalOperatorToken>("/", DIV),
      make_shared<IntegerToken>("2"),
  };

  // temp
  TokenList token_list_statement_49{
      make_shared<NameToken>("temp"),
  };

  // temp
  TokenList token_list_statement_50{
      make_shared<NameToken>("temp"),
  };

  // read
  TokenList token_list_statement_51{
      make_shared<NameToken>("read"),
  };

  // print
  TokenList token_list_statement_52{
      make_shared<NameToken>("print"),
  };




  pkb_write->AddAssignmentStatementAndExpression(
      "15", egs->GetExpressionFromInput(token_list_statement_15, "assign"));
  pkb_write->AddStatementModifyingVariable("15", "oSCar");
  pkb_write->AddStatementModifyingVariable("1", "x411");
  pkb_write->AddStatementModifyingVariable("2", "y132");
  pkb_write->AddStatementModifyingVariable("3", "x1c2v3b4");
  pkb_write->AddStatementModifyingVariable("4", "x");
  pkb_write->AddStatementModifyingVariable("5", "x");
  pkb_write->AddStatementModifyingVariable("6", "x");
  pkb_write->AddStatementModifyingVariable("7", "var");
  pkb_write->AddStatementModifyingVariable("8", "foo");
  pkb_write->AddStatementModifyingVariable("9", "bar");
  pkb_write->AddStatementModifyingVariable("10", "X");
  pkb_write->AddStatementModifyingVariable("11", "bar");
  pkb_write->AddStatementModifyingVariable("12", "bar");
  pkb_write->AddProcedureModifyingVariable("procedure", "x411");
  pkb_write->AddProcedureModifyingVariable("procedure", "y132");
  pkb_write->AddProcedureModifyingVariable("procedure", "x1c2v3b4");
  pkb_write->AddProcedureModifyingVariable("procedure", "x");
  pkb_write->AddProcedureModifyingVariable("procedure", "var");
  pkb_write->AddProcedureModifyingVariable("procedure", "foo");
  pkb_write->AddProcedureModifyingVariable("procedure", "bar");
  pkb_write->AddProcedureModifyingVariable("procedure", "X");
  pkb_write->AddProcedureModifyingVariable("procedure", "oSCar");

  pkb_write->AddStatementUsingVariable("4", "y132");
  pkb_write->AddStatementUsingVariable("5", "x");
  pkb_write->AddStatementUsingVariable("6", "x411");
  pkb_write->AddStatementUsingVariable("9", "foo");
  pkb_write->AddStatementUsingVariable("12", "foo");
  pkb_write->AddProcedureUsingVariable("procedure", "y132");
  pkb_write->AddProcedureUsingVariable("procedure", "x");
  pkb_write->AddProcedureUsingVariable("procedure", "x411");
  pkb_write->AddProcedureUsingVariable("procedure", "foo");
  pkb_write->AddProcedureUsingVariable("procedure", "a");
  pkb_write->AddProcedureUsingVariable("procedure", "bar");
  pkb_write->AddProcedureUsingVariable("procedure", "temp");

  SECTION("Test statements - basic") {
    QueryString query = "stmt s; Select s";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "2", "20", "21",
                                 "22", "23", "24", "25", "26", "27", "28", "29", "3", "30", "31", "32", "33", "34",
                                 "35", "36", "37", "38", "39", "4", "40", "41", "42", "43", "44", "45", "46", "47",
                                 "48", "49", "5", "50", "51", "52", "53", "54", "55", "6", "7", "8", "9"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test variables - basic") {
    QueryString query = "variable v; Select v";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"X", "a", "bar", "foo", "temp", "var", "x", "x1c2v3b4", "x411", "y132"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses with statement and wildcard") {
    QueryString query = "stmt s; Select s such that Modifies(s, _)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1", "10", "11", "12", "15", "2", "3", "4", "5", "6", "7", "8", "9"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses(proc, 'chArlie')") {
    QueryString query = R"(variable Select; procedure proc; Select proc such that Uses(proc, "chArlie"))";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses(proc, v) - select v") {
    QueryString query = R"(variable var; procedure proc; Select var such that Uses(proc, var))";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"a", "bar", "foo", "temp", "x", "x411", "y132"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses(s, 'X'") {
    QueryString query = R"(stmt stmt; Select stmt such that Uses(stmt, "X"))";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies('procedure', _)") {
    QueryString query = R"(Select BOOLEAN such that Modifies("procedure", _))";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies('procedure', 'x')") {
    QueryString query = R"(Select BOOLEAN such that Modifies("procedure", "x"))";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies('procedure', 'x')") {
    QueryString query = R"(variable v; Select BOOLEAN such that Modifies("procedure", "x"))";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies('procedure', proc)") {
    QueryString query = "procedure Modifies; Select BOOLEAN such that Modifies(\"procedure\", Modifies)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"SemanticError"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies('procedure', v)") {
    QueryString query = "variable Select; Select Select such that Modifies(\"procedure\", Select)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"X", "bar", "foo", "oSCar", "var", "x", "x1c2v3b4", "x411", "y132"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("SyntaxError - Modifies('procedure', 1)") {
    QueryString query = "Select BOOLEAN such that Modifies(\"procedure\", 1)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"SyntaxError"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies(proc, v) - select proc") {
    QueryString query = "variable Modifies; procedure such; Select such such that Modifies(such, Modifies)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"procedure"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies(proc, 'x1c2v3b4')") {
    QueryString query = "variable Select; procedure proc; Select proc such that Modifies(proc, \"x1c2v3b4\")";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"procedure"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies(proc, v) - select v") {
    QueryString query = "variable var; procedure proc; Select var such that Modifies(proc, var)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"X", "bar", "foo", "oSCar", "var", "x", "x1c2v3b4", "x411", "y132"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies(s, 'temp')") {
    QueryString query = "stmt s; Select s such that Modifies(s, \"temp\")";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies(s, v)") {
    QueryString query = "stmt s; variable var; Select <s, var> such that Modifies(s, var)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1 x411", "10 X", "11 bar", "12 bar", "15 oSCar", "2 y132", "3 x1c2v3b4", "4 x", "5 x",
                                 "6 x", "7 var", "8 foo", "9 bar"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modifies(proc, v)") {
    QueryString query = "procedure proc; variable var; Select <proc, var> such that Modifies(proc, var)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"procedure X", "procedure bar", "procedure foo", "procedure oSCar",
                                 "procedure var", "procedure x", "procedure x1c2v3b4", "procedure x411",
                                 "procedure y132"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses(s, v)") {
    QueryString query = "stmt s; variable var; Select <s, var> such that Uses(s, var)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{
        "12 foo", "13 a", "13 bar", "14 bar", "14 temp", "15 bar", "15 temp", "4 y132", "5 x", "6 x411", "9 foo"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses(proc, v)") {
    QueryString query = "procedure proc; variable var; Select <proc, var> such that Uses(proc, var)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"procedure a", "procedure bar", "procedure foo", "procedure temp", "procedure x",
                                 "procedure x411", "procedure y132"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses - (int, identifier) - Out of Bound") {
    QueryString query = "stmt s; Select BOOLEAN such that Uses(50000000000, \"x\")";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Semantic Error - Uses - (int, synonym)") {
    QueryString query = "stmt s; Select BOOLEAN such that Uses(50000000000, s)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"SemanticError"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Uses - (int, wildcard) - Out of Bound") {
    QueryString query = "stmt s; Select BOOLEAN such that Uses(50000000000, _)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modify - (int, identifier) - Out of Bound") {
    QueryString query = "stmt s; Select BOOLEAN such that Modifies(50000000000, \"x\")";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  // check this test case
  SECTION("Semantic Error - (int, synonym) - Modify") {
    QueryString query = "stmt s; Select BOOLEAN such that Modifies(50000000000, s)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"SemanticError"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Modify - (int, wildcard) - Out of Bound") {
    QueryString query = "Select BOOLEAN such that Modifies(500000000000, _)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}
TEST_CASE("Check if QPS works with Pkb for basic operations") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);

  /*
   *  procedure test {
   * 1  read x;
   * 2  y = x;
   * 3  if (x == 0) then {
   * 4    print x;}
   *    else {
   * 5    while (x > 0) {
   * 6      x = x - 1;}}
   * 7 print test
   * }
   */
  pkb_write->AddProcedure("test");

  pkb_write->AddStatementOfAType("1", READ);
  pkb_write->AddStatementOfAType("2", ASSIGN);
  pkb_write->AddStatementOfAType("3", IF);
  pkb_write->AddStatementOfAType("4", PRINT);
  pkb_write->AddStatementOfAType("5", WHILE);
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementOfAType("7", PRINT);

  pkb_write->AddVariable("x");
  pkb_write->AddVariable("y");
  pkb_write->AddVariable("test");
  pkb_write->AddConstant("0");
  pkb_write->AddConstant("1");

  pkb_write->AddFollowsRelation("1", "2");
  pkb_write->AddFollowsRelation("2", "3");

  pkb_write->AddFollowsStarRelation();

  pkb_write->AddParentRelation("3", "4");
  pkb_write->AddParentRelation("3", "5");
  pkb_write->AddParentRelation("5", "6");

  pkb_write->AddParentStarRelation();

  pkb_write->AddStatementModifyingVariable("1", "x");
  pkb_write->AddStatementModifyingVariable("2", "y");
  pkb_write->AddStatementModifyingVariable("3", "x");
  pkb_write->AddStatementModifyingVariable("5", "x");
  pkb_write->AddStatementModifyingVariable("6", "x");

  pkb_write->AddStatementUsingVariable("2", "x");
  pkb_write->AddStatementUsingVariable("3", "x");
  pkb_write->AddStatementUsingVariable("4", "x");
  pkb_write->AddStatementUsingVariable("5", "x");
  pkb_write->AddStatementUsingVariable("6", "x");
  pkb_write->AddStatementUsingVariable("7", "test");

  SECTION("Test basic get relationship -- with attr_ref = attr_ref -- both special case") {
    QueryString query = "print p; read r; Select p with p.varName = r.varName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- both special case (swap args)") {
    QueryString query = "print p; read r; Select p with r.varName = p.varName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- returns result") {
    QueryString
        query = "stmt s; constant c; Select s.stmt# with s.stmt# = c.value";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- returns result (swap args)") {
    QueryString
        query = "stmt s; constant c; Select s.stmt# with c.value = s.stmt#";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName") {
    QueryString query =
        "print pn; procedure proc; Select pn with pn.varName = proc.procName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- selecting for varName -- swap args") {
    QueryString query =
        "print pn; procedure proc; Select pn with proc.procName = pn.varName";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"7"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = attr_ref -- does not return result") {
    QueryString query = "print p; read r; Select r with p.stmt# = r.stmt#";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = int -- select varName from print") {
    QueryString query = "print p; Select p.stmt# with p.varName=\"x\"";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic  get relationship -- with attr_ref = int -- return result") {
    QueryString query = "print p; Select p with 4=p.stmt#";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4"};
    REQUIRE(results == expected_results);
  }

  SECTION(
      "Test basic get relationship -- with attr_ref = int -- select varName from print") {
    QueryString query = "print p; Select p.varName with p.stmt#=4";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"x"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic  get relationship -- with attr_ref = int -- return none ") {
    QueryString query = "print p; Select p with p.stmt#=1";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get procedure") {
    QueryString query = "procedure p; Select p";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"test"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get variable") {
    QueryString query = "variable v; Select v";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"test", "x", "y"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get procedure") {
    QueryString query = "constant c; Select c";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"0", "1"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get statements") {
    QueryString query = "stmt s; Select s";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1", "2", "3", "4", "5", "6", "7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get assign statements") {
    QueryString query = "assign s; Select s";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"2", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get read statements") {
    QueryString query = "read r; Select r";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get print statements") {
    QueryString query = "print p; Select p";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"4", "7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get if statements") {
    QueryString query = "if ifs; Select ifs";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"3"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get while statements") {
    QueryString query = "while w; Select w";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"5"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Follows") {
    QueryString query = "stmt s; Select s such that Follows(s, 2)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Follows*") {
    QueryString query = "stmt s; Select s such that Follows*(s, 2)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Parent") {
    QueryString query = "stmt s; Select s such that Parent(s, 4)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"3"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Parent*") {
    QueryString query = "stmt s; Select s such that Parent*(s, 4)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"3"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Uses") {
    QueryString query = "variable v; Select v such that Uses(2, v)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"x"};
    REQUIRE(results == expected_results);
  }

  SECTION("Test basic get relationship - Modifies") {
    QueryString query = "variable v; Select v such that Modifies(1, v)";
    QueryResult results;

    Qps::ProcessQuery(query, results, pkb_read);

    QueryResult expected_results{"x"};
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Test case of empty relationship stores") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  pkb_write->AddProcedure("test");

  pkb_write->AddStatementOfAType("1", READ);
  pkb_write->AddStatementOfAType("2", ASSIGN);
  pkb_write->AddStatementOfAType("3", IF);
  pkb_write->AddStatementOfAType("4", PRINT);
  pkb_write->AddStatementOfAType("5", WHILE);
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementOfAType("7", PRINT);
  pkb_write->AddStatementOfAType("8", CALL);

  pkb_write->AddVariable("x");
  pkb_write->AddVariable("y");
  pkb_write->AddVariable("test");

  pkb_write->AddConstant("0");
  pkb_write->AddConstant("1");

  SECTION("Calls(_,_)") {
    QueryString query = "procedure p; Select p.procName such that Calls(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,_)") {
    QueryString query = "procedure p; Select p such that Calls(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,PROC-SYN)") {
    QueryString query = "procedure p; Select p such that Calls(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,_)") {
    QueryString query = "procedure p; Select p.procName such that Calls*(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,_)") {
    QueryString query = "procedure p; Select p such that Calls*(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,PROC-SYN)") {
    QueryString query = "procedure p; Select p such that Calls*(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Follows(_,_)") {
    QueryString query = "constant c; Select c.value such that Follows(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Parent(_,_)") {
    QueryString query = "assign a; Select a.stmt# such that Parent(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Calls") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  pkb_write->AddProcedure("proc1");
  pkb_write->AddProcedure("proc2");
  pkb_write->AddProcedure("proc3");
  pkb_write->AddProcedure("proc4");
  pkb_write->AddProcedure("proc5");
  pkb_write->AddProcedure("proc6");
  pkb_write->AddProcedure("proc7");
  pkb_write->AddProcedure("proc8");

  pkb_write->AddCallsRelation("proc1", "proc2");
  pkb_write->AddCallsRelation("proc1", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc5");
  pkb_write->AddCallsRelation("proc3", "proc4");
  pkb_write->AddCallsRelation("proc5", "proc6");
  pkb_write->AddCallsRelation("proc6", "proc7");


  SECTION("Calls Multiclause -- test transitive") {
    // Select procedures that call procedures that are callers
    QueryString query =
        "procedure p,p1,p2,p3,p4; "
        "Select <p1,p2,p3.procName,p4> such that Calls(p1,p2) and Calls(p2,p3) and Calls(p3,p4)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc1 proc2 proc3 proc4", "proc1 proc2 proc5 proc6",
                         "proc2 proc5 proc6 proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,_) is true") {
    QueryString query = "procedure p; Select p.procName such that Calls(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is true") {
    QueryString
        query = "procedure p; Select <p.procName> such that Calls(_,\"proc5\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,IDENT) is false") {
    QueryString query =
        "procedure p; Select <p.procName> such that Calls (_,\"proc1\"  )   ";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is true") {
    QueryString query =
        "procedure p; procedure q       ; Select   <p. procName, p .procName > such that Calls  (\"proc1\",   _)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4",
         "proc5 proc5", "proc6 proc6", "proc7 proc7",
         "proc8 proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,_) is false") {
    QueryString query =
        "procedure p; procedure q; Select <p.procName, q.procName> such that Calls(\"proc8\",_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is true") {
    QueryString
        query = R"(procedure p; Select p such that Calls("proc1","proc2"))";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,IDENT) is false") {
    QueryString query =
        R"(procedure p; Select p .procName such that Calls("proc3    ","       proc2"))";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,_) has result") {
    QueryString query = "procedure p; Select p. procName such that Calls(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls(p, \"      proc2       \")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc1"};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,IDENT) has no result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls(p, \"proc8\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(PROC-SYN,PROC-SYN) has result") {
    QueryString query =
        "procedure p; procedure q; Select p.procName such that Calls(p,q) with q.procName = \"proc6\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc5"};
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls(PROC-SYN,PROC-SYN) has no result") {
    QueryString query =
        "procedure p; procedure q; Select p.procName such that Calls(p,q) with p.procName = \"proc4\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(_,PROC-SYN) has result") {
    QueryString query = "procedure p; Select p.procName such that Calls(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(IDENT,PROC-SYN) has result") {
    QueryString
        query = "procedure p; Select p.procName such that Calls(\"proc2\",p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc3", "proc5"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause") {
    // Select procedures that call procedures that are callers
    QueryString query =
        "procedure p,p1,p2,p3,p4; Select p1 such that Calls(p1,p2) and Calls(p2,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc1", "proc2", "proc5"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Calls*") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  pkb_write->AddProcedure("proc1");
  pkb_write->AddProcedure("proc2");
  pkb_write->AddProcedure("proc3");
  pkb_write->AddProcedure("proc4");
  pkb_write->AddProcedure("proc5");
  pkb_write->AddProcedure("proc6");
  pkb_write->AddProcedure("proc7");
  pkb_write->AddProcedure("proc8");

  pkb_write->AddCallsRelation("proc1", "proc2");
  pkb_write->AddCallsRelation("proc1", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc3");
  pkb_write->AddCallsRelation("proc2", "proc5");
  pkb_write->AddCallsRelation("proc3", "proc4");
  pkb_write->AddCallsRelation("proc5", "proc6");
  pkb_write->AddCallsRelation("proc6", "proc7");

  pkb_write->AddCallsStarRelation();

  SECTION("Calls*(p,p) should have no result") {
    QueryString query = "procedure p; Select p.procName such that Calls*(p,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls(p,p) should have no result") {
    QueryString query = "procedure p; Select p.procName such that Calls(p,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls('proc1','proc1') should have no result") {
    QueryString query = "procedure p; Select p.procName such that Calls(\"proc1\",\"proc1\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*('proc1','proc1') should have no result") {
    QueryString query = "procedure p; Select p.procName such that Calls*(\"proc1\",\"proc1\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,_) is true") {
    QueryString query = "procedure p; Select p.procName such that Calls*(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is true") {
    QueryString query =
        "procedure p; Select <p.procName> such that Calls*(_,\"proc4\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,IDENT) is false") {
    QueryString query =
        "procedure p; Select <p.procName> such that Calls*(_,\"proc8\"  )   ";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is true") {
    QueryString query =
        "procedure p; procedure q       ; Select   <p. procName, p .procName > such that Calls*  (\"proc2\",   _)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc1", "proc2 proc2", "proc3 proc3", "proc4 proc4",
         "proc5 proc5", "proc6 proc6", "proc7 proc7",
         "proc8 proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,_) is false") {
    QueryString query =
        "procedure p; procedure q; Select <p.procName, q.procName> such that Calls*(\"proc7\",_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is true") {
    QueryString
        query = "procedure p; Select p such that Calls*(\"proc2\",\"proc7\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1", "proc2", "proc3", "proc4", "proc5", "proc6", "proc7",
         "proc8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,IDENT) is false") {
    QueryString query =
        "procedure p; Select p .procName such that Calls*(\"proc4  \",\"       proc7\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,_) has result") {
    QueryString query = "procedure p; Select p. procName such that Calls*(p,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc1", "proc2", "proc3", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls*(p, \"      proc7       \")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc1", "proc2", "proc5", "proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,IDENT) has no result") {
    QueryString query =
        "procedure p; Select p  . procName such that Calls*(p, \"proc8\")";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(PROC-SYN,PROC-SYN) has result") {
    QueryString query =
        "procedure p; procedure q; Select q.procName such that Calls*(p,q) with p.procName = \"proc2\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Query with Calls*(PROC-SYN,PROC-SYN) has no result") {
    QueryString query =
        "procedure p; procedure q; Select p.procName such that Calls*(p,q) with q.procName = \"proc1\"";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(_,PROC-SYN) has result") {
    QueryString query = "procedure p; Select p.procName such that Calls*(_,p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"proc2", "proc3", "proc4", "proc5", "proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls*(IDENT,PROC-SYN) has result") {
    QueryString
        query = "procedure p; Select p.procName such that Calls*(\"proc5\",p)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"proc6", "proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- indirect calls only") {
    QueryString query =
        "procedure p,p1,p2,p3,p4; Select <p1,p3> such that Calls(p1,p2) and Calls*(p2,p3)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc3", "proc1 proc4", "proc1 proc5", "proc1 proc6",
         "proc1 proc7", "proc2 proc4", "proc2 proc6",
         "proc2 proc7", "proc5 proc7"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Calls Multiclause -- test transitive") {
    QueryString query =
        "procedure p,p1,p2,p3,p4; Select <p1,p3.procName> such that Calls(p1,p2) and Calls*(p2,p3) and Calls*(p3,p4)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results
        {"proc1 proc3", "proc1 proc5", "proc1 proc6", "proc2 proc6"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration testing for Next - Basic") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;
  typedef std::shared_ptr<Cfg> CfgPtr;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  CfgPtr cfg = std::make_shared<Cfg>();

  CfgNodePtr node1 = std::make_shared<CfgNode>();
  node1->AddStmt(1);
  cfg->AddStmtCfg(1, node1);
  node1->AddStmt(2);
  cfg->AddStmtCfg(2, node1);

  CfgNodePtr node2 = std::make_shared<CfgNode>();
  node2->AddStmt(3);
  cfg->AddStmtCfg(3, node2);
  node2->AddStmt(4);
  cfg->AddStmtCfg(4, node2);

  CfgNodePtr node3 = std::make_shared<CfgNode>();
  node3->AddStmt(5);
  cfg->AddStmtCfg(5, node3);
  node3->AddStmt(6);
  cfg->AddStmtCfg(6, node3);

  pkb_write->AddStatementOfAType("1", ASSIGN);
  pkb_write->AddStatementOfAType("2", IF);
  pkb_write->AddStatementOfAType("3", CALL);
  pkb_write->AddStatementOfAType("4", ASSIGN);
  pkb_write->AddStatementOfAType("5", CALL);
  pkb_write->AddStatementOfAType("6", READ);

  node1->AddTransition(true, node2);
  node1->AddTransition(false, node3);

  cfg->AddProcCfg("main", node1);

  pkb_write->AddCfg(cfg);

  SECTION("Next(_,_) is true") {
    QueryString query = "stmt s; Select s.stmt# such that Next(_,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_,IDENT) is true") {
    QueryString query = "stmt s; Select <s.stmt#> such that Next(_,2)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_,IDENT) is false") {
    QueryString query = "stmt s; Select <s.stmt#> such that Next (_,1 )";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, _) is true") {
    QueryString query =
        "stmt s1; stmt s2; Select <s1.stmt#, s1.stmt#> such that Next (1,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult
        expected_results{"1 1", "2 2", "3 3", "4 4", "5 5", "6 6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, _) is false") {
    QueryString query =
        "stmt s1; stmt s2; Select <s1.stmt#, s2.stmt#> such that Next (6,_)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT,IDENT) is true") {
    QueryString query = "stmt s; Select s such that Next(1,2)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"1", "2", "3", "4", "5", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT,IDENT) is false") {
    QueryString query = "stmt s; Select s .stmt# such that Next(3,2)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    REQUIRE(results == expected_results);
  }
}

// "procedure main {\n"
// "  while (x==1) {"
// "    flag = 1;"
// "    while( flag == 1 ) {"
// "        flag = 2;"
// "    }"
// "    count = count + 1;"
// "  } "
// "  y = 20;"
// "  while (x==1) {"
// "    flag = 1;"
// "    while( flag == 1 ) {"
// "        flag = 2;"
// "    }"
// "  }"
// "  count = count - 1; "
// "}\n";
TEST_CASE("Integration testing for Next API - Complex") {
  typedef std::shared_ptr<Pkb> PkbPtr;
  typedef std::shared_ptr<PkbWriteFacade> PkbWriteFacadePtr;
  typedef std::shared_ptr<PkbReadFacade> PkbReadFacadePtr;
  typedef std::string QueryString;
  typedef std::list<QueryString> QueryResult;
  typedef std::shared_ptr<Cfg> CfgPtr;
  typedef std::shared_ptr<CfgNode> CfgNodePtr;

  PkbPtr pkb = std::make_shared<Pkb>();
  PkbReadFacadePtr pkb_read = std::make_shared<PkbReadFacade>(*pkb);
  PkbWriteFacadePtr pkb_write = std::make_shared<PkbWriteFacade>(*pkb);

  CfgPtr cfg = std::make_shared<Cfg>();

  CfgNodePtr node1 = std::make_shared<CfgNode>();
  CfgNodePtr node2 = std::make_shared<CfgNode>();
  CfgNodePtr node3 = std::make_shared<CfgNode>();
  CfgNodePtr node4 = std::make_shared<CfgNode>();
  CfgNodePtr node5 = std::make_shared<CfgNode>();
  CfgNodePtr node6 = std::make_shared<CfgNode>();
  CfgNodePtr node7 = std::make_shared<CfgNode>();
  CfgNodePtr node8 = std::make_shared<CfgNode>();
  CfgNodePtr node9 = std::make_shared<CfgNode>();
  CfgNodePtr node10 = std::make_shared<CfgNode>();
  CfgNodePtr node11 = std::make_shared<CfgNode>();
  CfgNodePtr node12 = std::make_shared<CfgNode>();

  node1->AddStmt(1);
  cfg->AddStmtCfg(1, node1);
  node2->AddStmt(2);
  cfg->AddStmtCfg(2, node2);
  node3->AddStmt(3);
  cfg->AddStmtCfg(3, node3);
  node4->AddStmt(4);
  cfg->AddStmtCfg(4, node4);
  node5->AddStmt(5);
  cfg->AddStmtCfg(5, node5);
  node6->AddStmt(6);
  cfg->AddStmtCfg(6, node6);
  node7->AddStmt(7);
  cfg->AddStmtCfg(7, node7);
  node8->AddStmt(8);
  cfg->AddStmtCfg(8, node8);
  node9->AddStmt(9);
  cfg->AddStmtCfg(9, node9);
  node10->AddStmt(10);
  cfg->AddStmtCfg(10, node10);
  node11->AddStmt(11);
  cfg->AddStmtCfg(11, node11);
  node12->AddStmt(12);
  cfg->AddStmtCfg(12, node12);

  pkb_write->AddStatementOfAType("1", ASSIGN);
  pkb_write->AddStatementOfAType("2", WHILE);
  pkb_write->AddStatementOfAType("3", ASSIGN);
  pkb_write->AddStatementOfAType("4", WHILE);
  pkb_write->AddStatementOfAType("5", ASSIGN);
  pkb_write->AddStatementOfAType("6", ASSIGN);
  pkb_write->AddStatementOfAType("7", READ);
  pkb_write->AddStatementOfAType("8", WHILE);
  pkb_write->AddStatementOfAType("9", ASSIGN);
  pkb_write->AddStatementOfAType("10", WHILE);
  pkb_write->AddStatementOfAType("11", ASSIGN);
  pkb_write->AddStatementOfAType("12", ASSIGN);

  cfg->AddProcCfg("main", node1);

  node1->AddTransition(true, node2);
  node2->AddTransition(true, node3);
  node2->AddTransition(false, node7);
  node3->AddTransition(true, node4);
  node4->AddTransition(true, node5);
  node4->AddTransition(false, node6);
  node5->AddTransition(true, node4);
  node6->AddTransition(true, node2);
  node7->AddTransition(true, node8);
  node8->AddTransition(true, node9);
  node8->AddTransition(false, node12);
  node9->AddTransition(true, node10);
  node10->AddTransition(false, node8);
  node10->AddTransition(true, node11);
  node11->AddTransition(true, node10);

  pkb_write->AddCfg(cfg);

  SECTION("Test basic get relationship - Next") {
    QueryString query = "stmt s; Select s such that Next(3, s)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"4"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(_, WHILE-SYN) has result") {
    QueryString query = "while w; Select w such that Next(_, w)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"10", "2", "4", "8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(WHILE-SYN, IDENT) has a result") {
    QueryString query = "while w; assign a; Select w such that Next(w, a)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{"10", "2", "4", "8"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Next(IDENT, WHILE-SYN) returns false") {
    QueryString query = "while w; Select w such that Next(2, w)";
    QueryResult results;
    Qps::ProcessQuery(query, results, pkb_read);
    QueryResult expected_results{};
    results.sort();
    REQUIRE(results == expected_results);
  }
}

TEST_CASE("Integration Testing for Affects API - Basic") {
  std::shared_ptr<Pkb> pkb_ = std::make_shared<Pkb>();
  std::shared_ptr<PkbReadFacade>
      pkb_read_facade_ = std::make_shared<PkbReadFacade>(*pkb_);
  std::shared_ptr<PkbWriteFacade>
      pkb_write_facade_ = std::make_shared<PkbWriteFacade>(*pkb_);
  typedef std::shared_ptr<ExpressionGeneratorStub> ExpressionGeneratorPtr;

  ExpressionGeneratorPtr egs = std::make_shared<ExpressionGeneratorStub>();
  std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>();
  typedef std::vector<std::shared_ptr<Token>> TokenList;

  std::shared_ptr<CfgNode> node1 = std::make_shared<CfgNode>();
  node1->AddStmt(1);
  cfg->AddStmtCfg(1, node1);
  node1->AddStmt(2);
  cfg->AddStmtCfg(2, node1);

  std::shared_ptr<CfgNode> node2 = std::make_shared<CfgNode>();
  node2->AddStmt(3);
  cfg->AddStmtCfg(3, node2);

  std::shared_ptr<CfgNode> node3 = std::make_shared<CfgNode>();
  node3->AddStmt(4);
  cfg->AddStmtCfg(4, node3);
  node3->AddStmt(5);
  cfg->AddStmtCfg(5, node3);
  node3->AddStmt(6);
  cfg->AddStmtCfg(6, node3);

  std::shared_ptr<CfgNode> node4 = std::make_shared<CfgNode>();
  node4->AddStmt(7);
  cfg->AddStmtCfg(7, node4);

  std::shared_ptr<CfgNode> node5 = std::make_shared<CfgNode>();
  node5->AddStmt(8);
  cfg->AddStmtCfg(8, node5);

  std::shared_ptr<CfgNode> node6 = std::make_shared<CfgNode>();
  node6->AddStmt(9);
  cfg->AddStmtCfg(9, node6);

  std::shared_ptr<CfgNode> node7 = std::make_shared<CfgNode>();
  node7->AddStmt(10);
  cfg->AddStmtCfg(10, node7);
  node7->AddStmt(11);
  cfg->AddStmtCfg(11, node7);
  node7->AddStmt(12);
  cfg->AddStmtCfg(12, node7);

  // 0
  TokenList token_list_statement_1{
      make_shared<IntegerToken>("0"),
  };

  pkb_write_facade_->AddStatementOfAType("1", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("1", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "1", egs->GetExpressionFromInput(
          token_list_statement_1, "assign"));

  // 5
  TokenList token_list_statement_2{
      make_shared<IntegerToken>("5"),
  };

  pkb_write_facade_->AddStatementOfAType("2", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("2", "i");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "2", egs->GetExpressionFromInput(
          token_list_statement_2, "assign"));

  // i > 0
  TokenList token_list_statement_3{
      make_shared<NameToken>("i"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<IntegerToken>("0"),
  };

  pkb_write_facade_->AddStatementOfAType("3", WHILE);
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "4", egs->GetExpressionFromInput(
          token_list_statement_3, "while"));

  // x + 2 * y
  TokenList token_list_statement_4{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("y"),
  };

  pkb_write_facade_->AddStatementOfAType("4", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("4", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "4", egs->GetExpressionFromInput(
          token_list_statement_4, "assign"));

  pkb_write_facade_->AddStatementOfAType("5", CALL);

  // i - 1
  TokenList token_list_statement_6{
      make_shared<NameToken>("i"),
      make_shared<ArithmeticOperatorToken>("-", MINUS),
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("6", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("6", "i");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "6", egs->GetExpressionFromInput(
          token_list_statement_6, "assign"));

  // x > 1
  TokenList token_list_statement_7{
      make_shared<NameToken>("3"),
      make_shared<RelationalOperatorToken>(">", GT),
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("7", IF);
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "7", egs->GetExpressionFromInput(
          token_list_statement_7, "if"));

  // x + 1
  TokenList token_list_statement_8{
      make_shared<NameToken>("3"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("8", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("8", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "8", egs->GetExpressionFromInput(
          token_list_statement_8, "assign"));

  // 1
  TokenList token_list_statement_9{
      make_shared<IntegerToken>("1"),
  };

  pkb_write_facade_->AddStatementOfAType("9", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("9", "z");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "9", egs->GetExpressionFromInput(
          token_list_statement_9, "assign"));

  // z + x + i
  TokenList token_list_statement_10{
      make_shared<NameToken>("z"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("i"),
  };

  pkb_write_facade_->AddStatementOfAType("10", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("10", "z");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "10", egs->GetExpressionFromInput(
          token_list_statement_10, "assign"));

  // z + 2
  TokenList token_list_statement_11{
      make_shared<NameToken>("z"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<IntegerToken>("2"),
  };

  pkb_write_facade_->AddStatementOfAType("11", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("11", "y");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "11", egs->GetExpressionFromInput(
          token_list_statement_11, "assign"));

  // x * y + z
  TokenList token_list_statement_12{
      make_shared<NameToken>("x"),
      make_shared<ArithmeticOperatorToken>("*", MULTIPLY),
      make_shared<NameToken>("y"),
      make_shared<ArithmeticOperatorToken>("+", PLUS),
      make_shared<NameToken>("z"),
  };

  pkb_write_facade_->AddStatementOfAType("12", ASSIGN);
  pkb_write_facade_->AddStatementModifyingVariable("12", "x");
  pkb_write_facade_->AddAssignmentStatementAndExpression(
      "12", egs->GetExpressionFromInput(
          token_list_statement_12, "assign"));

  pkb_write_facade_->AddStatementModifyingVariable("5", "z");
  pkb_write_facade_->AddStatementModifyingVariable("5", "v");

  node1->AddTransition(true, node2);
  node2->AddTransition(true, node3);
  node2->AddTransition(false, node4);
  node3->AddTransition(true, node2);
  node4->AddTransition(true, node5);
  node4->AddTransition(false, node6);
  node5->AddTransition(true, node7);
  node6->AddTransition(true, node7);

  cfg->AddProcCfg("second", node1);
  cfg->AddProcCfg("third", node3);
  pkb_write_facade_->AddCfg(cfg);

  SECTION("Affects(_, _) - is true") {
    std::string query = "Select BOOLEAN such that Affects(_,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(_, INT) - is true") {
    std::string query = "Select BOOLEAN such that Affects(_,4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(_, INT) - is false") {
    std::string query = "Select BOOLEAN such that Affects(_,1)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, _) - is true") {
    std::string query = "Select BOOLEAN such that Affects(1,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, _) - is false") {
    std::string query = "Select BOOLEAN such that Affects(18,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- self modification e.g. x = x + 1") {
    std::string query = "Select BOOLEAN such that Affects(6,6)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- affects an assign in while loop") {
    std::string query = "Select BOOLEAN such that Affects(1,4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- valid control path through while loop") {
    std::string query = "Select BOOLEAN such that Affects(1,8)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    // check this - expected result should be true -> need to fix bug in affects
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- valid control path through if else") {
    std::string query = "Select BOOLEAN such that Affects(1,10)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- valid control path through stmt that uses"
          "but does not modify variable") {
    std::string query = "Select BOOLEAN such that Affects(1,12)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- simple case (one assign directly after another") {
    std::string query = "Select BOOLEAN such that Affects(9,10)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is true -- check if nested assigns can affect") {
    std::string query = "Select BOOLEAN such that Affects(8,10)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- variable is read") {
    std::string query = "Select BOOLEAN such that Affects(11,14)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- variable modified in if case and else case") {
    std::string query = "Select BOOLEAN such that Affects(18,22)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- assigns are in different procedures") {
    std::string query = "Select BOOLEAN such that Affects(2,17)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

    // check this -> confusion in affects queries
  SECTION("Affects(INT, INT) - is true -- variable is modified in a call stmt (even when in if-else)") {
    std::string query = "Select BOOLEAN such that Affects(2,6)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- affects does not hold for non-assign statements") {
    std::string query = "Select BOOLEAN such that Affects(2,3)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- a latter stmt cannot affect a stmt before it") {
    std::string query = "Select BOOLEAN such that Affects(6,2)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- simple case") {
    std::string query = "Select BOOLEAN such that Affects(9,11)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- simple case") {
    std::string query = "Select BOOLEAN such that Affects(9,12)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- compare between unrelated assigns") {
    std::string query = "Select BOOLEAN such that Affects(2,4)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    // need to check this -> expected result is FALSE
    std::list<std::string> expected_results{"TRUE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(INT, INT) - is false -- assigns with no control path to each other") {
    std::string query = "Select BOOLEAN such that Affects(20,21)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(_, INT) - is false") {
    std::string query = "Select BOOLEAN such that Affects(_,14)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(_, INT) - is false") {
    std::string query = "Select BOOLEAN such that Affects(_,9)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    std::list<std::string> expected_results{"FALSE"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(ASSIGN-SYN, _)") {
    std::string query = "assign a; Select a such that Affects(_,a)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    // need to check this -> expected results should be "4", "6", "8", "10", "11", "12"
    std::list<std::string> expected_results{"10", "11", "12", "4", "6"};
    results.sort();
    REQUIRE(results == expected_results);
  }

  SECTION("Affects(_, ASSIGN-SYN)") {
    std::string query = "assign a; Select a such that Affects(a,_)";
    std::list<std::string> results;
    Qps::ProcessQuery(query, results, pkb_read_facade_);
    // need to check this -> expected results should be 1", "4", "8", "2", "6", "9", "10", "11"
    std::list<std::string> expected_results{"1", "10", "11", "2", "4", "6", "8", "9"};
    results.sort();
    REQUIRE(results == expected_results);
  }
}




