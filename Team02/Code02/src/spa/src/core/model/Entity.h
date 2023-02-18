#pragma once
#include "./SP/DesignExtractor/ParserVisitor.h"

class Entity {
 public:
  virtual void Accept(shared_ptr<ParserVisitor> visitor) = 0;
};