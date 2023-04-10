#pragma once

#include<vector>
#include "ConstantParser.h"
#include "ExpressionParser.h"
#include "VariableParser.h"
#include "ConditionalOperationParser.h"
#include "SP/Tokenizer/NameToken.h"
#include "SP/Tokenizer/IntegerToken.h"
#include "SP/Util/SPConstants.h"

/**
 * Factory class for getting the appropriate Expression Parser
 * depending on the line and statement_type.
 */
class ExpressionParserFactory {
  typedef std::vector<shared_ptr<Token>> Line;

 public:
  static shared_ptr<ExpressionParser> GetExpressionParser(Line &line,
                                                          string statement_type);
 private:
  static inline bool CheckExpressionType(Line &line,
                                         std::string_view type_to_check);
  inline static int k_min_tokens_ = 1;
};