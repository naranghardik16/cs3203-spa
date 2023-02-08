#pragma once

#include <string>
#include <unordered_set>
#include <variant>

class PkbTypes {
 public:
  typedef std::string PROCEDURE;
  typedef std::string VARIABLE;
  typedef std::string CONSTANT;
  typedef std::string STATEMENT_NUMBER;
  typedef std::string FIELD;


  typedef std::unordered_set<VARIABLE> VARIABLE_SET;
  typedef std::variant<VARIABLE_SET, PROCEDURE> MODIFIES;

  typedef std::size_t INDEX;
};
