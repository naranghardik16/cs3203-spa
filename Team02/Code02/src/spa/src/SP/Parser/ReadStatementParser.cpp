#include "ReadStatementParser.h"
#include <iostream>

ReadStatement *ReadStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  std::string_view var_name = ExtractVariableName(line);
  Variable var(var_name);
  auto read_stmt =
      new ReadStatement(Program::GetAndIncreaseStatementNumber(), var,
                        "main");
  CheckEndOfStatement(line);
  return read_stmt;
}

std::string ReadStatementParser::ExtractVariableName(Line &line) const {
  auto print_keyword_itr =
      std::find_if(std::begin(line), std::end(line), [&](Token *const p) {
        return p->GetValue() == "read";
      });

  if (print_keyword_itr != line.begin()) {
    throw SyntaxErrorException("Read statement should start with print keyword");
  }

  if (line.size() < 2) {
    throw SyntaxErrorException("Read statement does not have a variable");
  }

  return line[1]->GetValue();

}

void ReadStatementParser::CheckEndOfStatement(Line &line) const {
  if ((*prev(line.end()))->GetValue() != ";") {
    throw SyntaxErrorException("AssignStatement does not end with ;");
  }

  if (line.size() > 3) {
    throw SyntaxErrorException("Too many tokens in a PrintStatement");
  }
}