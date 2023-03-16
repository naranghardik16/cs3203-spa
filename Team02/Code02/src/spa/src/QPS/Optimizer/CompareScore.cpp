#include "CompareScore.h"

bool CompareScore::operator()(std::shared_ptr<ClauseSyntax> const& c1, std::shared_ptr<ClauseSyntax>  const& c2) {
  bool c1_has_lower_syn_count = c1->GetSynonymCount() < c2->GetSynonymCount();
  bool c1_c2_has_equal_syn_count = c1->GetSynonymCount() == c2->GetSynonymCount();
  bool c1_has_lower_clause_type_score = c1->GetClauseScore(declaration_map_) <
      c2->GetClauseScore(declaration_map_);
  bool c1_c2_has_equal_clause_type_score = c1->GetClauseScore(declaration_map_) == c2->GetClauseScore
      (declaration_map_);
  bool c1_has_lower_arg_type_score = c1->GetArgumentScore(declaration_map_) <
      c2->GetArgumentScore(declaration_map_);

  if (c1_has_lower_syn_count) {
    return false;
  } else if (c1_has_lower_clause_type_score) {
    return false;
  } else if (c1_has_lower_arg_type_score) {
    return false;
  } else {
    return true;
  }
}
