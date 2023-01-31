#pragma once
#include <deque>
#include <string>
#include <vector>

template<typename Entity>
class EntityParser {
 public:
  typedef std::deque<std::vector<std::string>> TokenStream;
  typedef std::vector<std::string> Line;
  virtual Entity *ParseEntity(TokenStream &tokens) = 0;
};