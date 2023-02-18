#include "WhileStatementParser.h"

shared_ptr<Statement> WhileStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  auto condition = ExtractCondition(line);
  auto while_stmt = make_shared<WhileStatement>(Program::GetAndIncreaseStatementNumber(),
                                       *condition,
                                       "main");
  CheckStartOfLoopStatement(line);
  while (!tokens.empty() && !IsEndOfWhileStatement(tokens.front())) {
    auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
    auto loop_stmt = stmt_parser->ParseEntity(tokens);
    while_stmt->AddStatement(loop_stmt);
  }
  if (IsEndOfWhileStatement(tokens.front())) {
    tokens.pop_front();
  }
  return while_stmt;
}

void WhileStatementParser::CheckStartOfLoopStatement(Line &line) const {
  auto
      itr = std::find_if(std::begin(line), std::end(line), [&](shared_ptr<Token> const p) {
    return p->GetType() == TokenType::LEFT_BRACE;
  });

  if (itr != prev(line.end())) {
    throw SemanticErrorException("While Statement does not start with {");
  }
}

shared_ptr<ConditionalOperation> WhileStatementParser::ExtractCondition(Line &line) {
  // remove "while (" and ") {" from the token line
  vector<shared_ptr<Token>> expression_tokens{line.begin() + 2, line.end() - 2};
  auto expr_parser =
      ExpressionParserFactory::GetExpressionParser(expression_tokens, "if");
  auto
      condition = (expr_parser->ParseEntity(
      expression_tokens));
  if (!condition) {
    throw SyntaxErrorException("Could not get a condition for if statement");
  }
  return dynamic_pointer_cast<ConditionalOperation>(condition);
}

bool WhileStatementParser::IsEndOfWhileStatement(Line &line) const {
  return std::find_if(std::begin(line), std::end(line),
                      [&](shared_ptr<Token> const p) {
                        return p->GetType() == TokenType::RIGHT_BRACE;
                      }) != std::end(line);
}