#pragma once
#include <sstream>
#include "SP/Tokenizer/Tokenizer.h"
#include "./SP/DesignExtractor/DesignExtractor.h"
#include "PKB/PKB.h"

class SP {
 public:
  SP();
  void ProcessSIMPLE(istream &source, PKB *pkb);
};
