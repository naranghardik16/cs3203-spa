#pragma once

#include "OperationParser.h"

Operation *OperationParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

Operation *OperationParser::ParseEntity(Line &line) {
  bool is_arithmetic = false;
  bool is_logical = false;

  // TODO: Re-design this code to break down the expression into sub-expressions
  // each sub-expression will either be arithmetic or conditional or relational?
  for (Token* token : line) {
    auto ct = dynamic_cast<ArithmeticOperatorToken *>(token);
    if (ct) {
      is_arithmetic = true;
      continue;
    }
    auto ct_2 = dynamic_cast<RelationalOperatorToken *>(token);
    if (ct_2) {
      is_logical = true;
      continue;
    }
    auto ct_3 = dynamic_cast<ConditionalOperatorToken *>(token);
    if (ct_3) {
      is_logical = true;
      continue;
    }
  }

  Operation *result = nullptr;
  if (is_arithmetic) {
    ArithmeticOperationParser *aop = new ArithmeticOperationParser(line);
    result = aop->Parse();
  }


  return result;
}