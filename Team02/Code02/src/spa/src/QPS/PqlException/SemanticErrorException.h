#pragma once
#include <iostream>

class SemanticErrorException : public std::exception {
 public:
  char* what();
};
