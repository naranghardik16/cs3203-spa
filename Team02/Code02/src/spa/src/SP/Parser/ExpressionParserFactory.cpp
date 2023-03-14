#include "ExpressionParserFactory.h"

shared_ptr<ExpressionParser> ExpressionParserFactory::GetExpressionParser(Line &line, string statement_type) {
  if (CheckExpressionType(line, "variable")) {
    return make_shared<VariableParser>();
  }
  if (CheckExpressionType(line, "constant")) {
    return make_shared<ConstantParser>();
  }

  if (!CheckExpressionType(line, "operation")) {
    return nullptr;
  }

  if (statement_type == "assign") {
    return make_shared<ArithmeticOperationParser>();
  }

  if (statement_type == "if" || statement_type == "while") {
    return make_shared<ConditionalOperationParser>();
  }

  return nullptr;
}

bool ExpressionParserFactory::CheckExpressionType(Line &line,
                                                  std::string_view type_to_check) {
  if (line.size() == 1) {
    if (line[0]->GetType() == NAME) {
      return type_to_check == "variable";
    }

    if (line[0]->GetType() == INTEGER) {
      return type_to_check == "constant";
    }
  }

  return type_to_check == "operation";
}
