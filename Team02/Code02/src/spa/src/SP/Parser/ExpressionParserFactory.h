#pragma once

#include<vector>
#include "ConstantParser.h"
#include "ExpressionParser.h"
#include "VariableParser.h"
#include "ConditionalOperationParser.h"
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/IntegerToken.h"

class ExpressionParserFactory {
  typedef std::vector<Token *> Line;

 public:
  static ExpressionParser *GetExpressionParser(Line &line, string statement_type);
 private:
  static inline bool CheckExpressionType(Line &line,
                                         std::string_view type_to_check);
};