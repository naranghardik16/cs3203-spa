#pragma once
#include <string>

typedef std::pair<std::string, std::pair<std::string, std::string>> SyntaxPair;
class ClauseSyntax {
  std::string value_;
  std::string first_parameter_;
  std::string second_parameter_;
 public:
  explicit ClauseSyntax(SyntaxPair pair);
  std::string GetEntity();
  std::string GetFirstParameter();
  std::string GetSecondParameter();
  virtual bool Equals(ClauseSyntax &other) = 0;
};
