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
#include "core/model/RelationalOperation.h"
#include "core/model/IfStatement.h"
#include "core/model/WhileStatement.h"

class EntityExtractor : public ParserVisitor {
 public:
  typedef std::vector<Statement *> StmtListContainer;
  EntityExtractor(PKB *pkb);
  void VisitArithmeticalOperation(ArithmeticOperation *arith_operation) override;
  void VisitAssignStatement(AssignStatement *assign_statement) override;
  void VisitConditionalOperation(ConditionalOperation *cond_operation) override;
  void VisitPrintStatement(PrintStatement *print_statement) override;
  void VisitReadStatement(ReadStatement *read_statement) override;
  void VisitRelationalOperation(RelationalOperation *rel_operation) override;
  void VisitIfStatement(IfStatement *if_statement) override;
  void VisitWhileStatement(WhileStatement *while_statement) override;
  void VisitProgram(Program *program);
  void VisitProcedure(Procedure *procedure) override;
  void VisitVariable(Variable *variable) override;
  void VisitConstant(Constant *constant) override;
  void VisitStatement(Statement *statement);
  void VisitExpression(Expression *expression);

 private:
  void ProcessStatements(const StmtListContainer &statements);
  PKB *pkb_;
  PkbWriteFacade *pkb_write_facade_;
};