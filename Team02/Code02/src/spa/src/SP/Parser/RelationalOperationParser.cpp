#pragma once
#include "RelationalOperationParser.h"

/*
rel_expr: rel_factor '>' rel_factor | rel_factor '>=' rel_factor |
          rel_factor '<' rel_factor | rel_factor '<=' rel_factor |
          rel_factor '==' rel_factor | rel_factor '!=' rel_factor
 */
Expression *RelationalOperationParser::Parse() {
  auto left_rel_factor = Factor();
  UpdateCurrTokenWithUpdatedPos();
  unordered_set<TokenType> rel_ops = {LT, LTE, GT, GTE, DOUBLE_EQUALS, NE};
  if (rel_ops.find(GetCurrentTokenType()) == rel_ops.end()) {
    throw SyntaxErrorException("Missing relational operator");
  }
  string op = GetCurrentTokenValue();
  GetNext();
  auto right_rel_factor = Factor();
  UpdateCurrTokenWithUpdatedPos();
  pair<Expression*, Expression*> args;
  args.first = left_rel_factor;
  args.second = right_rel_factor;
  return new RelationalOperation(op, args);
}

Expression *RelationalOperationParser::Factor() {
  ArithmeticOperationParser *arithmetic_operation_parser = new ArithmeticOperationParser();
  arithmetic_operation_parser->InheritArgs(GetPos(), *GetLine(), GetIsSubExpr());
  arithmetic_operation_parser->SetIsSubExpr(true);
  return arithmetic_operation_parser->ParseEntity(*GetLine());
}