#include "Result.h"

Result::Result(ResultHeader header, ResultTable table) : header_(std::move(header)), table_(std::move(table)) {}

void Result::JoinResult(const std::shared_ptr<Result>& result) {
  if (this->header_.empty()) {
    this->header_ = result->header_;
    this->table_ = result->table_;
    return;
  }
  if (result->header_.empty()) {
    return;
  }
  InterceptResult intercept = FindIntercept(this->header_, result->header_);
  ResultTable temp;

  for (auto &i : intercept.second) {
    this->header_[i.first] = (int) this->header_.size();
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

std::unordered_set<std::string> Result::ProjectResult(const SelectedSynonymTuple& synonym_tuple) {
  std::unordered_set<std::string> output;

  std::vector<int> index_lst;
  for (auto &kSyn : synonym_tuple) {
    int index = this->header_.at(kSyn);
    index_lst.push_back(index);
  }

  for (auto &row : this->table_) {
    std::stringstream result;
    for (int i = 0; i < index_lst.size(); ++i) {
      result << ( i ? " " : "" ) << row[index_lst[i]];
    }
    output.insert(result.str());
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
  for (auto const &kEntry : r_2) {
    if (r_1.count(kEntry.first) == 1) {
      intercept.emplace_back(r_1[kEntry.first], kEntry.second);
    } else {
      non_intercept.emplace_back(kEntry);
    }
  }
  std::sort(non_intercept.begin(), non_intercept.end(),
            [] (auto &a, auto &b) {return a.second < b.second;});
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
        new_row.push_back(r[i.second]);
      }
      out.push_back(new_row);

      if (intercept.second.empty()) {
        return out;
      }
    }
  }
  return out;
}
