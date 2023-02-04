#include "PrintStatementParser.h"

PrintStatement *PrintStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  std::string_view var_name = ExtractVariableName(line);
  Variable var(var_name);
  auto print_stmt =
      new PrintStatement(Program::GetAndIncreaseStatementNumber(), var, "main");

  return print_stmt;
}

std::string PrintStatementParser::ExtractVariableName(Line &line) const {
  auto print_keyword_itr =
      std::find_if(std::begin(line), std::end(line), [&](Token *const p) {
        return p->GetValue() == "print";
      });

  if (print_keyword_itr != line.begin()) {
    throw SyntaxErrorException("Print statement should start with print keyword");
  }

  if (line.size() < 2) {
    throw SyntaxErrorException("Print statement does not have a variable");
  }

  return line[1]->GetValue();

}