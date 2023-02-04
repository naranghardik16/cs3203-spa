#pragma once
#include "DesignExtractor.h"

DesignExtractor::DesignExtractor() {};

void DesignExtractor::ExtractDesign(Program *program) {
  EntityExtractor *entity_extractor = new EntityExtractor();
  Program::ProcListContainer procedures = program->GetProcedureList();

  for (Procedure *p : procedures) {
    p->Accept(entity_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
//    for (Statement *s : statements) {
//
//    }
  }
}