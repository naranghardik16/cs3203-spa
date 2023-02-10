#pragma once
#include "ExpressionParser.h"
#include "core/model/Operation.h"
#include "../ArithmeticOperatorToken.h"
#include "../RelationalOperatorToken.h"
#include "../ConditionalOperatorToken.h"
//#include "ArithmeticOperationParser.h"


class OperationParser : public ExpressionParser {
 public:
  OperationParser() = default;
  Expression *ParseEntity(TokenStream &tokens) override;
  Expression *ParseEntity(Line &line) override;
  bool IsEndOfLine();
  TokenType GetCurrentTokenType();
  string GetCurrentTokenValue();
  int* GetPos();
//  void SetPos(int pos);
  void InheritArgs(int *pos, Line line);
  void UpdateCurrTokenWithUpdatedPos();
  Line *GetLine();
//  void Setline(Line line);
  void GetNext();
 private:
  Line line_;
  int starting_pos_value = 0;
  int* pos_ = &starting_pos_value;
  Token *curr_token_ = nullptr;
  string curr_token_value_;
  void Setup(Line &line);
  virtual Expression *Parse() = 0;
};


