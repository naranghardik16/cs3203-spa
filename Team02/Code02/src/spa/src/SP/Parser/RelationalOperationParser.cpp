#include "RelationalOperationParser.h"

/*
rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
          rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
          rel_factor '==' rel_factor | rel_factor '!=' rel_factor
 */
shared_ptr<Expression> RelationalOperationParser::Parse() {
  auto left_rel_factor = Factor();
  UpdateCurrTokenWithUpdatedPos();
  unordered_set<TokenType> rel_ops = {LT, LTE, GT, GTE, DOUBLE_EQUALS, NE};
  if (rel_ops.find(GetCurrentTokenType()) == rel_ops.end()) {
    throw SyntaxErrorException("Missing relational operator");
  }
  string op = GetCurrentTokenValue();
  GetNext();
  auto right_rel_factor = Factor();
  if (!right_rel_factor) {
    throw SyntaxErrorException("Missing RHS rel_factor");
  }
  UpdateCurrTokenWithUpdatedPos();
  pair<shared_ptr<Expression>, shared_ptr<Expression>> args;
  args.first = left_rel_factor;
  args.second = right_rel_factor;
  return make_shared<RelationalOperation>(op, args);
}

shared_ptr<Expression> RelationalOperationParser::Factor() {
  shared_ptr<ArithmeticOperationParser> arithmetic_operation_parser = make_shared<ArithmeticOperationParser>();
  arithmetic_operation_parser->InheritArgs(GetPos(), GetIsSubExpr(), GetIsProcessedCurrToken());
  arithmetic_operation_parser->SetIsSubExpr(true);
  return arithmetic_operation_parser->ParseEntity(*GetLine());
}