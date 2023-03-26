#include "ExpressionParserFactory.h"

shared_ptr<ExpressionParser> ExpressionParserFactory::GetExpressionParser(Line &line,
                                                                          string statement_type) {
  if (CheckExpressionType(line, sp_constants::k_variable_)) {
    return make_shared<VariableParser>();
  }
  if (CheckExpressionType(line, sp_constants::k_constant_)) {
    return make_shared<ConstantParser>();
  }

  if (!CheckExpressionType(line, sp_constants::k_operation_)) {
    return nullptr;
  }

  if (statement_type == sp_constants::k_assign_stmt) {
    return make_shared<ArithmeticOperationParser>();
  }

  if (statement_type == sp_constants::k_if_stmt_ || statement_type == sp_constants::k_while_stmt_) {
    return make_shared<ConditionalOperationParser>();
  }

  return nullptr;
}

bool ExpressionParserFactory::CheckExpressionType(Line &line,
                                                  std::string_view type_to_check) {
  if (line.size() == k_min_tokens_) {
    if (line[0]->GetType() == NAME) {
      return type_to_check == sp_constants::k_variable_;
    }

    if (line[0]->GetType() == INTEGER) {
      return type_to_check == sp_constants::k_constant_;
    }
  }

  return type_to_check == sp_constants::k_operation_;
}
