#include "CallsStore.h"

CallsStore::CallsStore() = default;

CallsStore::~CallsStore() = default;

void CallsStore::addCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  this->calls_store_.insert(caller_procedure, callee_procedure);
  this->calls_star_store_.insert(caller_procedure, callee_procedure);

  std::unordered_set<PkbTypes::PROCEDURE> callers =
      this->calls_star_store_.retrieveFromValue(caller_procedure);

  while (!callers.empty()) {
    std::unordered_set<PkbTypes::PROCEDURE> updated_callers;
    for (const auto& p: callers) {
      std::unordered_set<PkbTypes::PROCEDURE> temp = this->calls_star_store_.retrieveFromValue(p);
      updated_callers.insert(temp.begin(), temp.end());
      this->calls_star_store_.insert(p, callee_procedure);
    }
    callers = updated_callers;
  }
}

void CallsStore::addCallStatementToProcedureName(PkbTypes::STATEMENT_NUMBER statement_number,
                                                 PkbTypes::PROCEDURE procedure) {
  this->procedure_to_call_store_.insert(procedure, statement_number);
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
CallsStore::retrieveAllCallStatementToProcedurePairs() {
  return this->procedure_to_call_store_.retrieveAll();
}

std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                   PairHasherUtil::hash_pair> CallsStore::retrieveAllCallsPairs() {
  return this->calls_store_.retrieveAll();
}

std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>,
                   PairHasherUtil::hash_pair> CallsStore::retrieveAllCallsStarPairs() {
  return this->calls_star_store_.retrieveAll();
}

bool CallsStore::hasCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  return this->calls_store_.contains(caller_procedure, callee_procedure);
}

bool CallsStore::hasCallsStarRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  return this->calls_star_store_.contains(caller_procedure, callee_procedure);
}

bool CallsStore::hasAnyCallsRelation() {
  return this->calls_store_.length() > 0;
}

bool CallsStore::hasAnyCallsStarRelation() {
  return this->calls_star_store_.length() > 0;
}

bool CallsStore::hasCallsStar(PkbTypes::PROCEDURE procedure) {
  return !this->calls_star_store_.retrieveFromValue(procedure).empty();
}

bool CallsStore::hasCallsStarBy(PkbTypes::PROCEDURE procedure) {
  return !this->calls_star_store_.retrieveFromKey(procedure).empty();
}

std::unordered_set<PkbTypes::STATEMENT_NUMBER>
    CallsStore::retrieveCallStatementsFromAProcedure(PkbTypes::PROCEDURE procedure) {
  return this->procedure_to_call_store_.retrieveFromKey(procedure);
}

bool CallsStore::hasCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  return this->calls_store_.contains(caller_procedure, callee_procedure);
}

bool CallsStore::hasCallsStarRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  return this->calls_star_store_.contains(caller_procedure, callee_procedure);
}

