#pragma once
#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(PKB *pkb) {
  pkb_ = pkb;
};

void DesignExtractor::ExtractDesign(Program *program) {
  EntityExtractor *entity_extractor = new EntityExtractor(pkb_);
  Program::ProcListContainer procedures = program->GetProcedureList();

  for (Procedure *p : procedures) {
    p->Accept(entity_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
    for (Statement *s : statements) {
      s->Accept(entity_extractor);
    }
  }
}