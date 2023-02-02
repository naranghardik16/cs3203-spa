#include "StubPkb.h"

std::unordered_set<std::string> StubPkb::GetVariables() {
  std::unordered_set<std::string> variable_set({"a", "b", "c"});
  return variable_set;
}

std::unordered_set<std::string> StubPkb::GetStatements() {
  std::unordered_set<std::string> statement_set({"1", "2", "3"});
  return statement_set;
}

std::unordered_set<std::string> StubPkb::GetReadStatements() {
  std::unordered_set<std::string> read_set({"4", "5", "6"});
  return read_set;
}

std::unordered_set<std::string> StubPkb::GetPrintStatements() {
  std::unordered_set<std::string> print_set({"6", "7", "8"});
  return print_set;
}

std::unordered_set<std::string> StubPkb::GetCallStatements() {
  std::unordered_set<std::string> call_set({"9", "10", "11"});
  return call_set;
}

std::unordered_set<std::string> StubPkb::GetWhileStatements() {
  std::unordered_set<std::string> while_set({"12", "13", "14"});
  return while_set;
}
std::unordered_set<std::string> StubPkb::GetIfStatements() {
  std::unordered_set<std::string> if_set({"15", "16", "18"});
  return if_set;
}

std::unordered_set<std::string> StubPkb::GetAssignStatements() {
  std::unordered_set<std::string> assign_set({"19", "20", "21"});
  return assign_set;
}

std::unordered_set<std::string> StubPkb::GetConstants() {
  std::unordered_set<std::string> constant_set({"22", "23", "24"});
  return constant_set;
}

std::unordered_set<std::string> StubPkb::GetProcedures() {
  std::unordered_set<std::string> p_set({"eval", "parse", "validate"});
  return p_set;
}