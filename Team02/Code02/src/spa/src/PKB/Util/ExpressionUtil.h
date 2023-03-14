#pragma once

#include <stack>
#include <unordered_set>
#include <memory>

#include "core/model/Expression.h"
#include "PKB/Types/PkbTypes.h"

class ExpressionUtil {
 public:
  /**
   * Retrieves the set of variables that are a part of the given expression.
   *
   * @param expression - The expression whose variables are to be extracted.
   * @return An unordered set of variables.
   */
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

  /**
   * Retrieves the set of constants that are a part of the given expression.
   *
   * @param expression - The expression whose constants are to be extracted.
   * @return An unordered set of constants.
   */
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

  /**
   * Flattens the given expression into a string.
   *
   * @param expression - The expression to be flattened.
   * @return The string representing the flattened expression tree.
   */
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

  static bool hasSubExpression(shared_ptr<Expression> expression, std::shared_ptr<Expression> sub_expression) {
    if (!sub_expression || !expression) return false;
    if (expression->operator==(*sub_expression)) return true;

    auto children = expression->GetArguments();
    if (!children) return false;

    return hasSubExpression(children->first, sub_expression) || hasSubExpression(children->second, sub_expression);
  }
};

