#pragma once
#include "ParserVisitor.h"
#include "./core/model/Procedure.h"
#include "core/model/Constant.h"
#include "core/model/Variable.h"
#include "core/model/AssignStatement.h"
#include "core/model/PrintStatement.h"
#include "core/model/ReadStatement.h"

class AbstractionExtractor : public ParserVisitor {
 public:
  AbstractionExtractor(PKB *pkb);
  void VisitAssignStatement(AssignStatement *assign_statement) override;
  void VisitPrintStatement(PrintStatement *print_statement) override;
  void VisitReadStatement(ReadStatement *read_statement) override;
  void VisitProgram(Program *program);
  void VisitProcedure(Procedure *procedure) override;
  void VisitVariable(Variable *variable) override;
  void VisitConstant(Constant *constant) override;
  void VisitStatement(Statement *statement);
  void VisitExpression(Expression *expression);
 private:
  //TODO: Design Extractor should have one pkb and write_face
  PKB *pkb_;
  PkbWriteFacade *pkb_write_facade_;
};