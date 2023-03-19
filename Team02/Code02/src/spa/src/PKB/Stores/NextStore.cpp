#include "NextStore.h"

NextStore::NextStore() = default;

NextStore::~NextStore() = default;

void NextStore::SetProcedureToCfgNodeMap(const ProcedureToCfgNodeMap& ptonode) {
  this->procedure_name_to_cfg_node_map_ = ptonode;
}

void NextStore::SetStatementNumberToCfgNodeMap(const StatementToCfgNodeMap& stonode) {
  this->statement_number_to_cfg_node_map_ = stonode;
}

void NextStore::AddNextRelations() {
  for (const auto& p: this->procedure_name_to_cfg_node_map_) {
    StatementNumberSet visited;
    StatementCfgNodePtrStack s;

    s.push(std::make_pair(-1, p.second));

    while (!s.empty()) {
      auto ps = s.top();
      int prev_stmt = ps.first;
      auto current = ps.second;
      s.pop();

      if (current->GetNodeStmts().size() == 0 && current->GetNodeTrans().count(true) == 0) {
        continue;
      }

      std::vector<int> statements = current->GetNodeStmts();
      if (statements.empty() && current->GetNodeTrans().count(true) > 0) {
        s.push(std::make_pair(prev_stmt, current->GetNodeTrans()[true]));
        continue;
      }

      if (prev_stmt != -1) this->next_relation_store_.insert(std::to_string(prev_stmt), std::to_string(statements[0]));

      for (int i = 0; i < statements.size() - 1; ++i) {
        this->next_relation_store_.insert(std::to_string(statements[i]),
                                          std::to_string(statements[i + 1]));
      }

      prev_stmt = statements[statements.size() - 1];

      if (visited.count(current->GetStringRepresentation()) > 0) continue;

      if (current->GetNodeTrans().count(true) > 0) {
        s.push(std::make_pair(prev_stmt, current->GetNodeTrans()[true]));
      }

      if (current->GetNodeTrans().count(false) > 0) {
        s.push(std::make_pair(prev_stmt, current->GetNodeTrans()[false]));
      }

      visited.insert(current->GetStringRepresentation());
    }
  }
}

bool NextStore::HasNextRelation(const StatementNumber& statement_number, const StatementNumber& next_statement_number) {
  return this->next_relation_store_.contains(statement_number, next_statement_number);
}

bool NextStore::HasNextRelation() {
  return this->next_relation_store_.length() > 0;
}

NextStore::StatementStatementPairSet NextStore::GetNextPairs() {
  return this->next_relation_store_.retrieveAll();
}

bool NextStore::HasNextRelation(const StatementNumber& statement_number) {
  return this->next_relation_store_.containsKey(statement_number);
}

bool NextStore::HasNextRelationBy(const StatementNumber& statement_number) {
  return this->next_relation_store_.containsValue(statement_number);
}

NextStore::StatementStatementPairSet NextStore::GetNextStarPairs() {
  StatementStatementPairSet result;

  for (const auto& k: this->next_relation_store_.retrieveAllKeys()) {
    StatementNumberStack s;
    StatementStatementPairSet visited;
    s.push(k);

    while (!s.empty()) {
      StatementNumber current = s.top();
      s.pop();

      for (const auto& c: this->next_relation_store_.retrieveFromKey(current)) {
        if (!(visited.count(std::make_pair(k, c)) > 0)) {
          result.insert(std::make_pair(k, c));
          s.push(c);
          visited.insert(std::make_pair(k, c));
        }
      }
    }
  }

  return result;
}

bool NextStore::HasNextStarRelation(const StatementNumber& statement_number, const StatementNumber& next_statement_number) {
  StatementNumberStack s;
  StatementNumberSet visited;
  s.push(statement_number);

  while (!s.empty()) {
    StatementNumber current = s.top();
    s.pop();

    for (const auto &c: this->next_relation_store_.retrieveFromKey(current)) {
      if (c == next_statement_number) return true;
      if (!(visited.count(c) > 0)) s.push(c);
    }
    visited.insert(current);
  }

  return false;
}

bool NextStore::HasNextStarRelation(const StatementNumber& statement_number) {
  return this->next_relation_store_.containsKey(statement_number);
}

bool NextStore::HasNextStarRelationBy(const StatementNumber& statement_number) {
  return this->next_relation_store_.containsValue(statement_number);
}
