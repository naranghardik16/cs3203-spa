#pragma once

#include "./core/model/Procedure.h"
#include "core/cfg_model/Cfg.h"
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
#include "./ParserVisitor.h"

class CfgExtractor : public ParserVisitor {
 public:
  CfgExtractor(shared_ptr<Cfg> cfg);
  void VisitArithmeticalOperation(shared_ptr<ArithmeticOperation> arith_operation) override;
  void VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) override;
  void VisitConditionalOperation(shared_ptr<ConditionalOperation> cond_operation) override;
  void VisitPrintStatement(shared_ptr<PrintStatement> print_statement) override;
  void VisitReadStatement(shared_ptr<ReadStatement> read_statement) override;
  void VisitCallStatement(shared_ptr<CallStatement> call_statement) override;
  void VisitRelationalOperation(shared_ptr<RelationalOperation> rel_operation) override;
  void VisitIfStatement(shared_ptr<IfStatement> if_statement) override;
  void VisitWhileStatement(shared_ptr<WhileStatement> while_statement) override;
  void VisitProcedure(shared_ptr<Procedure> procedure) override;
  void VisitVariable(shared_ptr<Variable> variable) override;
  void VisitConstant(shared_ptr<Constant> constant) override;
 private:
  void ProcessStatements(const Procedure::StmtListContainer &statements);
  void AddTransitionAndUpdate(shared_ptr<CfgNode> new_node, bool value);
  void AddCfgForStmt(int stmt_number);
  shared_ptr<Cfg> cfg_;
  string cur_proc_name_;
  shared_ptr<CfgNode> cur_cfg_node_;
  const int no_nodes_ = 0;
};