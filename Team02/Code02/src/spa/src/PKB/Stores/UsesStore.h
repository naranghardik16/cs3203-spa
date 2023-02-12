#pragma once

#include <string>
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"
#include "PKB/Util/PairHasherUtil.h"


class UsesStore {
 public:
  UsesStore();
  ~UsesStore();

  void addStatementUsingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);
  void addProcedureUsingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);

  std::unordered_set<PkbTypes::VARIABLE> retrieveAllVariablesUsedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number);
  std::unordered_set<PkbTypes::VARIABLE> retrieveAllVariablesUsedByAProcedure(PkbTypes::PROCEDURE procedure);
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair> retrieveStatementVariablePairs();
  std::unordered_set<std::pair<PkbTypes::PROCEDURE, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair> retrieveProcedureVariablePairs();
  bool hasUsesRelationBetweenStatementAndVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);
  bool hasUsesRelationBetweenProcedureAndVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);
  std::unordered_set<PkbTypes::PROCEDURE> retrieveAllProceduresThatUse();

 protected:
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE> uses_statement_variable_;
  ManyToManyStore<PkbTypes::PROCEDURE, PkbTypes::VARIABLE> uses_procedure_variable_;




};