#pragma once

#include <string>
#include <unordered_set>
#include <variant>

class PkbTypes {
 public:
  typedef std::string PROCEDURE;
  typedef std::string VARIABLE;
  typedef std::string CONSTANT;
  typedef std::size_t LINE_NUMBER;

  typedef std::unordered_set<VARIABLE> VARIABLE_SET;
  typedef std::unordered_set<LINE_NUMBER> LINE_SET;
  typedef std::variant<VARIABLE_SET, PROCEDURE> MODIFIES;

  typedef uint64_t INDEX;
};
