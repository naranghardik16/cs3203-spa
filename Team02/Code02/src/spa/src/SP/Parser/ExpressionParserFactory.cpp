#include "ExpressionParserFactory.h"

ExpressionParser *ExpressionParserFactory::GetExpressionParser(Line &line) {
  if (CheckExpressionType(line, "variable")) {
    return new VariableParser();
  }
  return nullptr;
}

bool ExpressionParserFactory::CheckExpressionType(Line &line,
                                                  std::string_view type_to_check) {
  return true;
}