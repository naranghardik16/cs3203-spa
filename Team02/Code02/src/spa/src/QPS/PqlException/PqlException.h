#pragma once
#include <iostream>

class PqlException : public std::exception {
 public:
  virtual char* what() = 0;
};
