#include "SP.h"

SP::SP() {};

void SP::ProcessSIMPLE(istream &source, shared_ptr<PKB> pkb) {
  try {
    shared_ptr<Tokenizer> tokenizer = make_shared<Tokenizer>();
    shared_ptr<Parser::TokenStream> tokens = tokenizer->Tokenize(source);

    shared_ptr<Parser> parser = make_shared<Parser>();
    shared_ptr<Program> program = parser->ParseSource(*tokens);

    shared_ptr<SPSemanticValidator> validator = make_shared<SPSemanticValidator>();
    validator->ValidateProgram(program);

    shared_ptr<DesignExtractor>
        design_extractor = make_shared<DesignExtractor>(pkb);
    design_extractor->ExtractDesign(program);
  } catch (SpaException &e) {
    cout << e.what() << endl;
  }
}