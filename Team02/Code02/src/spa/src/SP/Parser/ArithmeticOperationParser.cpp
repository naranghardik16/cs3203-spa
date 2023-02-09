#pragma once
#include "ArithmeticOperationParser.h"

ArithmeticOperationParser::ArithmeticOperationParser(vector<Token *> &line) {
  line_ = line;
  GetNext();
}

void ArithmeticOperationParser::GetNext() {
  if (pos_ < line_.size()) {
    curr_token_ =  line_.at(pos_);
    curr_token_value_ = curr_token_->GetValue();
    pos_++;
  }
}

ArithmeticOperation *ArithmeticOperationParser::Parse() {
  Expression *root = Term();
  while (pos_ != line_.size() && root != nullptr && count(term_operators_.begin(), term_operators_.end(), curr_token_->GetType())) {
    string prev_token_value = curr_token_value_;
    GetNext();
    Expression *right_node = Term();
    pair<Expression*, Expression*> arguments;
    arguments.first = root;
    arguments.second = right_node;
    root = new ArithmeticOperation(prev_token_value, arguments);
  }
  return dynamic_cast<ArithmeticOperation*>(root);
}

Expression *ArithmeticOperationParser::Term() {
  Expression *term = Factor();

  while (pos_ != line_.size() && term != nullptr && count(factor_operators_.begin(), factor_operators_.end(), curr_token_->GetType())) {
    string prev_token_value = curr_token_value_;
    GetNext();
    Expression *right_node = Factor();
    pair<Expression*, Expression*> arguments;
    arguments.first = term;
    arguments.second = right_node;
    term = new ArithmeticOperation(prev_token_value, arguments);
  }
  return term;
}

Expression *ArithmeticOperationParser::Factor() {
  Expression *term = nullptr;

  if (curr_token_->GetType() == LEFT_BRACE) {
    GetNext();
    term = Parse();
    if (curr_token_->GetType() != RIGHT_BRACE) {
      throw new SyntaxErrorException("Missing )");
    }
  } else if (curr_token_->GetType() == INTEGER) {
    term = new Constant(curr_token_value_);
  } else if (curr_token_->GetType() == NAME) {
    term = new Variable(curr_token_value_);
  }
  GetNext();
  return term;
}

