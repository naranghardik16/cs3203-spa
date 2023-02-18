#include "StatementParserFactory.h"

shared_ptr<StatementParser> StatementParserFactory::GetStatementParser(std::deque<
    StatementParserFactory::Line> &tokens) {
  auto line = tokens.front();
  if (CheckStatementType(line, "if")) {
    return make_shared<IfStatementParser>();
  } else if (CheckStatementType(line, "print")) {
    return make_shared<PrintStatementParser>();
  } else if (CheckStatementType(line, "read")) {
    return make_shared<ReadStatementParser>();
  } else if (CheckStatementType(line, "while")) {
    return make_shared<WhileStatementParser>();
  } else if (CheckStatementType(line, "=")) {
    return make_shared<AssignStatementParser>();
  }
  for (auto token : line) {
    cout << token->GetValue() << " ";
  }
  cout << endl;
  throw SemanticErrorException("Unknown Statement type");
}
bool StatementParserFactory::CheckStatementType(StatementParserFactory::Line &line,
                                                std::string_view type_to_check) {
  auto entity_itr =
      std::find_if(std::begin(line), std::end(line), [&](shared_ptr<Token> const p) {
        return p->GetValue() == type_to_check;
      });
  return entity_itr != std::end(line);
}