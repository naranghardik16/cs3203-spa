#include "OperationParser.h"

void OperationParser::Setup(Line &line) {
  if (*pos_ == 0) {
    line_ = line;
    GetNext();
  }
}

void OperationParser::UpdateCurrTokenWithUpdatedPos() {
  curr_token_ =  line_.at(*pos_ - 1);
  curr_token_value_ = curr_token_->GetValue();
}

void OperationParser::GetNext() {
  if (*pos_ < line_.size()) {
    curr_token_ =  line_.at(*pos_);
    curr_token_value_ = curr_token_->GetValue();
    (*pos_)++;
  }
}

int* OperationParser::GetPos() {
  return pos_;
}

ExpressionParser::Line *OperationParser::GetLine() {
  return &line_;
}

//void OperationParser::Setline() {
//
//}

void OperationParser::InheritArgs(int *pos, ExpressionParser::Line line) {
  pos_ = pos;
  line_ = line;
  curr_token_ = line_.at(*pos_ - 1);
  curr_token_value_ = curr_token_->GetValue();
}

bool OperationParser::IsEndOfLine() {
  return *pos_ == line_.size();
}

TokenType OperationParser::GetCurrentTokenType() {
  return curr_token_->GetType();
}

string OperationParser::GetCurrentTokenValue() {
  return curr_token_value_;
}

Expression *OperationParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

Expression *OperationParser::ParseEntity(Line &line) {
  Setup(line);
  return Parse();
}

/*
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
 */