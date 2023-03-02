#pragma once

#include "core/model/Statement.h"
#include "core/model/Procedure.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "EntityParser.h"
#include "ExpressionParserFactory.h"

class StatementParser : public EntityParser<Statement> {
 public:
  virtual shared_ptr<Statement> ParseEntity(TokenStream &tokens) = 0;
  string GetProcName();
  void SetProcName(string proc_name);
 private:
  string proc_name_;
};