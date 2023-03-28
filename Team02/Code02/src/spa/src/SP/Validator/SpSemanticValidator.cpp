#include "SpSemanticValidator.h"

SpSemanticValidator::SpSemanticValidator() {
  no_of_procedures_ = 0;
}

void SpSemanticValidator::AddProcedure(string proc_name) {
  // check whether the proc_name exist before adding
  if (IsProcedureExist(proc_name)) {
    throw SemanticErrorException(
        "A program cannot have 2 procedures with the same name");
  }
  procedures_[proc_name] = no_of_procedures_;
  no_of_procedures_++;
}

bool SpSemanticValidator::IsProcedureExist(string proc_name) {
  return procedures_.find(proc_name) != procedures_.end();
}

void SpSemanticValidator::AddCallsRelationship(string caller_proc_name,
                                               string callee_proc_name) {
  calls_relationship_.push_back(make_pair(caller_proc_name, callee_proc_name));
}

void SpSemanticValidator::ValidateProgram(shared_ptr<Program> program) {
  ProcessProgram(program);
  PopulateAdjacencyList();
  ValidateNoRecursiveAndCyclicCalls();
}

void SpSemanticValidator::ProcessProgram(shared_ptr<Program> program) {
  Program::ProcListContainer procedures = program->GetProcedureList();
  for (shared_ptr<Procedure> p : procedures) {
    AddProcedure(p->GetProcedureName());
    ProcessStatements(p->GetStatementList(), p->GetProcedureName());
  }
}

void SpSemanticValidator::ProcessStatements(Procedure::StmtListContainer statements,
                                            string proc_name) {
  for (shared_ptr<Statement> s : statements) {
    if (s->GetStatementType() == sp_constants::k_call_stmt_) {
      auto call_stmt = dynamic_pointer_cast<CallStatement>(s);
      AddCallsRelationship(proc_name, call_stmt->GetProcedureName());
      continue;
    }

    // for container statements need to loop through their statement list as well
    if (s->GetStatementType() == sp_constants::k_while_stmt_) {
      auto while_stmt = dynamic_pointer_cast<WhileStatement>(s);
      ProcessStatements(while_stmt->GetLoopStatements(), proc_name);
      continue;
    }
    if (s->GetStatementType() == sp_constants::k_if_stmt_) {
      auto if_stmt = dynamic_pointer_cast<IfStatement>(s);
      ProcessStatements(if_stmt->GetThenStatements(), proc_name);
      ProcessStatements(if_stmt->GetElseStatements(), proc_name);
      continue;
    }
  }
}

void SpSemanticValidator::PopulateAdjacencyList() {
  if (calls_relationship_.empty()) {
    return;
  }

  adj_list_.resize(procedures_.size());

  for (auto crls : calls_relationship_) {
    if (!IsProcedureExist(crls.second)) {
      throw SemanticErrorException(
          "A procedure cannot call a non-existing procedure");
    }
    auto position = procedures_.find(crls.first)->second;
    auto neighbour = procedures_.find(crls.second)->second;
    adj_list_[position].push_back(neighbour);
  }
}

// Solution below adapted from https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
void SpSemanticValidator::ValidateNoRecursiveAndCyclicCalls() {
  if (calls_relationship_.empty()) {
    return;
  }

  auto visited = make_shared<vector<bool>>();
  auto rec_stack = make_shared<vector<bool>>();
  // initial set up
  for (int i = 0; i < no_of_procedures_; i++) {
    (*visited).push_back(false);
    (*rec_stack).push_back(false);
  }

  for (int i = 0; i < no_of_procedures_; i++) {
    if (!(*visited)[i] && IsCyclicUtil(i, visited, rec_stack)) {
      throw SemanticErrorException("Recursive and cyclic calls are not allowed");
    }
  }
}

// Solution before adapted from https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
bool SpSemanticValidator::IsCyclicUtil(int v,
                                       shared_ptr<vector<bool>> visited,
                                       shared_ptr<vector<bool>> rec_stack) {
  if ((*visited)[v] || v >= adj_list_.size()) {
    return false;
  }

  // mark the current node as visited and part of recursion stack
  (*visited)[v] = true;
  (*rec_stack)[v] = true;

  // recur for all the vertices adjacent to the current vertex
  for (auto neighbour : adj_list_[v]) {
    if (!(*visited)[neighbour] && IsCyclicUtil(neighbour, visited, rec_stack)) {
      return true;
    } else if ((*rec_stack)[neighbour]) {
      return true;
    }
  }

  // remove the current vertex from recursion stack
  (*rec_stack)[v] = false;
  return false;
}
