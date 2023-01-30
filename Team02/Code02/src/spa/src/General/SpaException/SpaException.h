#pragma once
#include <iostream>

class SpaException : public std::exception {
 public:
  virtual char* what() = 0;
};
