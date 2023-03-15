#pragma once

#include <memory>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include "General/SpaException/SemanticErrorException.h"
#include "./core/model/Program.h"
#include "./core/model/CallStatement.h"
#include "./core/model/WhileStatement.h"
#include "./core/model/IfStatement.h"


using namespace std;

class SPSemanticValidator {
 public:
  SPSemanticValidator();
  void AddProcedure(string proc_name);
  void AddCallsRelationship(string caller_proc_name, string callee_proc_name);
  void ValidateProgram(shared_ptr<Program> program);
 private:
  int no_of_procedures_;
  unordered_map<string, int> procedures_;
  vector<pair<string, string>> calls_relationship_;
  vector<list<int>> adj_list_;
  bool IsProcedureExist(string proc_name);
  void ProcessProgram(shared_ptr<Program> program);
  void ProcessStatements(Procedure::StmtListContainer statements, string proc_name);
  void PopulateAdjacencyList();
  void ValidateNoRecursiveAndCyclicCalls();
  bool IsCyclicUtil(int v, shared_ptr<vector<bool>> visited, shared_ptr<vector<bool>> rec_stack);
};