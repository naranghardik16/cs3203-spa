#include "AssignStatementParser.h"

shared_ptr<Statement> AssignStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  std::string var_name = ExtractVariableName(line);
  Variable var(var_name);
  auto assign_stmt =
      make_shared<AssignStatement>(Program::GetAndIncreaseStatementNumber(),
                                   var,
                                   GetProcName());
  CheckEndOfStatement(line);
  vector<shared_ptr<Token>>
      expression_tokens{line.begin() + sp_constants::k_pos_of_assign, line.end() - sp_constants::k_token_size};
  auto expr_parser =
      ExpressionParserFactory::GetExpressionParser(expression_tokens, sp_constants::k_assign_stmt);
  auto expression = expr_parser->ParseEntity(expression_tokens);
  assign_stmt->AddExpression(expression);
  return assign_stmt;
}

std::string AssignStatementParser::ExtractVariableName(Line &line) const {
  auto assign_keyword_itr = std::find_if(std::begin(line), std::end(line),
                                         [&](shared_ptr<Token> const p) {
                                           return p->GetType() == SINGLE_EQUAL;
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

  if (line[k_pos_lhs_]->GetType() != NAME) {
    throw SyntaxErrorException("var_name should be a NAME");
  }

  return line[k_pos_lhs_]->GetValue();
}

void AssignStatementParser::CheckEndOfStatement(Line &line) const {
  if ((*prev(line.end()))->GetType() != SEMICOLON) {
    throw SyntaxErrorException("AssignStatement does not end with ;");
  }

  if (line.size() < k_min_tokens_) {
    throw SyntaxErrorException("Lesser tokens than what an AssignStatement has");
  }
}
