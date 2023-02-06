#include "Result.h"

Result::Result(ResultHeader header, ResultTable table) : header_(header), table_(table) {}

void Result::JoinResult(Result &result) {
  InterceptResult intercept = FindIntercept(this->header_, result.header_);
  ResultTable temp;
  for (auto &row : this->table_) {
    ResultTable join = FindMatch(row, result.table_, intercept);
    temp.insert(temp.end(), join.begin(), join.end());
  }
  this->table_ = temp;
}

InterceptResult Result::FindIntercept(ResultHeader &r_1, ResultHeader &r_2) {
  Intercept intercept;
  NonIntercept non_intercept;
  for (int i = 0; i < r_2.size(); ++i) {
    auto it = std::find(r_1.begin(), r_1.end(), r_2[i]);
    if (it != r_1.end()) {
      intercept.push_back({it - r_1.begin(), i});
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
}
