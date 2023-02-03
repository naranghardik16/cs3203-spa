#pragma once
#include <vector>
//#include "Entity.h"
#include "core/model/Procedure.h"

class Program {
 public:
  typedef std::vector<Procedure *> ProcListContainer;
  Program();

  void AddToProcedureList(Procedure *proc);
  [[nodiscard]] ProcListContainer GetProcedureList();

 private:
  ProcListContainer procedure_list_;

};