#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(shared_ptr<PKB> pkb) {
  pkb_ = pkb;
}

void DesignExtractor::ExtractDesign(shared_ptr<Program> program) {
  shared_ptr<EntityExtractor> entity_extractor = make_shared<EntityExtractor>(pkb_);
  shared_ptr<AbstractionExtractor> abstraction_extractor = make_shared<AbstractionExtractor>(pkb_);
  Program::ProcListContainer procedures = program->GetProcedureList();

  for (shared_ptr<Procedure> p : procedures) {
    p->Accept(entity_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
    for (shared_ptr<Statement> s : statements) {
      s->Accept(entity_extractor);
    }
  }
  for (shared_ptr<Procedure> p : procedures) {
    p->Accept(abstraction_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
    shared_ptr<Statement> prev_stmt = nullptr;
    for (shared_ptr<Statement> s : statements) {
      if (prev_stmt != nullptr) {
        abstraction_extractor->ExtractFollows(prev_stmt, s);
      }
      s->Accept(abstraction_extractor);
      prev_stmt = s;
    }
  }

}
