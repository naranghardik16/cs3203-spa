#include "ConditionalOperationParser.h"

/*
cond_expr: rel_expr | '!' '(' cond_expr ')' |
           '(' cond_expr ')' '&&' '(' cond_expr ')' |
           '(' cond_expr ')' '||' '(' cond_expr ')'
 */
shared_ptr<Expression> ConditionalOperationParser::Parse() {
  if (GetCurrentTokenType() == NOT) {
    GetNext();
    if (GetCurrentTokenType() == LEFT_PARENTHESIS) {
      GetNext();
      this->SetIsSubExpr(true);
      auto cond_expr = Parse();
      if (GetCurrentTokenType() != RIGHT_PARENTHESIS) {
        throw SyntaxErrorException("Missing )");
      }
      pair<shared_ptr<Expression>, shared_ptr<Expression>> args;
      args.first = cond_expr;
      return make_shared<ConditionalOperation>("!", args);
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
      pair<shared_ptr<Expression>, shared_ptr<Expression>> args;
      args.first = left_cond_expr;
      args.second = right_cond_expr;
      return make_shared<ConditionalOperation>(op, args);
    } else {
      throw SyntaxErrorException("Missing (");
    }

  } else { // rel_expr
    shared_ptr<RelationalOperationParser> relational_operation_parser = make_shared<RelationalOperationParser>();
    relational_operation_parser->InheritArgs(GetPos(),GetIsSubExpr(),GetIsProcessedCurrToken());
    auto rel_expr = relational_operation_parser->ParseEntity(*GetLine());
    this->SetIsSubExpr(false);
    if (rel_expr) {
      pair<shared_ptr<Expression>, shared_ptr<Expression>> args;
      args.first = rel_expr;
      UpdateCurrTokenWithUpdatedPos();
      return make_shared<ConditionalOperation>("rel_expr", args);
    }
  }

  return nullptr;
}