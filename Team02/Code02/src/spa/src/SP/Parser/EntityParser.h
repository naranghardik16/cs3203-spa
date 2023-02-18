#pragma once
#include <deque>
#include <string>
#include <vector>
#include "SP/Tokenizer/Token.h"

template<typename Entity>
class EntityParser {
 public:
  typedef std::deque<std::vector<shared_ptr<Token>>> TokenStream;
  typedef std::vector<shared_ptr<Token>> Line;
  virtual shared_ptr<Entity> ParseEntity(TokenStream &tokens) = 0;
};