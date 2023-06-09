#pragma once
#include "ParserVisitor.h"
#include "./core/model/Procedure.h"
#include "core/model/Constant.h"
#include "core/model/Variable.h"
#include "core/model/ArithmeticOperation.h"
#include "core/model/AssignStatement.h"
#include "core/model/ConditionalOperation.h"
#include "core/model/PrintStatement.h"
#include "core/model/ReadStatement.h"
#include "core/model/CallStatement.h"
#include "core/model/RelationalOperation.h"
#include "core/model/IfStatement.h"
#include "core/model/WhileStatement.h"
#include "./PKB/Interfaces/PkbWriteFacade.h"
#include "./PKB/Interfaces/PkbReadFacade.h"

class AbstractionExtractor : public ParserVisitor {
 public:
  AbstractionExtractor(shared_ptr<Pkb> pkb);
  void VisitArithmeticalOperation(shared_ptr<ArithmeticOperation> arith_operation) override {};
  void VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) override;
  void VisitConditionalOperation(shared_ptr<ConditionalOperation> cond_operation) override;
  void VisitPrintStatement(shared_ptr<PrintStatement> print_statement) override;
  void VisitReadStatement(shared_ptr<ReadStatement> read_statement) override;
  void VisitCallStatement(shared_ptr<CallStatement> call_statement) override;
  void VisitRelationalOperation(shared_ptr<RelationalOperation> rel_operation) override;
  void VisitIfStatement(shared_ptr<IfStatement> if_statement) override;
  void VisitWhileStatement(shared_ptr<WhileStatement> while_statement) override;
  void VisitProcedure(shared_ptr<Procedure> procedure) override {};
  void VisitVariable(shared_ptr<Variable> variable) override {};
  void VisitConstant(shared_ptr<Constant> constant) override {};
  void ExtractFollows(shared_ptr<Statement> prev_stmt, shared_ptr<Statement> curr_stmt);
  void SetIsExtractIndirectModifiesAndUsesTrue();

 private:
  shared_ptr<Pkb> pkb_;
  shared_ptr<PkbWriteFacade> pkb_write_facade_;
  shared_ptr<PkbReadFacade> pkb_read_facade_;
  shared_ptr<bool> is_extract_indirect_modifies_and_uses_;
  void ProcessStatements(const vector<shared_ptr<Statement>> &statements,
                         PkbTypes::STATEMENT_NUMBER parent);
  void ExtractParent(PkbTypes::STATEMENT_NUMBER parent, shared_ptr<Statement> child_stmt);
  void ExtractIndirectModifiesFromCallStatements(PkbTypes::PROCEDURE curr_proc, PkbTypes::VARIABLE variable);
  void ExtractIndirectUsesFromCallStatements(PkbTypes::PROCEDURE curr_proc, PkbTypes::VARIABLE variable);
  void ExtractIndirectModifies(PkbTypes::VARIABLE variable, PkbTypes::PROCEDURE stmt_proc);
  void ExtractIndirectUses(PkbTypes::VARIABLE variable, PkbTypes::PROCEDURE stmt_proc);
};