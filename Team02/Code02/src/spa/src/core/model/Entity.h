#pragma once
#include "./SP/DesignExtractor/ParserVisitor.h"

/**
 * A Wrapper interface that can accept Visitors
 */
class Entity {
 public:
  virtual void Accept(shared_ptr<ParserVisitor> visitor) = 0;
};