#pragma once

#include <unordered_set>
#include <string>
#include "PKB/Types/PkbTypes.h"
#include "PKB/Util/PairHasherUtil.h"
#include "PKB/AbstractDataModels/ManyToManyStore.h"

class ModifiesStore {
 public:
  ModifiesStore();
  ~ModifiesStore();

  void addStatementModifyingVariable(PkbTypes::STATEMENT_NUMBER statement_number, PkbTypes::VARIABLE variable);
  void addProcedureModifyingVariable(PkbTypes::PROCEDURE procedure, PkbTypes::VARIABLE variable);

  std::unordered_set<PkbTypes::VARIABLE>
  retrieveAllVariablesModifiedByAStatement(PkbTypes::STATEMENT_NUMBER statement_number);

  std::unordered_set<PkbTypes::VARIABLE>
  retrieveAllVariablesModifiedByAProcedure(PkbTypes::PROCEDURE procedure);

  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
  retrieveStatementVariablePairs();

  std::unordered_set<std::pair<PkbTypes::PROCEDURE , PkbTypes::VARIABLE>, PairHasherUtil::hash_pair>
  retrieveProcedureVariablePairs();

  bool hasModifiesRelationBetweenStatementAndVariable(PkbTypes::STATEMENT_NUMBER statement_number,
                                                      PkbTypes::VARIABLE variable);

  bool hasModifiesRelationBetweenProcedureAndVariable(PkbTypes::PROCEDURE procedure,
                                                      PkbTypes::VARIABLE variable);

  std::unordered_set<PkbTypes::PROCEDURE> retrieveAllProceduresThatModify();
//  std::unordered_set<std::vector<std::string>> convert(std::vector<std::string> s);

 protected:
  ManyToManyStore<PkbTypes::STATEMENT_NUMBER, PkbTypes::VARIABLE> modifies_statement_variable_;
  ManyToManyStore<PkbTypes::PROCEDURE, PkbTypes::VARIABLE> modifies_procedure_variable_;
};

