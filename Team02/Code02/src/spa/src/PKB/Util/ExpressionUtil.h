#pragma once

#include <unordered_set>

#include "PKB/Types/PkbTypes.h"
#include "core/model/Expression.h"

class ExpressionUtil {
 public:
  std::unordered_set<PkbTypes::VARIABLE> retrieveAllVariablesFromExpression(Expression* expression) {
    std::unordered_set<PkbTypes::VARIABLE> result;
    if (expression->GetExpressionType() == "variable") {
      result.insert(expression->GetName());
    } else {
    }

    return {};
  }

  std::unordered_set<PkbTypes::CONSTANT> retrieveAllConstantsFromExpression(Expression* expression) {
    std::unordered_set<PkbTypes::VARIABLE> result;
    return {};
  }

  std::string flatten(Expression expression) {
    return {};
  }
};

