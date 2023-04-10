#include "CompareScore.h"

bool CompareScore::operator()(std::shared_ptr<ClauseSyntax> const& c1, std::shared_ptr<ClauseSyntax>  const& c2) {
  auto c1_score_tuple = std::tuple{c1->GetSynonymCount(), c1->GetClauseScore(declaration_map_), c1->GetArgumentScore
                                   (declaration_map_)};
  auto c2_score_tuple = std::tuple{c2->GetSynonymCount(), c2->GetClauseScore(declaration_map_), c2->GetArgumentScore
      (declaration_map_)};
  return c2_score_tuple < c1_score_tuple;
}
