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

  static bool IsQuoted(const std::string& s);

  static bool IsRelationshipReference(const std::string& s);

  static bool IsCharacterString(const std::string& s);

  static bool IsPartialMatchExpressionSpecification(const std::string& s);

  static bool IsVariableSynonym(Map &declaration, const std::string& expression);

  static bool IsConstantSynonym(Map &declaration, const std::string& expression);

  static bool IsAssignSynonym(Map &declaration, const std::string& expression);

  static bool IsIfSynonym(Map &declaration, const std::string& expression);

  static bool IsStatementSynonym(Map &declaration, const std::string& expression);

  static bool IsWhileSynonym(Map &declaration, const std::string& expression);

  static bool IsPrintSynonym(Map &declaration, const std::string& expression);

  static bool IsReadSynonym(Map &declaration, const std::string& expression);

  static bool IsCallSynonym(Map &declaration, const std::string& expression);

  static bool IsProcedureSynonym(Map &declaration, const std::string& expression);

  static bool IsContainerStatementSynonym(Map &declaration, const std::string& expression);

  static bool IsATypeOfStatementSynonym(Map &declaration, const std::string& expression);

  static std::unordered_set<std::string> ConvertToSet(std::vector<std::vector<std::string>> v);
  static std::vector<std::vector<std::string>> ExtractFirstElementInTheVectors(std::vector<std::vector<std::string>> v);
  static std::vector<std::vector<std::string>> ExtractSecondElementInTheVectors(std::vector<std::vector<std::string>> v);
};

