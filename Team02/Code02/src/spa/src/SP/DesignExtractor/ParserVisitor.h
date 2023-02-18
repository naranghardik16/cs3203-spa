#pragma once
//#include "./core/model/Program.h"
//#include "./core/model/Procedure.h"
//#include "./core/model/Statement.h"
//#include "./core/model/Expression.h"
//#include "./PKB/Interfaces/PkbWriteFacade.h"

class ArithmeticOperation;
class AssignStatement;
class ConditionalOperation;
class PrintStatement;
class ReadStatement;
class RelationalOperation;
class IfStatement;
class WhileStatement;
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
  virtual void VisitArithmeticalOperation(ArithmeticOperation *arith_operation) = 0;
  virtual void VisitAssignStatement(AssignStatement *assign_statement) = 0;
  virtual void VisitConditionalOperation(ConditionalOperation *cond_operation) = 0;
  virtual void VisitPrintStatement(PrintStatement *print_statement) = 0;
  virtual void VisitReadStatement(ReadStatement *read_statement) = 0;
  virtual void VisitRelationalOperation(RelationalOperation *rel_operation) = 0;
  virtual void VisitIfStatement(IfStatement *if_statement) = 0;
  virtual void VisitWhileStatement(WhileStatement *while_statement) = 0;
  void VisitExpression(Expression *expression);
};