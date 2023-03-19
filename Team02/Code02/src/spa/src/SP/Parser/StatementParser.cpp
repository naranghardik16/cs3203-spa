#include "StatementParser.h"

string StatementParser::GetProcName() {
  return proc_name_;
}

void StatementParser::SetProcName(string proc_name) {
  proc_name_ = proc_name;
}
