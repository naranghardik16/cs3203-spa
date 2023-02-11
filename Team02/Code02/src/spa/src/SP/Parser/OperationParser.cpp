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