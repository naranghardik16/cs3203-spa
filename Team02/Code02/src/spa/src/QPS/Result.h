#pragma once

#include <algorithm>
#include <sstream>
#include <utility>
#include <map>
#include "QPS/Util/QPSTypeDefs.h"

/*!
 * Class to store the result of clause evaluation.
 * Header contains the synonyms with table containing the result rows.
 * The index of synonym in header correspond to the col index in the table.
 */
class Result {
 public:
  ResultHeader header_;
  ResultTable table_;
  Result(ResultHeader header, ResultTable table);

  /*!
   * Join two result on intercepting header. Result will be store in the calling object.
   * Both of the table should not be empty, else nothing will happen.
   */
  void JoinResult(const std::shared_ptr<Result>& result);
  std::unordered_set<std::string> ProjectResult(const SelectedSynonymTuple& synonym);
  std::unordered_set<std::string> ProjectResultForBoolean();

 private:
  //!Helper function
  static InterceptResult FindIntercept(ResultHeader &r_1, ResultHeader &r_2);
  static ResultTable HashJoin(ResultTable &main, ResultTable &other, InterceptResult &intercept);
  static ResultTable NestedLoopJoin(ResultTable &main, ResultTable &other, InterceptResult &intercept);
};
