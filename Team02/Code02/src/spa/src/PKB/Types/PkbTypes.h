#pragma once

#include <string>
#include <unordered_set>
#include <variant>

class PkbTypes {
 public:
  /**
   * Wrapper typedef around string to represent a procedure.
   */
  typedef std::string PROCEDURE;

  /**
   * Wrapper typedef around string to represent a variable.
   */
  typedef std::string VARIABLE;

  /**
  * Wrapper typedef around string to represent a constant.
  */
  typedef std::string CONSTANT;

  /**
  * Wrapper typedef around string to represent a statement number.
  */
  typedef std::string STATEMENT_NUMBER;

  /**
  * Wrapper typedef around string to represent a field that belongs to a statement, like variable or constant.
  */
  typedef std::string FIELD;

  /**
  * Wrapper typedef around size_t to represent an index for single sets.
  */
  typedef std::size_t INDEX;
};
