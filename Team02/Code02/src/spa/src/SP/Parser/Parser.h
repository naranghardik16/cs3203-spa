#pragma once

#include <deque>
#include <string>
#include <vector>

#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"
#include "core/model/Program.h"
#include "../Token.h"

class Parser {
 public:
  typedef std::deque<std::vector<Token*>> TokenStream;
  typedef std::vector<std::string> Line;
  [[nodiscard]] Program ParseSource(TokenStream &token);
  static bool IsStatement(Line &line);
  static bool IsProcedure(Line &line);

};