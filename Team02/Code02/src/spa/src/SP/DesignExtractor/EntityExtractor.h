#pragma once
#include "ParserVisitor.h"
#include "./core/model/Procedure.h"
#include "core/model/Constant.h"
#include "core/model/Variable.h"

class EntityExtractor : public ParserVisitor {
 private:
  PKB pkb_ = PKB();
  PkbWriteFacade *pkb_write_facade_ = new PkbWriteFacade(pkb_);
 public:
  void VisitProgram(Program *program);
  void VisitProcedure(Procedure *procedure);
  void VisitVariable(Variable *variable);
  void VisitConstant(Constant *constant);
  void VisitStatement(Statement *statement);
  void VisitExpression(Expression *expression);
};