#include <algorithm>
#include <string>
#include <queue>
#include <stack>

#include "NextStore.h"
#include "core/cfg_model/CfgNode.h"

NextStore::NextStore() = default;

NextStore::~NextStore() = default;

void NextStore::setProcedureToCfgRootNodeMap(std::unordered_map<PkbTypes::PROCEDURE, std::shared_ptr<CfgNode>> ptonode) {
  this->procedure_name_to_cfg_node_map_ = ptonode;
}

void NextStore::setStatementNumberToCfgRootNodeMap(std::unordered_map<PkbTypes::STATEMENT_NUMBER,
                                                           std::shared_ptr<CfgNode>> stonode) {
  this->statement_number_to_cfg_node_map_ = stonode;
}

void NextStore::extractNextRelations() {
  for (const auto& p: this->procedure_name_to_cfg_node_map_) {
    std::unordered_set<std::string> visited;
    std::stack<std::shared_ptr<CfgNode>> s;

    s.push(p.second);
    int prev_last = -1;

    while (!s.empty()) {
      std::shared_ptr<CfgNode> current = s.top();
      s.pop();
      visited.insert(current->GetStringRepresentation());

      std::vector<int> statements = current->GetNodeStmts();
      if (statements.empty()) continue;

      if (prev_last != -1) this->next_store_.insert(std::to_string(prev_last), std::to_string(statements[0]));

      for (int i = 0; i < statements.size() - 1; ++i) {
        this->next_store_.insert(std::to_string(statements[i]),
                                 std::to_string(statements[i + 1]));
      }

      prev_last = statements[statements.size() - 1];

      if (!(visited.count(current->GetNodeTrans()[true]->GetStringRepresentation()) > 0)) {
        s.push(current->GetNodeTrans()[true]);
      }

      if (current->GetNodeTrans().count(false) > 0 &&
          !(visited.count(current->GetNodeTrans()[false]->GetStringRepresentation()) > 0)) {
        s.push(current->GetNodeTrans()[false]);
      }
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
