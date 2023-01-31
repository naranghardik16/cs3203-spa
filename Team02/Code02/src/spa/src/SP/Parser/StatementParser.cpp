#include "StatementParser.h"

Statement *StatementParser::ParseEntity(TokenStream &tokens) {
  auto stmt_parser = StatementParserFactory::GetStatementParser(tokens);
  
}