#pragma

#include "Statement.h"
#include "Procedure.h"

class CallStatement : public Statement {
 public:
  CallStatement(int statement_number, Procedure proc, std::string in_scope_proc);
  ~CallStatement() = default;
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  [[nodiscard]] string GetProcedureName() const;

 private:
  Procedure procedure_;
};