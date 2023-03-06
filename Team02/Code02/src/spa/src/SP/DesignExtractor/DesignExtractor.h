#pragma once
#include "./core/model/Program.h"
#include "EntityExtractor.h"
#include "AbstractionExtractor.h"
#include "CfgExtractor.h"
#include "./PKB/PKB.h"

class DesignExtractor {
 private:
  shared_ptr<PKB> pkb_;
 public:
  DesignExtractor(shared_ptr<PKB> pkb);
  void ExtractDesign(shared_ptr<Program> program);
};