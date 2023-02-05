#include "TestWrapper.h"

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper *WrapperFactory::wrapper = 0;
AbstractWrapper *WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

PKB *pkb;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
  pkb = new PKB();
}

// Read all the lines in the file
vector<string> read_all_lines(string const& filename)
{
  ifstream file(filename);

  vector<string> lines;
  while(not file.eof() && not file.fail()) {
    // Get the line
    std::string line;
    std::getline(file, line);
    // Add the line into the vector
    lines.push_back(std::move(line));
  }
  return lines;
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
  // call your parser to do the parsing
  // ...rest of your code...
  Tokenizer* tokenizer = new Tokenizer();

//  // Read all the lines in the file we wrote:
//  vector<string> lines = read_all_lines(filename);
  std::ifstream input(filename);

  Parser::TokenStream *tokens = tokenizer->Tokenize(input);

  Parser *parser = new Parser();
  Program program = parser->ParseSource(*tokens);

  DesignExtractor *design_extractor = new DesignExtractor(pkb);
  design_extractor->ExtractDesign(&program);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string> &results) {
// call your evaluator to evaluate the query here
  // ...code to evaluate query...
//  PKB pkb;
  std::shared_ptr<PkbReadFacade> pkb_read = std::make_shared<PkbReadFacade>(*pkb);

  Qps::ProcessQuery(query, results, pkb_read);
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
