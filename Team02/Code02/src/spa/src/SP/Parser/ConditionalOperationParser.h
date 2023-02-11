#pragma once

#include "OperationParser.h"
#include "RelationalOperationParser.h"
#include "../../core/model/ConditionalOperation.h"
#include "../Token.h"
#include "../../General/SpaException/SyntaxErrorException.h"

using namespace std;

class ConditionalOperationParser : public OperationParser {
 public:
  ConditionalOperationParser() = default;
  Operation *Parse() override;
};
