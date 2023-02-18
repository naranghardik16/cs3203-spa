#include "OperationParser.h"

void OperationParser::Setup(Line &line) {
  if (*pos_ == 0) {
    line_ = line;
    GetNext();
  }

  if (is_inherit_args_) {
    line_ = line;
    curr_token_ = line_.at(*pos_ - 1);
    curr_token_value_ = curr_token_->GetValue();
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
    (*is_processed_curr_token_) = false;
    (*pos_)++;
  }
}

int* OperationParser::GetPos() {
  return pos_;
}

ExpressionParser::Line *OperationParser::GetLine() {
  return &line_;
}

void OperationParser::InheritArgs(int *pos, bool is_sub_expr, bool *is_processed_curr_token) {
  is_inherit_args_ = true;
  pos_ = pos;
  is_sub_expr_ = is_sub_expr;
  is_processed_curr_token_ = is_processed_curr_token;
}

bool OperationParser::IsEndOfLine() {
  return *pos_ == line_.size();
}

TokenType OperationParser::GetCurrentTokenType() {
  (*is_processed_curr_token_) = true;
  return curr_token_->GetType();
}

string OperationParser::GetCurrentTokenValue() {
  (*is_processed_curr_token_) = true;
  return curr_token_value_;
}

shared_ptr<Expression> OperationParser::ParseEntity(TokenStream &tokens) {
  return ParseEntity(tokens.front());
}

shared_ptr<Expression> OperationParser::ParseEntity(Line &line) {
  Setup(line);
  shared_ptr<Expression> result = Parse();
  ValidateForBalancedParenthesis();
  return result;
}

bool OperationParser::GetIsSubExpr() {
  return is_sub_expr_;
}

void OperationParser::SetIsSubExpr(bool is_sub_expr) {
  is_sub_expr_ = is_sub_expr;
}

bool* OperationParser::GetIsProcessedCurrToken() {
  return is_processed_curr_token_;
}

void OperationParser::ValidateForBalancedParenthesis() {
  if (is_sub_expr_ || (IsEndOfLine() && *is_processed_curr_token_)) {
    return;
  }
  throw SyntaxErrorException("Unbalanced parenthesis ()");
}

void OperationParser::ValidateEnoughTokensToProcess(string err_msg) {
  if (*is_processed_curr_token_) {
    throw SyntaxErrorException("Insufficient tokens to process");
  }
}
