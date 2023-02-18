#pragma  once
#include <vector>

#include "core/model/Statement.h"
#include "Entity.h"

class Procedure : public Entity, public enable_shared_from_this<Procedure> {
 public:
  typedef std::vector<std::shared_ptr<Statement>> StmtListContainer;
  explicit Procedure(std::string proc_name);
  ~Procedure();
  void AddToStatementList(shared_ptr<Statement> stmt);
  void Accept(shared_ptr<ParserVisitor> visitor) override;
  [[nodiscard]] StmtListContainer GetStatementList() const;
  [[nodiscard]] std::string GetProcedureName() const;

 private:
  std::string procedure_name_;
  StmtListContainer statement_list_;
};