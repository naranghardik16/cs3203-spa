#pragma once

#include <stack>
#include <unordered_map>
#include "ExpressionParser.h"
#include "core/model/Operation.h"
#include "SP/Tokenizer/ArithmeticOperatorToken.h"
#include "SP/Tokenizer/RelationalOperatorToken.h"
#include "SP/Tokenizer/ConditionalOperatorToken.h"


class OperationParser : public ExpressionParser {
 public:
  OperationParser() = default;
  shared_ptr<Expression> ParseEntity(TokenStream &tokens) override;
  shared_ptr<Expression> ParseEntity(Line &line) override;
  bool IsEndOfLine();
  TokenType GetCurrentTokenType();
  string GetCurrentTokenValue();
  int GetCurrentTokenPos();
  shared_ptr<int> GetPos();
  void InheritArgs(shared_ptr<int> pos, bool is_sub_expr, shared_ptr<bool> is_processed_curr_token);
  void UpdateCurrTokenWithUpdatedPos();
  shared_ptr<Line> GetLine();
  void GetNext();
  bool GetIsSubExpr();
  void SetIsSubExpr(bool is_sub_expr);
  shared_ptr<bool> GetIsProcessedCurrToken();
  void ValidateEnoughTokensToProcess();
  void AddParenthesis(TokenType type, string val, int token_pos);
 private:
  Line line_;
  bool is_inherit_args_ = false;
  int starting_pos_value_ = 0;
  shared_ptr<int> pos_ = make_shared<int>(starting_pos_value_);
  shared_ptr<Token> curr_token_ = nullptr;
  string curr_token_value_;
  bool is_sub_expr_ = false;
  bool is_processed_curr_token_value_ = false;
  shared_ptr<bool> is_processed_curr_token_ = make_shared<bool>(is_processed_curr_token_value_);
  void Setup(Line &line);
  virtual shared_ptr<Expression> Parse() = 0;
  void ValidateForBalancedParenthesis();
  stack<string> parentheses_container_;
  unordered_map<int, string> parentheses_pos_mappings_;
};


