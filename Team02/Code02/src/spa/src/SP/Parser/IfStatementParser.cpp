#include "IfStatementParser.h"

IfStatement *IfStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  auto condition = ExtractCondition(line);
  auto if_stmt = new IfStatement(Program::GetAndIncreaseStatementNumber(),
                                 condition,
                                 "main");
  CheckStartOfIfStatement(line);
  while (!tokens.empty() && !IsEndOfThenStatement(tokens.front())) {
    auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
    auto stmt = stmt_parser->ParseEntity(tokens);
    if_stmt->AddThenStmtList(stmt);
  }

  if (IsEndOfThenStatement(tokens.front())) {
    tokens.pop_front();
  }

  while (!tokens.empty() && !IsEndOfIfElseStatement(tokens.front())) {
    auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
    auto stmt = stmt_parser->ParseEntity(tokens);
    if_stmt->AddElseStmtList(stmt);
  }

  if (IsEndOfIfElseStatement(tokens.front())) {
    tokens.pop_front();
  }

  return if_stmt;
}

ConditionalOperation IfStatementParser::ExtractCondition(Line &line) {
  // remove "if (" and ") then {" from the token line
  vector<Token *> expression_tokens{line.begin() + 2, line.end() - 3};
  auto expr_parser =
      ExpressionParserFactory::GetExpressionParser(expression_tokens, "if");
  auto
      condition = (expr_parser->ParseEntity(
      expression_tokens));
  if (!condition) {
    throw SyntaxErrorException("Could not get a condition for if statement");
  }
  return *dynamic_cast<ConditionalOperation *>(condition);
}

void IfStatementParser::CheckStartOfIfStatement(Line &line) const {
  auto
      itr_brace =
      std::find_if(std::begin(line), std::end(line), [&](Token *const p) {
        return p->GetType() == TokenType::LEFT_BRACE;
      });

  if (itr_brace != prev(line.end())) {
    throw SemanticErrorException("If Statement is missing a {");
  }

  auto
      itr_then =
      std::find_if(std::begin(line), std::end(line), [&](Token *const p) {
        return p->GetValue() == "then";
      });

  if (itr_then != prev(prev(line.end()))) {
    throw SemanticErrorException(
        "If Statement is missing then or is not in correct position");
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
                        return p->GetType() == TokenType::RIGHT_BRACE;
                      }) != std::end(line);
}
