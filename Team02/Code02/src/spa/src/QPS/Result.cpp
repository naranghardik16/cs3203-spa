#include "Result.h"

Result::Result(ResultHeader header, ResultTable table) : header_(header), table_(table) {}

void Result::JoinResult(std::shared_ptr<Result> result) {
  if (result->header_.empty() || this->header_.empty()) {
    return;
  }
  InterceptResult intercept = FindIntercept(this->header_, result->header_);
  ResultTable temp;

  for (auto &i : intercept.second) {
    this->header_.push_back(result->header_[i]);
  }

  if (result->table_.empty() || this->table_.empty()) {
    this->table_.clear();
    return;
  }

  for (auto &row : this->table_) {
    ResultTable join = FindMatch(row, result->table_, intercept);
    temp.insert(temp.end(), join.begin(), join.end());
  }
  this->table_ = temp;
}

std::unordered_set<std::string> Result::ProjectResult(SelectedSynonymTuple synonym_tuple) {
  std::unordered_set<std::string> output;

  std::vector<int> index_lst;
  for (auto &syn : synonym_tuple) {
    auto it = std::find(this->header_.begin(), this->header_.end(), syn);
    int index = it - this->header_.begin();
    index_lst.push_back(index);
  }

  for (auto &row : this->table_) {
    std::string result;
    for (auto &index : index_lst) {
      result += row[index] + " ";
    }
    output.insert(result.substr(0, result.length() - 1));
  }
  return output;
}

std::unordered_set<std::string> Result::ProjectResultForBoolean() {
  if (!this->table_.empty()) {
    return { "TRUE" };
  } else {
    return { "FALSE" };
  }
}

InterceptResult Result::FindIntercept(ResultHeader &r_1, ResultHeader &r_2) {
  Intercept intercept;
  NonIntercept non_intercept;
  for (int i = 0; i < r_2.size(); ++i) {
    auto it = std::find(r_1.begin(), r_1.end(), r_2[i]);
    if (it != r_1.end()) {
      int index = it - r_1.begin();
      intercept.emplace_back(index, i);
    } else {
      non_intercept.push_back(i);
    }
  }
  return {intercept, non_intercept};
}

ResultTable Result::FindMatch(ResultRow &row, ResultTable &table, InterceptResult &intercept) {
  ResultTable out;
  for (auto &r : table) {
    bool match = true;

    for (auto &p : intercept.first) {
      if (row[p.first] != r[p.second]) {
        match = false;
        break;
      }
    }

    if (match) {
      ResultRow new_row(row);
      for (auto &i : intercept.second) {
        new_row.push_back(r[i]);
      }
      out.push_back(new_row);

      if (intercept.second.empty()) {
        return out;
      }
    }
  }
  return out;
}
