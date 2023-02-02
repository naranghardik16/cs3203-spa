#include "ClauseSyntax.h"

class PatternClauseSyntax : public ClauseSyntax {
 public:
  PatternClauseSyntax(SyntaxPair pair);
  bool Equals(ClauseSyntax &other);
};
