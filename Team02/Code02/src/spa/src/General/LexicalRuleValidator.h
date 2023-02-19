#pragma once
#include <iostream>

class LexicalRuleValidator {

 public:

  static bool IsLetter(char c);

  static bool IsDigit(char c);

  static bool IsNzDigit(char c);

  static bool IsStartWithLetterThenMadeOfOptionalLetterOrNumbers(std::string s);

  static bool IsIdent(std::string s);

  static bool IsName(std::string s);

  static bool IsInteger(std::string s);



};
