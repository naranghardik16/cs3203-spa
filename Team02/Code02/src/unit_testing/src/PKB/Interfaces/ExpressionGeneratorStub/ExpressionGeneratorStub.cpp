#include "ExpressionGeneratorStub.h"

ExpressionGeneratorStub::ExpressionGeneratorStub() = default;

ExpressionGeneratorStub::~ExpressionGeneratorStub() = default;

ExpressionGeneratorStub::ExpressionPtr ExpressionGeneratorStub::GetExpressionFromInput(TokenList input, String type) {
  auto expr_parser = ExpressionParserFactory::GetExpressionParser(input, type);
  auto expr = expr_parser->ParseEntity(input);
  return expr;
}
