#pragma once
#include "SyntaxErrorException.h"

char* SyntaxErrorException::what() {
  return "SyntaxError";
}