#pragma once
#include <iostream>
#include "SpaException.h"

class SemanticErrorException : public SpaException {
 public:
  char* what();
};
