#include "ExpressionParserFactory.h"

ExpressionParser *ExpressionParserFactory::GetExpressionParser(Line &line) {
  if (CheckExpressionType(line, "variable")) {
    return new VariableParser();
  }
  if (CheckExpressionType(line, "constant")) {
    return new ConstantParser();
  }
  if (CheckExpressionType(line, "operation")) {
    return new OperationParser();
  }
  return nullptr;
}

bool ExpressionParserFactory::CheckExpressionType(Line &line,
                                                  std::string_view type_to_check) {
  if (line.size() == 1) {
//    // can only be a Variable or Constant;
//    auto it = dynamic_cast<NameToken *>(line[0]);
//    if (it) {
//      return type_to_check == "variable";
//    }
//    auto it2 = dynamic_cast<IntegerToken *>(line[0]);
//    if (it2) {
//      return type_to_check == "constant";
//    }
    if (line[0]->GetType() == NAME) {
      return type_to_check == "variable";
    }

    if (line[0]->GetType() == INTEGER) {
      return type_to_check == "constant";
    }
  }

  return type_to_check == "operation";
}