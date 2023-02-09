#include "WhileStatementParser.h"

WhileStatement *WhileStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  auto condition = ExtractCondition(line);
  auto while_stmt = new WhileStatement(Program::GetAndIncreaseStatementNumber(),
                                       condition,
                                       "main");
  CheckStartOfLoopStatement(line);
  while (!tokens.empty() && IsEndOfWhileStatement(tokens.front())) {
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
      itr = std::find_if(std::begin(line), std::end(line), [&](Token *const p) {
    return p->GetType() == TokenType::LEFT_PARENTHESIS;
  });

  if (itr != prev(line.end())) {
    throw SemanticErrorException("While Statement does not start with {");
  }
}

ConditionalOperation WhileStatementParser::ExtractCondition(Line &line) {
  return ConditionalOperation("<",
                              {new Variable("x"), new Constant("5")});
}

bool WhileStatementParser::IsEndOfWhileStatement(Line &line) const {
  return std::find_if(std::begin(line), std::end(line),
                      [&](Token *const p) {
                        return p->GetType() == TokenType::RIGHT_PARENTHESIS;
                      }) != std::end(line);
}