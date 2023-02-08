#pragma once

#include<vector>
#include "ConstantParser.h"
#include "ExpressionParser.h"
#include "VariableParser.h"
#include "OperationParser.h"
#include "../NameToken.h"
#include "../IntegerToken.h"

class ExpressionParserFactory {
  typedef std::vector<Token *> Line;

 public:
  static ExpressionParser *GetExpressionParser(Line &line);
 private:
  static inline bool CheckExpressionType(Line &line,
                                         std::string_view type_to_check);
};