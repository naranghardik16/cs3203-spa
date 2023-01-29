#pragma once
#include <iostream>
#include "PqlException.h"

class SyntaxErrorException : public PqlException {
 public:
  char* what();
};
