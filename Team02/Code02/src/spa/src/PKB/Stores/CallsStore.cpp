#include "CallsStore.h"

CallsStore::CallsStore() = default;

CallsStore::~CallsStore() = default;

void CallsStore::AddCallsRelation(const Procedure &caller_procedure, const Procedure &callee_procedure) {
  this->calls_relation_store_.insert(caller_procedure, callee_procedure);
}

void CallsStore::AddCallsStarRelation() {
  ProcedureProcedurePairSet result = TransitiveRelationUtil::GetTransitiveRelations(this->GetCallsPairs());
  std::for_each(result.begin(), result.end(), [&](auto &p) {
    this->calls_star_relation_store_.insert(p.first, p.second);
  });
}

void CallsStore::AddCallStatementToProcedure(const StatementNumber &statement_number, const Procedure &procedure) {
  this->procedure_to_call_statement_store_.insert(procedure, statement_number);
}

CallsStore::StatementNumberProcedurePairSet CallsStore::GetCallStatementToProcedurePairs() {
  StatementNumberProcedurePairSet
      result;

  for (const auto &p : this->procedure_to_call_statement_store_.retrieveAll()) {
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

bool CallsStore::HasCallsRelation(const Procedure &caller_procedure, const Procedure &callee_procedure) {
  return this->calls_relation_store_.contains(caller_procedure, callee_procedure);
}

bool CallsStore::HasCallsStarRelation(const Procedure &caller_procedure, const Procedure &callee_procedure) {
  return this->calls_star_relation_store_.contains(caller_procedure, callee_procedure);
}

bool CallsStore::HasCallsRelation() {
  return this->calls_relation_store_.length() > 0;
}

bool CallsStore::HasCallsStarRelation() {
  return this->calls_star_relation_store_.length() > 0;
}

bool CallsStore::HasCallsStarRelation(const Procedure &procedure) {
  return !this->calls_star_relation_store_.retrieveFromValue(procedure).empty();
}

bool CallsStore::HasCallsStarRelationBy(const Procedure &procedure) {
  return !this->calls_star_relation_store_.retrieveFromKey(procedure).empty();
}

CallsStore::StatementNumberSet CallsStore::GetCallStatementsFromProcedure(const Procedure &procedure) {
  return this->procedure_to_call_statement_store_.retrieveFromKey(procedure);
}

CallsStore::Procedure CallsStore::GetProcedureFromStatement(const StatementNumber &statement_number) {
  return this->procedure_to_call_statement_store_.retrieveFromValue(statement_number);
}

