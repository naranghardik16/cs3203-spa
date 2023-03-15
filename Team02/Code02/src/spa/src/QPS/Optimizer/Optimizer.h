#pragma once

#include "ClauseGroup.h"
#include <algorithm>

class Optimizer {
 private:
  std::unordered_map<std::string, std::string> map_;
  std::string Find(std::string syn);
  void Union(const std::shared_ptr<ClauseSyntax>& clause);

 public:
  std::vector<std::shared_ptr<ClauseGroup>> GetClauseGroups(const ClauseSyntaxPtrList& clause_list);
};
