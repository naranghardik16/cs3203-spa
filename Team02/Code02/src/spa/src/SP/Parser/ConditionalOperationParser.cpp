#include "ConditionalOperationParser.h"

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
      this->SetIsSubExpr(true);
      auto cond_expr = Parse();
      if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
        throw SyntaxErrorException("Missing )");
      }
      pair<Expression*, Expression*> args;
      args.first = cond_expr;
      return new ConditionalOperation("!", args);
    }
  } else if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
    GetNext();
    ValidateEnoughTokensToProcess("");
    this->SetIsSubExpr(true);
    auto left_cond_expr = Parse();
    if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
      throw SyntaxErrorException("Missing )");
    }

    GetNext();
    string op = GetCurrentTokenValue();
    if (!(GetCurrentTokenType() == AND || GetCurrentTokenType() == OR)) {
      throw SyntaxErrorException("Missing && or ||");
    }
    GetNext();

    if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
      GetNext();
      this->SetIsSubExpr(true);
      auto right_cond_expr = Parse();
      if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
        throw SyntaxErrorException("Missing )");
      }
      pair<Expression*, Expression*> args;
      args.first = left_cond_expr;
      args.second = right_cond_expr;
      return new ConditionalOperation(op, args);
    } else {
      throw SyntaxErrorException("Missing (");
    }

  } else { // rel_expr
    RelationalOperationParser *relational_operation_parser = new RelationalOperationParser();
    relational_operation_parser->InheritArgs(GetPos(),GetIsSubExpr(),GetIsProcessedCurrToken());
    auto rel_expr = relational_operation_parser->ParseEntity(*GetLine());
    this->SetIsSubExpr(false);
    if (rel_expr) {
      pair<Expression*, Expression*> args;
      args.first = rel_expr;
      UpdateCurrTokenWithUpdatedPos();
      return new ConditionalOperation("rel_expr", args);
    }
  }

  return nullptr;
}