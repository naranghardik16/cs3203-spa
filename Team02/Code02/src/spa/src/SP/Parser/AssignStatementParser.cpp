#include "AssignStatementParser.h"
#include "iostream"

Statement *AssignStatementParser::ParseEntity(TokenStream &tokens) {
  tokens.pop_front();
  return new Statement(0, "assign", "proc");
}