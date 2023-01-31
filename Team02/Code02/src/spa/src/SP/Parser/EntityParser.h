#pragma once
#include <deque>
#include <vector>

template<typename Entity>
class EntityParser {
 public:
  typedef std::vector<std::string> Line;
  typedef std::deque<Line> TokenStream;
  virtual Entity *ParseEntity(TokenStream &tokens) = 0;
};