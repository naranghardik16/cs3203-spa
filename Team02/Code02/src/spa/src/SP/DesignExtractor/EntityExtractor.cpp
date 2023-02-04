#pragma once
#include "EntityExtractor.h"

void EntityExtractor::VisitProcedure(Procedure *procedure) {
  PkbTypes::PROCEDURE p = procedure->GetProcedureName();
  pkb_write_facade_->AddProcedure(p);
}
