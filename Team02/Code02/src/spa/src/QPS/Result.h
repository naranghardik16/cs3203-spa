#pragma once

#include <algorithm>
#include "QPS/Util/QPSTypeDefs.h"

/*
 * Class to store the result of clause evaluation.
 * Header contains the synonyms with table containing the result rows.
 * The index of synonym in header correspond to the col index in the table.
 */
class Result {
 private:
  ResultHeader header_;
  ResultTable table_;
 public:
  Result(ResultHeader header, ResultTable table);

  /*
   * Join two result on intercepting header. Result will be store in the calling object.
   */
  void JoinResult(Result &result);

  //Helper function
  static InterceptResult FindIntercept(ResultHeader &r_1, ResultHeader &r_2);
  static ResultTable FindMatch(ResultRow &row, ResultTable &table, InterceptResult &intercept);
};
