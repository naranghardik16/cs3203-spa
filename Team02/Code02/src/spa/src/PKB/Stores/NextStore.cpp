#include <algorithm>
#include <queue>
#include <stack>
#include <string>

#include "core/cfg_model/CfgNode.h"
#include "NextStore.h"

NextStore::NextStore() = default;

NextStore::~NextStore() = default;

void NextStore::setProcedureToCfgRootNodeMap(std::unordered_map<PkbTypes::PROCEDURE,
                                             std::shared_ptr<CfgNode>> ptonode) {
  this->procedure_name_to_cfg_node_map_ = ptonode;
}

void NextStore::setStatementNumberToCfgRootNodeMap(std::unordered_map<PkbTypes::STATEMENT_NUMBER,
                                                           std::shared_ptr<CfgNode>> stonode) {
  this->statement_number_to_cfg_node_map_ = stonode;
}

void NextStore::extractNextRelations() {
  for (const auto& p: this->procedure_name_to_cfg_node_map_) {
    std::unordered_set<std::string> visited;
    std::stack<std::pair<int, std::shared_ptr<CfgNode>>> s;

    s.push(std::make_pair(-1, p.second));

    while (!s.empty()) {
      auto ps = s.top();
      int prev_stmt = ps.first;
      auto current = ps.second;
      s.pop();

      if (current->GetNodeStmts().size() == 0 && current->GetNodeTrans().count(true) == 0) {
        continue;
      }

      std::cout << current->GetStringRepresentation() << std::endl;

      std::vector<int> statements = current->GetNodeStmts();
      if (statements.empty() && current->GetNodeTrans().count(true) > 0) {
        s.push(std::make_pair(prev_stmt, current->GetNodeTrans()[true]));
        continue;
      }

      if (prev_stmt != -1) this->next_store_.insert(std::to_string(prev_stmt), std::to_string(statements[0]));

      for (int i = 0; i < statements.size() - 1; ++i) {
        this->next_store_.insert(std::to_string(statements[i]),
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

bool NextStore::hasNextRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                                PkbTypes::STATEMENT_NUMBER next_statement_number) {
  return this->next_store_.contains(std::move(statement_number), std::move(next_statement_number));
}

bool NextStore::hasAnyNextRelation() {
  return this->next_store_.length() > 0;
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
NextStore::retrieveAllNextPairs() {
  return this->next_store_.retrieveAll();
}

bool NextStore::hasNext(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->next_store_.containsKey(statement_number);
}

bool NextStore::hasNextBy(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->next_store_.containsValue(statement_number);
}

std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
NextStore::retrieveAllNextStarPairs() {
  std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>, PairHasherUtil::hash_pair>
  result;

  for (const auto& k: this->next_store_.retrieveAllKeys()) {
    std::stack<PkbTypes::STATEMENT_NUMBER> s;
    std::unordered_set<std::pair<PkbTypes::STATEMENT_NUMBER, PkbTypes::STATEMENT_NUMBER>,
        PairHasherUtil::hash_pair> visited;
    s.push(k);

    while (!s.empty()) {
      PkbTypes::STATEMENT_NUMBER current = s.top();
      s.pop();

      for (const auto& c: this->next_store_.retrieveFromKey(current)) {
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

bool NextStore::hasNextStarRelation(PkbTypes::STATEMENT_NUMBER statement_number,
                                    PkbTypes::STATEMENT_NUMBER next_statement_number) {
  std::stack<PkbTypes::STATEMENT_NUMBER> s;
  std::unordered_set<PkbTypes::STATEMENT_NUMBER> visited;
  s.push(statement_number);

  while (!s.empty()) {
    PkbTypes::STATEMENT_NUMBER current = s.top();
    s.pop();

    for (const auto &c: this->next_store_.retrieveFromKey(current)) {
      if (c == next_statement_number) return true;
      if (!(visited.count(c) > 0)) s.push(c);
    }
    visited.insert(current);
  }

  return false;
}

bool NextStore::hasNextStar(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->next_store_.containsKey(statement_number);
}

bool NextStore::hasNextStarBy(PkbTypes::STATEMENT_NUMBER statement_number) {
  return this->next_store_.containsValue(statement_number);
}
