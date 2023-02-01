#pragma once
#include "SyntaxErrorException.h"

SyntaxErrorException::SyntaxErrorException() : SpaException("Syntax Error ") {}

SyntaxErrorException::SyntaxErrorException(std::string_view message)
    : SpaException(message) {}

std::string_view SyntaxErrorException::what() {
  return message_;
}