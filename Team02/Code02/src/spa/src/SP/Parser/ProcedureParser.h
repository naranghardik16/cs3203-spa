#pragma once

#include "core/model/Procedure.h"
#include "EntityParser.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "StatementParserFactory.h"

class ProcedureParser : public EntityParser<Procedure> {
 public:
  Procedure *ParseEntity(TokenStream &tokens) override;
  static std::string ExtractProcName(Line &line);
  static inline bool IsProcedureEnd(Line &line);
};