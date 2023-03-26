#include "CallStatementParser.h"

shared_ptr<Statement> CallStatementParser::ParseEntity(TokenStream &tokens) {
  auto line = tokens.front();
  tokens.pop_front();
  std::string extracted_proc_name = ExtractProcedureName(line);
  Procedure proc(extracted_proc_name);
  auto call_stmt =
      make_shared<CallStatement>(Program::GetAndIncreaseStatementNumber(), proc,
                                 GetProcName());
  CheckEndOfStatement(line);
  return call_stmt;
}

std::string CallStatementParser::ExtractProcedureName(Line &line) const {
  auto call_keyword_itr =
      std::find_if(std::begin(line), std::end(line), [&](shared_ptr<Token> const p) {
        return p->GetValue() == sp_constants::k_call_stmt_;
      });

  if (call_keyword_itr != line.begin()) {
    throw SyntaxErrorException("Call statement should start with call keyword");
  }

  if (line.size() < 2) {
    throw SyntaxErrorException("Call statement does not have a procedure");
  }

  if (line[1]->GetType() != NAME) {
    throw SyntaxErrorException("var_name should be a NAME");
  }

  return line[1]->GetValue();
}

void CallStatementParser::CheckEndOfStatement(Line &line) const {
  if ((*prev(line.end()))->GetType() != SEMICOLON) {
    throw SyntaxErrorException("CallStatement does not end with ;");
  }

  if (line.size() > k_max_tokens_) {
    throw SyntaxErrorException("Too many tokens in a CallStatement");
  }
}
