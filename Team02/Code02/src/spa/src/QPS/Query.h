#pragma once
#include "PKB.h"
#include "QPS/Util/QPSTypeDefs.h"

class Query {
  private:
  Synonym synonym_;
  Map declaration_map_;
  ClauseSyntaxPtrList syntax_pair_list_;

 public:
  Query(Synonym synonym, Map declaration_map, ClauseSyntaxPtrList syntax_pair_list) {
    this->synonym_ = synonym;
    this->declaration_map_ = declaration_map;
    this->syntax_pair_list_ = syntax_pair_list;
  }

  Synonym GetSynonym();

  Map GetDeclarationMap();

  ClauseSyntaxPtrList GetClauseSyntaxPtrList();

};
