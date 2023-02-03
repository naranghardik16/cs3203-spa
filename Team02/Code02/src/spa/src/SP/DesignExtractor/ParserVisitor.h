#pragma once
#include "./core/model/Program.h"
#include "./core/model/Procedure.h"
#include "./core/model/Statement.h"
#include "./core/model/Expression.h"

class ParserVisitor {
 public:
  void VisitProgram(Program *program);
  void VisitProcedure(Procedure *procedure);
  void VisitStatement(Statement *statement);
  void VisitExpression(Expression *expression);
};