#pragma once
#include <string>
#include "QPSTypeDefs.h"
#include <unordered_set>
#include <unordered_map>

class QueryUtil {

 public:
  static bool IsWildcard(const std::string& s);

  static bool IsSynonym(const std::string& s);

  static bool IsStmtRef(const std::string& s);

  static bool IsEntRef(const std::string& s);

  static bool IsDesignEntity(const std::string& s);

  static bool IsRelationshipReference(const std::string& s);

  static bool IsCharacterString(const std::string& s);

  static bool IsPartialMatchExpressionSpecification(const std::string& s);

  static bool IsVariableSynonym(Map &declaration, const std::string& expression);

  static SingleConstraintSet QueryUtil::GetIntersection(const SingleConstraintSet& set_1, const SingleConstraintSet& set_2);

  //TODO To complete this
  // static void QueryUtil::GetIntersectionOfPairSets(const PairConstraintSet& set_1, const PairConstraintSet&  set_2);

};

