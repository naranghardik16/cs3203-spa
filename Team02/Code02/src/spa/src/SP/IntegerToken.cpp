//
// Created by Kai Qi Yong on 29/1/23.
//
#include "IntegerToken.h"

bool IntegerToken::Equals(IntegerToken *other) {
  return this->GetValue() == other->GetValue() == 0;
}