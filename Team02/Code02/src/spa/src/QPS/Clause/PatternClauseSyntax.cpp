#include "PatternClauseSyntax.h"

PatternClauseSyntax::PatternClauseSyntax(SyntaxPair pair) : ClauseSyntax(pair) {}

bool PatternClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  PatternClauseSyntax *pc = dynamic_cast<PatternClauseSyntax*>(&other);
  if (pc) {
    return (this->GetEntity() == pc->GetEntity()) && (this->GetFirstParameter() == pc->GetFirstParameter()) &&
        (this->GetSecondParameter() == pc->GetSecondParameter());
  }
  return false;
}