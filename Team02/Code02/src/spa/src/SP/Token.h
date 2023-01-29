//
// Created by Kai Qi Yong on 29/1/23.
//
//
#ifndef SPA_SRC_SPA_SRC_TOKEN_H_
#define SPA_SRC_SPA_SRC_TOKEN_H_

#pragma once
#include <string>
using namespace std;
/*
enum class TokenType {
  NAME,
  INTEGER,
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  LEFT_BRACE,
  RIGHT_BRACE,
  SEMICOLON,
  UNDERSCORE,
  DOUBLE_QUOTE,
  SINGLE_EQUALS,
  DOUBLE_EQUALS,
  NOT,
  NOT_EQUALS,
  AND,
  OR,
  GT,
  GTE,
  LT,
  LTE,
  PLUS,
  MINUS,
  MULTIPLY,
  DIV,
  MOD
};

class Token {
  TokenType type_;
  string value_;
 public:
  Token(TokenType t, string val);
  TokenType GetType();
  string GetValue();
  bool Equals(Token* other);
};
*/

class Token {
  string value_;
 public:
  Token(string val);
  string GetValue();
  virtual bool Equals(Token* other);
};

#endif //SPA_SRC_SPA_SRC_TOKEN_H_
