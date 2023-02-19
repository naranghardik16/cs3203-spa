#pragma once
#include <memory>

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

using namespace std;

class ParserVisitor {
 public:
  void VisitProgram(shared_ptr<Program> program);
  virtual void VisitProcedure(shared_ptr<Procedure> procedure) = 0;
  virtual void VisitVariable(shared_ptr<Variable> variable) = 0;
  virtual void VisitConstant(shared_ptr<Constant> constant) = 0;
  virtual void VisitArithmeticalOperation(shared_ptr<ArithmeticOperation> arith_operation) = 0;
  virtual void VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) = 0;
  virtual void VisitConditionalOperation(shared_ptr<ConditionalOperation> cond_operation) = 0;
  virtual void VisitPrintStatement(shared_ptr<PrintStatement> print_statement) = 0;
  virtual void VisitReadStatement(shared_ptr<ReadStatement> read_statement) = 0;
  virtual void VisitRelationalOperation(shared_ptr<RelationalOperation> rel_operation) = 0;
  virtual void VisitIfStatement(shared_ptr<IfStatement> if_statement) = 0;
  virtual void VisitWhileStatement(shared_ptr<WhileStatement> while_statement) = 0;
  void VisitExpression(shared_ptr<Expression> expression);
};