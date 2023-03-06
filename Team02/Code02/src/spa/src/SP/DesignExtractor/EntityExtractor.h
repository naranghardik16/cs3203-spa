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

using namespace std;

class EntityExtractor : public ParserVisitor {
 public:
  typedef vector<shared_ptr<Statement>> StmtListContainer;
  EntityExtractor(shared_ptr<PKB> pkb);
  void VisitArithmeticalOperation(shared_ptr<ArithmeticOperation> arith_operation) override;
  void VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) override;
  void VisitConditionalOperation(shared_ptr<ConditionalOperation> cond_operation) override;
  void VisitPrintStatement(shared_ptr<PrintStatement> print_statement) override;
  void VisitReadStatement(shared_ptr<ReadStatement> read_statement) override;
  void VisitCallStatement(shared_ptr<CallStatement> call_statement) override;
  void VisitRelationalOperation(shared_ptr<RelationalOperation> rel_operation) override;
  void VisitIfStatement(shared_ptr<IfStatement> if_statement) override;
  void VisitWhileStatement(shared_ptr<WhileStatement> while_statement) override;
  void VisitProgram(shared_ptr<Program> program);
  void VisitProcedure(shared_ptr<Procedure> procedure) override;
  void VisitVariable(shared_ptr<Variable> variable) override;
  void VisitConstant(shared_ptr<Constant> constant) override;
  void VisitStatement(shared_ptr<Statement> statement);
  void VisitExpression(shared_ptr<Expression> expression);

 private:
  void ProcessStatements(const StmtListContainer &statements);
  shared_ptr<PKB> pkb_;
  shared_ptr<PkbWriteFacade> pkb_write_facade_;
};