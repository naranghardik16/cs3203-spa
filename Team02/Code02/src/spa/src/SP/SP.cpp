#include "SP.h"

SP::SP() {};

void SP::ProcessSIMPLE(istream &source, PKB *pkb) {
  try {
    Tokenizer *tokenizer = new Tokenizer();
    Parser::TokenStream *tokens = tokenizer->Tokenize(source);

    Parser *parser = new Parser();
    Program program = parser->ParseSource(*tokens);

    DesignExtractor *design_extractor = new DesignExtractor(pkb);
    design_extractor->ExtractDesign(&program);
  } catch (SpaException *e) {
    cout << e->what();
  }
}