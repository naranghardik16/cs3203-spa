#pragma once
#include "./core/model/Program.h"
#include "EntityExtractor.h"
#include "AbstractionExtractor.h"

class DesignExtractor {
 public:
  DesignExtractor();
  void ExtractDesign(Program *program);
};