#include "CallsStore.h"
#include <iostream>
#include <stack>

CallsStore::CallsStore() = default;

CallsStore::~CallsStore() = default;

void CallsStore::addCallsRelation(PkbTypes::PROCEDURE caller_procedure, PkbTypes::PROCEDURE callee_procedure) {
  this->calls_store_.insert(caller_procedure, callee_procedure);
}

void CallsStore::addCallsStarRelation() {
  for (const auto& k: this->calls_store_.retrieveAllKeys()) {
    std::stack<PkbTypes::PROCEDURE> s;
    std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair> visited;
    s.push(k);

    while (!s.empty()) {
      PkbTypes::PROCEDURE current = s.top();
      s.pop();

      for (const auto& c: this->calls_store_.retrieveFromKey(current)) {
        if (!(visited.count(std::make_pair(k, c)) > 0)) {
          if (k != c) {
            this->calls_star_store_.insert(k, c);
            s.push(c);
            visited.insert(std::make_pair(k, c));
          }
        }
      }
    }
  }
//  for (const auto& k: this->calls_store_.retrieveAllKeys()) {
//    std::stack<PkbTypes::PROCEDURE> s;
//    std::unordered_set<PkbTypes::PROCEDURE> visited;
//    s.push(k);
//
//    while (!s.empty()) {
//      PkbTypes::PROCEDURE current = s.top();
//      s.pop();
//      visited.insert(current);
//
//      for (const auto& c: this->calls_store_.retrieveFromKey(current)) {
//        if (!(visited.count(c) > 0)) {
//          this->calls_star_store_.insert(k, c);
//          s.push(c);
//        }
//      }
//    }
//  }
}

void CallsStore::addCallStatementToProcedureName(PkbTypes::STATEMENT_NUMBER statement_number,
                                                 PkbTypes::PROCEDURE procedure) {
  this->procedure_to_call_store_.insert(procedure, statement_number);
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
CallsStore::retrieveAllCallStatementToProcedurePairs() {
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::PROCEDURE>, PairHasherUtil::hash_pair>
      result;

  for (const auto& p: this->procedure_to_call_store_.retrieveAll()) {
    result.insert(std::make_pair(p.second, p.first));
  }

  return result;
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

