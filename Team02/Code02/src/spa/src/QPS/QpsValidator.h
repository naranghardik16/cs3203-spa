#pragma once
#include <memory>
#include "ValidationHandler/SuchThatBaseHandler.h"
#include "ValidationHandler/StmtToStmtHandler.h"
#include "ValidationHandler/StmtProcToVarHandler.h"
#include "ValidationHandler/PatternHandler.h"
#include "QPS/Clause/ClauseSyntax.h";

typedef std::unordered_map<std::string, std::string> Map;

class QpsValidator {
 public:
  static void Validate(Map &declaration, Map &such_that_clause, Map &pattern_clause);
  static void ValidateSuchThat(Map &declaration, Map &clause);
  static void ValidatePattern(Map &declaration, Map &clause);
  //TODO To figure out validation -- this is dummy
  static void ValidateSubClause(Map &declaration, std::shared_ptr<ClauseSyntax> syntax);
};