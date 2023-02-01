#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "General/SpaException/SyntaxErrorException.h"
#include "QPS/QPSTypeDefs.h"

/*
 * Handler base class.
 */
class Handler {
 private:
  std::shared_ptr<Handler> next_handler_;

 public:
  Handler();
  virtual ~Handler() = default;
  std::shared_ptr<Handler> SetNext(std::shared_ptr<Handler> handler);

  /*
   * Handle method to be implemented in derived class.
   *
   * @param declaration_map contains synonyms declared
   * @param clause_map contains either parameters of such that clause or pattern clause
  */
  virtual void Handle(Map &declaration, Map &clause);
};