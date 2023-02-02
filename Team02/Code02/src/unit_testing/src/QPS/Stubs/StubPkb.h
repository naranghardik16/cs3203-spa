#include "PKB.h"

class StubPkb : public PKB {
  virtual std::unordered_set<std::string> GetVariables();
  virtual std::unordered_set<std::string> GetStatements();
  virtual std::unordered_set<std::string> GetReadStatements();
  virtual std::unordered_set<std::string> GetPrintStatements();
  virtual std::unordered_set<std::string> GetCallStatements();
  virtual std::unordered_set<std::string> GetWhileStatements();
  virtual std::unordered_set<std::string> GetIfStatements();
  virtual std::unordered_set<std::string> GetAssignStatements();
  virtual std::unordered_set<std::string> GetConstants();
  virtual std::unordered_set<std::string> GetProcedures();

};
