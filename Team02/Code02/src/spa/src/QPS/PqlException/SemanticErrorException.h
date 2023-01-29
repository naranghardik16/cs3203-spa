#pragma once
#include <iostream>
#include "PqlException.h"

class SemanticErrorException : public PqlException {
 public:
  char* what();
};
