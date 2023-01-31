#include "SuchThatClauseSyntax.h"

SuchThatClauseSyntax::SuchThatClauseSyntax(SyntaxPair pair) : ClauseSyntax(pair) {}

bool SuchThatClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  SuchThatClauseSyntax *sc = dynamic_cast<SuchThatClauseSyntax*>(&other);
  if (sc) {
    return (this->GetEntity() == sc->GetEntity()) && (this->GetFirstParameter() == sc->GetFirstParameter()) &&
        (this->GetSecondParameter() == sc->GetSecondParameter());
  }
  return false;
}
