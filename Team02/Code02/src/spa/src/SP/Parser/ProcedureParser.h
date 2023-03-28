#pragma once

#include "core/model/Procedure.h"
#include "EntityParser.h"
#include "General/SpaException/SyntaxErrorException.h"
#include "StatementParserFactory.h"
#include "SP/Util/SPConstants.h"

class ProcedureParser : public EntityParser<Procedure> {
 public:
  shared_ptr<Procedure> ParseEntity(TokenStream &tokens) override;
  static std::string ExtractProcName(Line &line);
  static bool IsProcedureEnd(Line &line);
 private:
  inline static const int k_min_tokens_ = 2;
};