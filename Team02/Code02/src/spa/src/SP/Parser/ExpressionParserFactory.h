#pragma once

#include<vector>
#include "ConstantParser.h"
#include "ExpressionParser.h"
#include "VariableParser.h"
#include "ConditionalOperationParser.h"
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/IntegerToken.h"

class ExpressionParserFactory {
  typedef std::vector<shared_ptr<Token>> Line;

 public:
  static shared_ptr<ExpressionParser> GetExpressionParser(Line &line, string statement_type);
 private:
  static inline bool CheckExpressionType(Line &line,
                                         std::string_view type_to_check);
};