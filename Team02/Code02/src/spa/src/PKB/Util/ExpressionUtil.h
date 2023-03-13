#pragma once

#include <stack>
#include <unordered_set>
#include <memory>

#include "core/model/Expression.h"
#include "PKB/Types/PkbTypes.h"

class ExpressionUtil {
 public:
  static std::unordered_set<PkbTypes::VARIABLE>
      retrieveAllVariablesFromExpression(std::shared_ptr<Expression> expression) {
    std::unordered_set<PkbTypes::VARIABLE> result;
    std::stack<std::shared_ptr<Expression>> s;

    s.push(expression);

    while (!s.empty()) {
      auto current = s.top();
      s.pop();

      if (current.get() == NULL) continue;

      if (current->GetExpressionType() == "variable") {
        result.insert(current->GetName());
      } else {
        if (current->GetExpressionType() != "constant") {
          auto children = current->GetArguments();

          s.push(children->first);
          s.push(children->second);
        }
      }
    }

    return result;
  }

  static std::unordered_set<PkbTypes::CONSTANT>
      retrieveAllConstantsFromExpression(std::shared_ptr<Expression> expression) {
    std::unordered_set<PkbTypes::CONSTANT> result;
    std::stack<std::shared_ptr<Expression>> s;

    s.push(expression);

    while (!s.empty()) {
      auto current = s.top();
      s.pop();

      if (!current) continue;

      if (current->GetExpressionType() == "constant") {
        result.insert(current->GetName());
      } else {
        if (current->GetExpressionType() != "variable") {
          auto children = current->GetArguments();

          s.push(children->first);
          s.push(children->second);
        }
      }
    }

    return result;
  }

  static std::string prefixFlatten(std::shared_ptr<Expression> expression) {
    if (!expression) return "";

    std::string ret;
    ret += expression->GetName();
    auto children = expression->GetArguments();

    if (!children) return ret;

    ret += " " + prefixFlatten(children->first);
    ret += " " + prefixFlatten(children->second);

    return "[" + ret + "]";
  }

};

