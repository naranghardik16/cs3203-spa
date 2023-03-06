#include "QPS/Query.h"

SelectedSynonymTuple Query::GetSynonymTuple() {
  return synonym_;
}

Map Query::GetDeclarationMap() {
  return declaration_map_;
}

ClauseSyntaxPtrList Query::GetClauseSyntaxPtrList() {
  return syntax_pair_list_;
}