#pragma once
#include "SemanticErrorException.h"

char* SemanticErrorException::what() {
  return "Semantic error";
}