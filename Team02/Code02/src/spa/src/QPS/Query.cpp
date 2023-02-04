#pragma once
#include "QPS/Query.h"

Synonym Query::GetSynonym() {
  return synonym_;
}

Map Query::GetDeclarationMap() {
  return declaration_map_;
}

ClauseSyntaxPtrList Query::GetClauseSyntaxPtrList() {
  return syntax_pair_list_;
}