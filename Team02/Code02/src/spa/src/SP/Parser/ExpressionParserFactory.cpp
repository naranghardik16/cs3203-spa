#include "ExpressionParserFactory.h"

shared_ptr<ExpressionParser> ExpressionParserFactory::GetExpressionParser(Line &line,
                                                                          string statement_type) {
  if (CheckExpressionType(line, k_variable_)) {
    return make_shared<VariableParser>();
  }
  if (CheckExpressionType(line, k_constant_)) {
    return make_shared<ConstantParser>();
  }

  if (!CheckExpressionType(line, k_operation_)) {
    return nullptr;
  }

  if (statement_type == k_assign_) {
    return make_shared<ArithmeticOperationParser>();
  }

  if (statement_type == k_if_ || statement_type == k_while_) {
    return make_shared<ConditionalOperationParser>();
  }

  return nullptr;
}

bool ExpressionParserFactory::CheckExpressionType(Line &line,
                                                  std::string_view type_to_check) {
  if (line.size() == 1) {
    if (line[0]->GetType() == NAME) {
      return type_to_check == k_variable_;
    }

    if (line[0]->GetType() == INTEGER) {
      return type_to_check == k_constant_;
    }
  }

  return type_to_check == k_operation_;
}
