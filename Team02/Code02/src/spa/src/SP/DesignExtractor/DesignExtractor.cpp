#pragma once
#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(PKB *pkb) {
  pkb_ = pkb;
}

void DesignExtractor::ExtractDesign(Program *program) {
  EntityExtractor *entity_extractor = new EntityExtractor(pkb_);
  auto *abstraction_extractor = new AbstractionExtractor(pkb_);
  Program::ProcListContainer procedures = program->GetProcedureList();

  for (Procedure *p : procedures) {
    p->Accept(entity_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
    for (Statement *s : statements) {
      s->Accept(entity_extractor);
    }
  }

  for (Procedure *p : procedures) {
    p->Accept(abstraction_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
    for (Statement *s : statements) {
      s->Accept(abstraction_extractor);
    }
  }
}
