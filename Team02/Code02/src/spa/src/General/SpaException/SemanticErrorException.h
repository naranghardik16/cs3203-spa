#pragma once
#include <iostream>
#include "SpaException.h"

class SemanticErrorException : public SpaException {
 public:
  SemanticErrorException();
  SemanticErrorException(std::string_view message);
  std::string_view what();
};
