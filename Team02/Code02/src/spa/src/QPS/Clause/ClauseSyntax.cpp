#pragma once
#include "ClauseSyntax.h"

ClauseSyntax::ClauseSyntax(SyntaxPair pair) {
  pair_ = pair;
}

std::string ClauseSyntax::GetEntity() {
  return pair_.first;
}

std::string ClauseSyntax::GetFirstParameter() {
  return pair_.second[0];
}

std::string ClauseSyntax::GetSecondParameter() {
  return pair_.second[1];
}

std::string ClauseSyntax::GetThirdParameter() {
  return pair_.second[2];
}

SyntaxPair ClauseSyntax::GetSyntaxPair() {
  return pair_;
}

bool ClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  return this->GetEntity() == other.GetEntity() && this->GetFirstParameter() == other.GetFirstParameter() &&
    this->GetSecondParameter() == other.GetSecondParameter();
}