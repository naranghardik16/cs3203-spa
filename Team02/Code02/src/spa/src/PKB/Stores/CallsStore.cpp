#include "CallsStore.h"

CallsStore::CallsStore() = default;

CallsStore::~CallsStore() = default;

void CallsStore::AddCallsRelation(const Procedure& caller_procedure, const Procedure& callee_procedure) {
  this->calls_relation_store_.insert(caller_procedure, callee_procedure);
}

void CallsStore::AddCallsStarRelation() {
  for (const auto& k: this->calls_relation_store_.retrieveAllKeys()) {
    ProcedureStack s;
    ProcedureProcedurePairSet visited;
    s.push(k);

    while (!s.empty()) {
      Procedure current = s.top();
      s.pop();

      for (const auto& c: this->calls_relation_store_.retrieveFromKey(current)) {
        if (!(visited.count(std::make_pair(k, c)) > 0)) {
          if (k != c) {
            this->calls_star_relation_store_.insert(k, c);
            s.push(c);
            visited.insert(std::make_pair(k, c));
          }
        }
      }
    }
  }
}

void CallsStore::AddCallStatementToProcedure(const StatementNumber& statement_number, const Procedure& procedure) {
  this->procedure_to_call_statement_store_.insert(procedure, statement_number);
}

CallsStore::StatementNumberProcedurePairSet CallsStore::GetCallStatementToProcedurePairs() {
  StatementNumberProcedurePairSet
      result;

  for (const auto& p: this->procedure_to_call_statement_store_.retrieveAll()) {
    result.insert(std::make_pair(p.second, p.first));
  }

  return result;
}

CallsStore::ProcedureProcedurePairSet CallsStore::GetCallsPairs() {
  return this->calls_relation_store_.retrieveAll();
}

CallsStore::ProcedureProcedurePairSet CallsStore::GetCallsStarPairs() {
  return this->calls_star_relation_store_.retrieveAll();
}

bool CallsStore::HasCallsRelation(const Procedure& caller_procedure, const Procedure& callee_procedure) {
  return this->calls_relation_store_.contains(caller_procedure, callee_procedure);
}

bool CallsStore::HasCallsStarRelation(const Procedure& caller_procedure, const Procedure& callee_procedure) {
  return this->calls_star_relation_store_.contains(caller_procedure, callee_procedure);
}

bool CallsStore::HasCallsRelation() {
  return this->calls_relation_store_.length() > 0;
}

bool CallsStore::HasCallsStarRelation() {
  return this->calls_star_relation_store_.length() > 0;
}

bool CallsStore::HasCallsStarRelation(const Procedure& procedure) {
  return !this->calls_star_relation_store_.retrieveFromValue(procedure).empty();
}

bool CallsStore::HasCallsStarRelationBy(const Procedure& procedure) {
  return !this->calls_star_relation_store_.retrieveFromKey(procedure).empty();
}

CallsStore::StatementNumberSet CallsStore::GetCallStatementsFromProcedure(const Procedure& procedure) {
  return this->procedure_to_call_statement_store_.retrieveFromKey(procedure);
}

