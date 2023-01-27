//
// Created by isabe on 24/01/2023.
#pragma once
#include <iostream>

class SyntaxErrorException : public std::exception {
 public:
  char* what();
};
