#pragma once

#include <stack>
#include "ExpressionParser.h"
#include "core/model/Operation.h"
#include "SP/Tokenizer/ArithmeticOperatorToken.h"
#include "SP/Tokenizer/RelationalOperatorToken.h"
#include "SP/Tokenizer/ConditionalOperatorToken.h"


class OperationParser : public ExpressionParser {
 public:
  OperationParser() = default;
  Expression *ParseEntity(TokenStream &tokens) override;
  Expression *ParseEntity(Line &line) override;
  bool IsEndOfLine();
  TokenType GetCurrentTokenType();
  string GetCurrentTokenValue();
  int* GetPos();
  void InheritArgs(int *pos, Line line, bool is_sub_expr);
  void UpdateCurrTokenWithUpdatedPos();
  Line *GetLine();
  void GetNext();
  bool GetIsSubExpr();
  void SetIsSubExpr(bool is_sub_expr);
 private:
  Line line_;
  int starting_pos_value_ = 0;
  int* pos_ = &starting_pos_value_;
  Token *curr_token_ = nullptr;
  string curr_token_value_;
  bool is_sub_expr_ = false;
  void Setup(Line &line);
  virtual Expression *Parse() = 0;
  void ValidateForBalancedParenthesis();
};


