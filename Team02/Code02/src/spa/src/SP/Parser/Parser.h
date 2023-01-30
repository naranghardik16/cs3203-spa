#pragma once

#include <string>
#include <vector>

#include "core/model/Program.h"

class Parser {
 public:
  typedef std::vector<std::vector<std::string>> TokenStream;
  typedef std::vector<std::string> Line;
  [[nodiscard]] Program ParseSource(TokenStream &token);
 private:
  static bool IsStatement(Line &line);
  static bool IsProcedure(Line &line);

};