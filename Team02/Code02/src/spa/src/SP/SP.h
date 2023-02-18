#pragma once
#include <sstream>
#include "SP/Tokenizer/Tokenizer.h"
#include "./SP/DesignExtractor/DesignExtractor.h"
#include "PKB/PKB.h"

using namespace std;

class SP {
 public:
  SP();
  void ProcessSIMPLE(istream &source, shared_ptr<PKB> pkb);
};
