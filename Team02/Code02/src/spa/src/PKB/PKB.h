#pragma once

#include "PKB/Stores/EntityStore.h"

class PKB {
 public:
  static EntityStore *entity_store_;
  PKB();
  ~PKB();

  friend class PkbWriteFacade;
  friend class PkbReadFacade;

  std::unordered_set<std::string> GetVariables();
  std::unordered_set<std::string> GetStatements();
  std::unordered_set<std::string> GetReadStatements();
  std::unordered_set<std::string> GetPrintStatements();
  std::unordered_set<std::string> GetCallStatements();
  std::unordered_set<std::string> GetWhileStatements();
  std::unordered_set<std::string> GetIfStatements();
  std::unordered_set<std::string> GetAssignStatements();
  std::unordered_set<std::string> GetConstants();
  std::unordered_set<std::string> GetProcedures();
};

