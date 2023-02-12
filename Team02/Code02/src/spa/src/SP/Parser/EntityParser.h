#pragma once
#include <deque>
#include <string>
#include <vector>
#include "SP/Tokenizer/Token.h"

template<typename Entity>
class EntityParser {
 public:
  typedef std::deque<std::vector<Token*>> TokenStream;
  typedef std::vector<Token*> Line;
  virtual Entity *ParseEntity(TokenStream &tokens) = 0;
};