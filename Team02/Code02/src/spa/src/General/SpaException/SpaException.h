#pragma once
#include <iostream>

class SpaException : public std::exception {
 public:
  SpaException() = default;
  SpaException(std::string_view message);
  virtual std::string_view what() = 0;

 protected:
  std::string message_;
};
