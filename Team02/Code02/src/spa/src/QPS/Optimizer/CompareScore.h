#pragma once
#include "QPS/Util/PQLConstants.h"
#include "QPS/Clause/ClauseSyntax.h"
#include <tuple>

class CompareScore {
  Map declaration_map_;
 public:
  CompareScore(Map declaration_map) {
    declaration_map_ = declaration_map;
  }
  bool operator()(std::shared_ptr<ClauseSyntax> const& c1, std::shared_ptr<ClauseSyntax>  const& c2);
  virtual ~CompareScore() = default;
};
