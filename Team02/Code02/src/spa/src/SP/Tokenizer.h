#ifndef SPA_SRC_SPA_SRC_TOKENIZER_H_
#define SPA_SRC_SPA_SRC_TOKENIZER_H_

#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <cctype>
#include "NameToken.h"
#include "IntegerToken.h"
#include "PunctuationToken.h"
#include "ArithmeticOperatorToken.h"
#include "RelationalOperatorToken.h"
#include "ConditionalOperatorToken.h"
using namespace std;

class Tokenizer {
 public:
  Tokenizer();
  vector<vector<Token>>* tokenize(istream &stream);
};
#endif //SPA_SRC_SPA_SRC_TOKENIZER_H_



