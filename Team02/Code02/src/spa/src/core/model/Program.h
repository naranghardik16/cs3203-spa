#pragma once
#include <vector>
#include "core/model/Procedure.h"

class Program {
 public:
  typedef std::vector<Procedure *> ProcListContainer;
  Program();

  void AddToProcedureList(Procedure *proc);
  [[nodiscard]] ProcListContainer GetProcedureList();
  [[nodiscard]] static int GetAndIncreaseStatementNumber();

 private:
  ProcListContainer procedure_list_;
  static int statement_number_;
};