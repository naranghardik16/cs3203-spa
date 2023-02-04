#pragma once

#include <memory>
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Clause/ClauseSyntax.h"
#include "QPS/Util/QueryUtil.h"
#include "QPS/Util/PQLConstants.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "General/SpaException/SemanticErrorException.h"

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
   * Syntax handle method to be implemented in derived class.
   *
   * @param clause contains parameters of either such that clause or pattern clause
  */
  virtual void HandleSyntax(std::shared_ptr<ClauseSyntax> clause);

  /*
   * Semantic handle method to be implemented in derived class.
   *
   * @param clause contains parameters of either such that clause or pattern clause
  */
  virtual void HandleSemantic(std::shared_ptr<ClauseSyntax> clause, Map &declaration);
};