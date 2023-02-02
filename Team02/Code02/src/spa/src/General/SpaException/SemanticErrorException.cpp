#pragma once
#include "SemanticErrorException.h"

SemanticErrorException::SemanticErrorException() : SpaException(
    "Semantic Exception") {}

SemanticErrorException::SemanticErrorException(std::string_view message)
    : SpaException(message) {}

std::string_view SemanticErrorException::what() {
  return message_;
}