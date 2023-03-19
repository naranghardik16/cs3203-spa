#pragma once
#include "./core/model/Program.h"
#include "EntityExtractor.h"
#include "AbstractionExtractor.h"
#include "CfgExtractor.h"
#include "./PKB/Pkb.h"

class DesignExtractor {
 private:
  shared_ptr<Pkb> pkb_;
  shared_ptr<Cfg> cfg_;
 public:
  DesignExtractor(shared_ptr<Pkb> pkb_, shared_ptr<Cfg> cfg);
  void ExtractDesign(shared_ptr<Program> program);
};