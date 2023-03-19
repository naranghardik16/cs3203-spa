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

  for (auto &i : intercept.second) {
    this->header_[i.first] = static_cast<int>(this->header_.size());
  }

  if (result->table_.empty() || this->table_.empty()) {
    this->table_.clear();
    return;
  }

  // this->table_ = NestedLoopJoin(this->table_, result->table_, intercept);
  this->table_ = HashJoin(this->table_, result->table_, intercept);
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
      result << (i ? " " : "") << row[index_lst[i]];
    }
    output.insert(result.str());
  }
  return output;
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

ResultTable Result::HashJoin(ResultTable &main, ResultTable &other, InterceptResult &intercept) {
  std::unordered_map<std::vector<std::string>, std::vector<std::vector<std::string>>, vector_string_hash> map;
  // build
  for (auto &row : other) {
    std::vector<std::string> key;
    std::vector<std::string> value;
    for (auto &p : intercept.first) {
      key.push_back(row[p.second]);
    }
    for (auto &p : intercept.second) {
      value.push_back(row[p.second]);
    }
    map[key].push_back(value);
  }

  // probe
  ResultTable r;
  for (auto &row : main) {
    std::vector<std::string> key;
    for (auto &p : intercept.first) {
      key.push_back(row[p.first]);
    }

    if (map.find(key) != map.end()) {
      auto &values = map[key];
      for (auto &value : values) {
        ResultRow new_row(row);
        new_row.insert(new_row.end(), value.begin(), value.end());
        r.push_back(new_row);
        if (intercept.second.empty()) {
          break;
        }
      }
    }
  }
  return r;
}

ResultTable Result::NestedLoopJoin(ResultTable &main, ResultTable &other, InterceptResult &intercept) {
  ResultTable out;
  for (auto &main_row : main) {
    for (auto &other_row : other) {
      bool match = true;

      for (auto &p : intercept.first) {
        if (main_row[p.first] != other_row[p.second]) {
          match = false;
          break;
        }
      }

      if (match) {
        ResultRow new_row(main_row);
        for (auto &i : intercept.second) {
          new_row.push_back(other_row[i.second]);
        }
        out.push_back(new_row);

        if (intercept.second.empty()) {
          break;
        }
      }
    }
  }
  return out;
}

ResultHeader &Result::GetHeader() {
  return header_;
}

ResultTable &Result::GetTable() {
  return table_;
}
