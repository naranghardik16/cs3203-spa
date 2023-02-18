#pragma  once
#include <vector>

#include "core/model/Statement.h"
#include "Entity.h"

class Procedure : public Entity {
 public:
  typedef std::vector<Statement *> StmtListContainer;
  explicit Procedure(std::string proc_name);
  ~Procedure();
  void AddToStatementList(Statement *stmt);
  void Accept(ParserVisitor *visitor) override;
  [[nodiscard]] StmtListContainer GetStatementList() const;
  [[nodiscard]] std::string GetProcedureName() const;

 private:
  std::string procedure_name_;
  StmtListContainer statement_list_;
};