#pragma once
#include "./core/model/Program.h"
#include "EntityExtractor.h"
#include "AbstractionExtractor.h"
#include "./PKB/PKB.h"

class DesignExtractor {
 private:
  PKB *pkb_;
 public:
  DesignExtractor(PKB *pkb);
  void ExtractDesign(Program *program);
};