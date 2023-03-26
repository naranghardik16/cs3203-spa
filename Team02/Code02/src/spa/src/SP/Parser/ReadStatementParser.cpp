#include "ReadStatementParser.h"

shared_ptr<Statement> ReadStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  std::string var_name = ExtractVariableName(line);
  Variable var(var_name);
  auto read_stmt =
      make_shared<ReadStatement>(Program::GetAndIncreaseStatementNumber(), var,
                                 GetProcName());
  CheckEndOfStatement(line);
  return read_stmt;
}

std::string ReadStatementParser::ExtractVariableName(Line &line) const {
  auto print_keyword_itr =
      std::find_if(std::begin(line), std::end(line), [&](shared_ptr<Token> const p) {
        return p->GetValue() == sp_constants::k_read_stmt_;
      });

  if (print_keyword_itr != line.begin()) {
    throw SyntaxErrorException("Read statement should start with read keyword");
  }

  if (line.size() < k_min_tokens_) {
    throw SyntaxErrorException("Read statement does not have a variable");
  }

  if (line[1]->GetType() != NAME) {
    throw SyntaxErrorException("var_name should be a NAME");
  }

  return line[1]->GetValue();
}

void ReadStatementParser::CheckEndOfStatement(Line &line) const {
  if ((*prev(line.end()))->GetType() != SEMICOLON) {
    throw SyntaxErrorException("ReadStatement does not end with ;");
  }

  if (line.size() > k_max_tokens) {
    throw SyntaxErrorException("Too many tokens in a ReadStatement");
  }
}
