#pragma once
#include <iostream>
#include "SpaException.h"

class SyntaxErrorException : public SpaException {
 public:
  SyntaxErrorException();
  explicit SyntaxErrorException(std::string_view);
  std::string_view what();
};
