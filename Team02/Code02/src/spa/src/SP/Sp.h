#pragma once
#include <sstream>
#include "SP/Tokenizer/Tokenizer.h"
#include "./SP/DesignExtractor/DesignExtractor.h"
#include "PKB/Pkb.h"
#include "SP/Validator/SPSemanticValidator.h"

using namespace std;

class Sp {
 public:
  Sp();
  bool ProcessSIMPLE(istream &source, shared_ptr<Pkb> pkb, shared_ptr<Cfg> cfg);
};
