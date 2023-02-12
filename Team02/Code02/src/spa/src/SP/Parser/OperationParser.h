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
  void InheritArgs(int *pos, bool is_sub_expr, bool *is_processed_curr_token);
  void UpdateCurrTokenWithUpdatedPos();
  Line *GetLine();
  void GetNext();
  bool GetIsSubExpr();
  void SetIsSubExpr(bool is_sub_expr);
  bool* GetIsProcessedCurrToken();
  void ValidateEnoughTokensToProcess(string err_msg);
 private:
  Line line_;
  bool is_inherit_args_ = false;
  int starting_pos_value_ = 0;
  int* pos_ = &starting_pos_value_;
  Token *curr_token_ = nullptr;
  string curr_token_value_;
  bool is_sub_expr_ = false;
  bool is_processed_curr_token_value_ = false;
  bool* is_processed_curr_token_ = &is_processed_curr_token_value_;
  void Setup(Line &line);
  virtual Expression *Parse() = 0;
  void ValidateForBalancedParenthesis();
};


