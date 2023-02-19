#include "IfStatementParser.h"

shared_ptr<Statement> IfStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  auto condition = ExtractCondition(line);
  auto if_stmt =
      make_shared<IfStatement>(Program::GetAndIncreaseStatementNumber(),
                               *condition,
                               "main");
  // Verify syntax is correct for if statement
  CheckStartOfIfStatement(line);

  // Parse and add statements in then block
  while (!tokens.empty() && !IsEndOfThenStatement(tokens.front())) {
    auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
    auto stmt = stmt_parser->ParseEntity(tokens);
    if_stmt->AddThenStmtList(stmt);
  }

  if (IsEndOfThenStatement(tokens.front())) {
    tokens.pop_front();
  }

  if (!HasElseStatements(tokens.front())) return if_stmt;

  CheckStartOfElseStatement(tokens.front());
  tokens.pop_front();

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

shared_ptr<ConditionalOperation> IfStatementParser::ExtractCondition(Line &line) {
  // remove "if (" and ") then {" from the token line
  vector<shared_ptr<Token>> expression_tokens{line.begin() + 2, line.end() - 3};
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

void IfStatementParser::CheckStartOfIfStatement(Line &line) const {
  if (line.size() < 2) {
    throw SyntaxErrorException("Invalid length for if then statement");
  }

  auto
      itr_brace =
      std::find_if(std::begin(line),
                   std::end(line),
                   [&](shared_ptr<Token> const p) {
                     return p->GetType() == TokenType::LEFT_BRACE;
                   });

  if (itr_brace != prev(line.end())) {
    throw SemanticErrorException("If Statement is missing a {");
  }

  auto
<<<<<<< HEAD
      itr_then = prev(prev(line.end()));
=======
      itr_then =
      std::find_if(std::begin(line),
                   std::end(line),
                   [&](shared_ptr<Token> const p) {
                     return p->GetValue() == "then";
                   });
>>>>>>> milestone1

  if (itr_then->get()->GetValue() != "then") {
    throw SemanticErrorException(
        "If Statement is missing then or is not in correct position");
  }
}

bool IfStatementParser::IsEndOfThenStatement(Line &line) const {

  return std::find_if(std::begin(line), std::end(line),
                      [&](shared_ptr<Token> const p) {
                        return p->GetValue() == "}";
                      }) != std::end(line);
}

bool IfStatementParser::HasElseStatements(Line &line) const {
  return std::find_if(std::begin(line), std::end(line),
                      [&](shared_ptr<Token> const p) {
                        return p->GetValue() == "else";
                      }) != std::end(line);
}

void IfStatementParser::CheckStartOfElseStatement(Line &line) const {
  if (line.size() != 2) {
    throw SyntaxErrorException("Not a valid else statement");
  }

  if (line[0]->GetValue() != "else") {
    throw SyntaxErrorException("Missing else statement");
  }

  if (line[1]->GetValue() != "{") {
    throw SyntaxErrorException("Missing } at the start of else block");
  }
}

bool IfStatementParser::IsEndOfIfElseStatement(Line &line) const {
  return std::find_if(std::begin(line), std::end(line),
                      [&](shared_ptr<Token> const p) {
                        return p->GetType() == TokenType::RIGHT_BRACE;
                      }) != std::end(line);
}
