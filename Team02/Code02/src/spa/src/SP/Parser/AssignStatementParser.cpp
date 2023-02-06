#include "AssignStatementParser.h"

AssignStatement *AssignStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  std::string var_name = ExtractVariableName(line);
  Variable var(var_name);
  auto assign_stmt =
      new AssignStatement(Program::GetAndIncreaseStatementNumber(),
                          var,
                          "main");
  CheckEndOfStatement(line);
  vector<Token *> expression_tokens{line.begin() + 2, line.end() - 1};
  auto expr_parser =
      ExpressionParserFactory::GetExpressionParser(expression_tokens);
  auto expression = expr_parser->ParseEntity(expression_tokens);
  assign_stmt->AddExpression(expression);
  return assign_stmt;
}

std::string AssignStatementParser::ExtractVariableName(Line &line) const {
  auto assign_keyword_itr = std::find_if(std::begin(line), std::end(line),
                                         [&](Token *const p) {
                                           return p->GetValue() == "=";
                                         });

  // There should a var on the left and an expression on the right side of the assignment operator
  if (assign_keyword_itr == line.begin() || assign_keyword_itr == line.end()) {
    throw SyntaxErrorException("Assign Operator is at the incorrect position");
  }
  // ensure only one variable on the left
  bool
      valid_lhs_variable = std::distance(line.begin(), assign_keyword_itr) == 1;
  if (!valid_lhs_variable) {
    throw SyntaxErrorException("Multiple expressions in lhs of assign");
  }
  return line[0]->GetValue();
}

void AssignStatementParser::CheckEndOfStatement(Line &line) const {
  if ((*prev(line.end()))->GetValue() != ";") {
    throw SyntaxErrorException("AssignStatement does not end with ;");
  }

  if (line.size() < 4) {
    throw SyntaxErrorException("Lesser tokens than what an AssignStatement has");
  }
}