#pragma once

#include "core/model/Procedure.h"
#include "EntityParser.h"

class ProcedureParser : public EntityParser<Procedure> {
 public:
  Procedure *ParseEntity(TokenStream &tokens) override;
 private:
  static std::string ExtractProcName(Line &line);
  static inline bool IsProcedureEnd(Line &line);
};