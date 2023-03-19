#pragma once

#include <memory>
#include <stack>
#include <unordered_set>

#include "core/model/Expression.h"
#include "PKB/Types/PkbTypes.h"

class ExpressionUtil {
 public:
  typedef std::unordered_set<PkbTypes::VARIABLE> VariableSet;
  typedef std::unordered_set<PkbTypes::CONSTANT> ConstantSet;
  typedef std::stack<std::shared_ptr<Expression>> ExpressionStack;
  typedef std::shared_ptr<Expression> ExpressionPtr;

  /**
   * Retrieves the set of variables that are a part of the given expression.
   *
   * @param expression - The expression whose variables are to be extracted.
   * @return An unordered set of variables.
   */
  static VariableSet GetAllVariablesFromExpression(const ExpressionPtr& expression) {
    VariableSet result;
    ExpressionStack s;

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
  static ConstantSet GetAllConstantsFromExpression(const ExpressionPtr& expression) {
    ConstantSet result;
    ExpressionStack s;

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
  static std::string PrefixFlatten(const ExpressionPtr& expression) {
    if (!expression) return "";

    std::string result;
    result += expression->GetName();
    auto children = expression->GetArguments();

    if (!children) return result;

    result += " " + PrefixFlatten(children->first);
    result += " " + PrefixFlatten(children->second);

    return "[" + result + "]";
  }

  /**
   * Checks if the given sub expression is a part of the given expression.
   *
   * @param expression - The expression to be checked to check membership against.
   * @param sub_expression - The expression whose membership is to be checked.
   * @return True if it exists, false otherwise.
   */
  static bool HasSubExpression(const ExpressionPtr& expression,
                               const ExpressionPtr& sub_expression) {
    if (!sub_expression || !expression) return false;
    if (expression->operator==(*sub_expression)) return true;

    auto children = expression->GetArguments();
    if (!children) return false;

    return HasSubExpression(children->first, sub_expression) || HasSubExpression(children->second, sub_expression);
  }
};

