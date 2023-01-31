#pragma once
#include <iostream>
#include "SpaException.h"

class SyntaxErrorException : public SpaException {
 public:
  char* what();
};
