#pragma once
#include <sstream>
#include "SP/Tokenizer/Tokenizer.h"
#include "./SP/DesignExtractor/DesignExtractor.h"
#include "PKB/PKB.h"
#include "SP/Validator/SPSemanticValidator.h"

using namespace std;

class SP {
 public:
  SP();
  bool ProcessSIMPLE(istream &source, shared_ptr<PKB> pkb);
};
