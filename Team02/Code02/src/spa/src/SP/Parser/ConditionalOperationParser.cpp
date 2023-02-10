#include "ConditionalOperationParser.h"

//Operation *ConditionalOperationParser::ParseEntity(Line &line) {
//  Setup(line);
//  return Parse();
//}

/*
cond_expr: rel_expr | '!' '(' cond_expr ')' |
           '(' cond_expr ')' '&&' '(' cond_expr ')' |
           '(' cond_expr ')' '||' '(' cond_expr ')'
 */
Operation *ConditionalOperationParser::Parse() {
  if (GetCurrentTokenType() == NOT) {
    GetNext();
    if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
      GetNext();
      auto cond_expr = Parse();
      if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
        throw new SyntaxErrorException("Missing )");
      }
      pair<Expression*, Expression*> args;
      args.first = cond_expr;
      return new ConditionalOperation("!", args);
    }
  } else if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
    GetNext();
    auto left_cond_expr = Parse();
    if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
      throw new SyntaxErrorException("Missing )");
    }

    GetNext();
    string op = GetCurrentTokenValue();
    if (!(GetCurrentTokenType() == AND || GetCurrentTokenType() == OR)) {
      throw new SyntaxErrorException("Missing && or ||");
    }
    GetNext();

    if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
      GetNext();
      auto right_cond_expr = Parse();
      if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
        throw new SyntaxErrorException("Missing )");
      }
      pair<Expression*, Expression*> args;
      args.first = left_cond_expr;
      args.second = right_cond_expr;
      return new ConditionalOperation(op, args);
    }

  } else { // rel_expr
    try {
      RelationalOperationParser *relational_operation_parser = new RelationalOperationParser();
      relational_operation_parser->InheritArgs(GetPos(), *GetLine());
      auto rel_expr = relational_operation_parser->ParseEntity(*GetLine());

      if (rel_expr) {
        pair<Expression*, Expression*> args;
        args.first = rel_expr;
        return new ConditionalOperation("rel_expr", args);
      }
    } catch (exception&) {
      cout << "failed RelationalOperationParser";
    }
  }

  return nullptr;
}