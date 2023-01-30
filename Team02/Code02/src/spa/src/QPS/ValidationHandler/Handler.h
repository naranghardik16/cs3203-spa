#pragma once

#include <string>
#include <unordered_map>
#include "General/SpaException/SyntaxErrorException.h"

typedef std::unordered_map<std::string, std::string> Map;
/*
 * Handler base class.
 */
class Handler {
 private:
  Handler *next_handler_;

 public:
  Handler();
  virtual ~Handler() = default;
  Handler *SetNext(Handler *handler);

  /*
   * Handle method to be implemented in derived class. Default to throw syntax error.
   *
   * @param declaration_map contains synonyms declared
   * @param clause_map contains either parameters of such that clause or pattern clause
  */
  virtual void Handle(Map &declaration, Map &clause);
};