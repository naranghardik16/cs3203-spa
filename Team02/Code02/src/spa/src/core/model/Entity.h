#pragma once
#include "./SP/DesignExtractor/ParserVisitor.h"

class Entity {
 public:
  virtual void Accept(ParserVisitor* visitor) = 0;
};