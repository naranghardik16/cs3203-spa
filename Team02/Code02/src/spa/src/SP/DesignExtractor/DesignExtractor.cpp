#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(shared_ptr<Pkb> pkb, shared_ptr<Cfg> cfg) {
  pkb_ = pkb;
  cfg_ = cfg;
}

void DesignExtractor::ExtractDesign(shared_ptr<Program> program) {
  auto pkb_write_facade = make_shared<PkbWriteFacade>(*pkb_);
  shared_ptr<EntityExtractor>
      entity_extractor = make_shared<EntityExtractor>(pkb_);
  shared_ptr<AbstractionExtractor>
      abstraction_extractor = make_shared<AbstractionExtractor>(pkb_);
  shared_ptr<CfgExtractor> cfg_extractor = make_shared<CfgExtractor>(cfg_);

  Program::ProcListContainer procedures = program->GetProcedureList();

  for (shared_ptr<Procedure> p : procedures) {
    p->Accept(entity_extractor);
    p->Accept(abstraction_extractor);
    p->Accept(cfg_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
    shared_ptr<Statement> prev_stmt = nullptr;
    for (shared_ptr<Statement> s : statements) {
      if (prev_stmt != nullptr) {
        abstraction_extractor->ExtractFollows(prev_stmt, s);
      }
      s->Accept(entity_extractor);
      s->Accept(abstraction_extractor);
      s->Accept(cfg_extractor);
      prev_stmt = s;
    }
  }
  
  pkb_write_facade->AddCallsStarRelation();
  pkb_write_facade->AddFollowsStarRelation();
  pkb_write_facade->AddParentStarRelation();
  pkb_write_facade->AddCfg(cfg_);

  abstraction_extractor->SetIsExtractIndirectModifiesAndUsesTrue();
  for (shared_ptr<Procedure> p : procedures) {
    Procedure::StmtListContainer statements = p->GetStatementList();
    for (shared_ptr<Statement> s : statements) {
      s->Accept(abstraction_extractor);
    }
  }
}
