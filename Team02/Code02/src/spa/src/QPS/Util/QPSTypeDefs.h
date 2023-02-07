#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
// Forward declarations of classes if any

typedef std::vector<std::string> Declarations;
typedef std::string SelectStatement;
typedef std::pair<Declarations, SelectStatement> QueryStatementPair;

typedef std::string Synonym;
typedef std::string DesignEntity;
typedef std::unordered_map<Synonym, DesignEntity> Map;

typedef std::string FirstParameter;
typedef std::string SecondParameter;
typedef std::pair<FirstParameter, SecondParameter> ParameterPair;
//refers to ref-ref/syn assign
typedef std::pair<DesignEntity, ParameterPair> SyntaxPair;
class ClauseSyntax;
typedef std::vector<std::shared_ptr<ClauseSyntax>> ClauseSyntaxPtrList;


typedef std::vector<std::string> ResultHeader;
typedef std::vector<std::string> ResultRow;
typedef std::vector<std::vector<std::string>> ResultTable;
typedef std::vector<std::pair<int, int>> Intercept;
typedef std::vector<int> NonIntercept;
typedef std::pair<Intercept, NonIntercept> InterceptResult;
