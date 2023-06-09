#pragma once
#include "QPS/Util/QPSTypeDefs.h"

/*!
 * Holds information from parsing the query given from user for the query evaluation
 */
class Query {
  private:
  SelectedSynonymTuple synonym_;
  Map declaration_map_;
  ClauseSyntaxPtrList syntax_pair_list_;

 public:
  Query(SelectedSynonymTuple synonym_tuple, Map declaration_map, ClauseSyntaxPtrList syntax_pair_list) {
    this->synonym_ = synonym_tuple;
    this->declaration_map_ = declaration_map;
    this->syntax_pair_list_ = syntax_pair_list;
  }

  /*!
   * A getter function to get the synonym that is being selected for
   */
  SelectedSynonymTuple GetSynonymTuple();

  /*!
 * A getter function to get the declaration map, which has the synonym as a key and design entity as value
 */
  Map GetDeclarationMap();

  /*!
 * A getter function to get the list of ClauseSyntax, which contains information parsed from the subclauses
 */
  ClauseSyntaxPtrList GetClauseSyntaxPtrList();

};
