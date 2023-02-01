#pragma once
#include "ClauseSyntax.h"

typedef std::pair<std::string, std::pair<std::string, std::string>> SyntaxPair;

ClauseSyntax::ClauseSyntax(SyntaxPair pair) {
  value_ = pair.first;
  first_parameter_ = pair.second.first;
  second_parameter_ = pair.second.second;
}

std::string ClauseSyntax::GetEntity() {
  return value_;
}

std::string ClauseSyntax::GetFirstParameter() {
  return first_parameter_;
}

std::string ClauseSyntax::GetSecondParameter() {
  return second_parameter_;
}

bool ClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  return this->GetEntity() == other.GetEntity() && this->GetFirstParameter() == other.GetFirstParameter() &&
    this->GetSecondParameter() == other.GetSecondParameter();
}