#include "AssignStatementParser.h"
#include "iostream"

AssignStatement *AssignStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  // need to extract lhs and the expression
  std::string_view var_name = ExtractVariableName(line);
  return new AssignStatement(var_name, 2, "main");
}

std::string_view AssignStatementParser::ExtractVariableName(Line &line) const {
  auto assign_keyword_itr = std::find(line.begin(), line.end(), "assign");

  // There should a var on the left and an expression on the right side of the assignment operator
  if (assign_keyword_itr == line.begin() || assign_keyword_itr == line.end()) {
    throw SyntaxErrorException();
  }
  // ensure only one variable on the left
  bool
      valid_lhs_variable = std::distance(line.begin(), assign_keyword_itr) == 1;
  if (!valid_lhs_variable) {
    throw SyntaxErrorException();
  }
  return line[0];
}