#pragma once

enum TokenType {
  // Punctuation
  LEFT_PARENTHESIS,
  RIGHT_PARENTHESIS,
  LEFT_BRACE,
  RIGHT_BRACE,
  SEMICOLON,
  DOUBLE_QUOTE,
  SINGLE_EQUAL,
  // Arithmetic
  PLUS,
  MINUS,
  DIV,
  MULTIPLY,
  MOD,
  // Relational
  LT,
  LTE,
  GT,
  GTE,
  DOUBLE_EQUALS,
  NE,
  // Conditional
  AND,
  OR,
  NOT,
  // Others
  NAME,
  INTEGER
};