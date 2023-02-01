#pragma once

#include<vector>
#include "ExpressionParser.h"
#include "VariableParser.h"

class ExpressionParserFactory {
  typedef std::vector<std::string> Line;

 public:
  static ExpressionParser *GetExpressionParser(Line &line);
 private:
  static inline bool CheckExpressionType(Line &line,
                                         std::string_view type_to_check);
};