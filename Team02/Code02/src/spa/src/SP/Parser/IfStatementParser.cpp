#include "IfStatementParser.h"

IfStatement *IfStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  auto condition = ExtractCondition(line);
  auto if_stmt = new IfStatement(Program::GetAndIncreaseStatementNumber(),
                                 condition,
                                 "main");
  CheckStartOfIfStatement(line);
  while (!tokens.empty() && !IsEndOfThenStatement(line)) {
    auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
    auto stmt = stmt_parser->ParseEntity(tokens);
    if_stmt->AddThenStmtList(stmt);
  }
  if (IsEndOfThenStatement(line)) {
    tokens.pop_front();
  }

  while (!tokens.empty() && !IsEndOfIfElseStatement(line)) {
    auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
    auto stmt = stmt_parser->ParseEntity(tokens);
    if_stmt->AddElseStmtList(stmt);
  }

  if (IsEndOfIfElseStatement(line)) {
    tokens.pop_front();
  }

  return if_stmt;
}

ConditionalOperation IfStatementParser::ExtractCondition(Line &line) {
  return ConditionalOperation("<", {new Variable("x"), new Constant("5")});
}

void IfStatementParser::CheckStartOfIfStatement(Line &line) const {
  auto
      itr = std::find_if(std::begin(line), std::end(line), [&](Token *const p) {
    return p->GetType() == TokenType::LEFT_PARENTHESIS;
  });

  if (itr != prev(line.end())) {
    throw SemanticErrorException("While Statement does not start with {");
  }
}

bool IfStatementParser::IsEndOfThenStatement(Line &line) const {
  return std::find_if(std::begin(line), std::end(line),
                      [&](Token *const p) {
                        return p->GetValue() == "else";
                      }) != std::end(line);
}

bool IfStatementParser::IsEndOfIfElseStatement(Line &line) const {
  return std::find_if(std::begin(line), std::end(line),
                      [&](Token *const p) {
                        return p->GetType() == TokenType::RIGHT_PARENTHESIS;
                      }) != std::end(line);
}
