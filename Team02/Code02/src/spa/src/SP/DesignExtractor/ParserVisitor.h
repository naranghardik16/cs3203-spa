#pragma once
//#include "./core/model/Program.h"
//#include "./core/model/Procedure.h"
//#include "./core/model/Statement.h"
//#include "./core/model/Expression.h"
#include "./PKB/Interfaces/PkbWriteFacade.h"

class Program;
class Procedure;
class Statement;
class Expression;
class Variable;
class Constant;

class ParserVisitor {
 public:
  void VisitProgram(Program *program);
  virtual void VisitProcedure(Procedure *procedure) = 0;
  virtual void VisitVariable(Variable *variable) = 0;
  virtual void VisitConstant(Constant *constant) = 0;
  void VisitStatement(Statement *statement);
  void VisitExpression(Expression *expression);
};