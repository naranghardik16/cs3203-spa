#pragma once

#include "Parser.h"

// TODO remove the below const
const std::string kProc = "Proc";

Program Parser::ParseSource(TokenStream &token) {

}

bool Parser::IsStatement(Line &line) {
  return !IsProcedure(line);
}

bool Parser::IsProcedure(Line &line) {
  return !line.empty() && line[0] == kProc;
}

