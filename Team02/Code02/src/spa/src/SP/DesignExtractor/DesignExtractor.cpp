#include "DesignExtractor.h"

DesignExtractor::DesignExtractor(shared_ptr<PKB> pkb) {
  pkb_ = pkb;
//  cfg_ = cfg;
}

void DesignExtractor::ExtractDesign(shared_ptr<Program> program) {
  shared_ptr<EntityExtractor>
      entity_extractor = make_shared<EntityExtractor>(pkb_);
  shared_ptr<AbstractionExtractor>
      abstraction_extractor = make_shared<AbstractionExtractor>(pkb_);
//  shared_ptr<CfgExtractor> cfg_extracter = make_shared<CfgExtractor>(cfg_);

  Program::ProcListContainer procedures = program->GetProcedureList();
//   Extraction for CFG
//  for (shared_ptr<Procedure> &p : procedures) {
//    p->Accept(cfg_extracter);
//    auto statements = p->GetStatementList();
//    for (auto const &s : statements) {
//      s->Accept(cfg_extracter);
//    }
//  }

  for (shared_ptr<Procedure> p : procedures) {
    p->Accept(entity_extractor);
    p->Accept(abstraction_extractor);
    Procedure::StmtListContainer statements = p->GetStatementList();
    shared_ptr<Statement> prev_stmt = nullptr;
    for (shared_ptr<Statement> s : statements) {
      if (prev_stmt != nullptr) {
        abstraction_extractor->ExtractFollows(prev_stmt, s);
      }
      s->Accept(entity_extractor);
      s->Accept(abstraction_extractor);
      prev_stmt = s;
    }
  }

  auto pkb_write_facade_ = make_shared<PkbWriteFacade>(*pkb_);
  pkb_write_facade_->AddCallsStarRelation();

  for (shared_ptr<Procedure> p : procedures) {
    abstraction_extractor->SetIsExtractIndirectModifiesAndUsesTrue();
    Procedure::StmtListContainer statements = p->GetStatementList();
    for (shared_ptr<Statement> s : statements) {
      s->Accept(abstraction_extractor);
    }
  }

  /*
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
  */
}
