#include "ClauseSyntax.h"

typedef std::pair<std::string, std::pair<std::string, std::string>> SyntaxPair;
class SuchThatClauseSyntax : public ClauseSyntax {
 public:
  SuchThatClauseSyntax(SyntaxPair pair);
  bool Equals(ClauseSyntax &other);
};
