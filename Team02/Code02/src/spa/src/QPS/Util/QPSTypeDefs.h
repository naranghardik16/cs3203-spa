#pragma once
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>

/**
 * Organises all type definitions that are used in QPS
 */
typedef std::vector<std::string> Declarations;
typedef std::string SelectStatement;
typedef std::vector<std::string> SelectedSynonymTuple;
typedef std::pair<Declarations, SelectStatement> QueryLinesPair;

typedef std::string Synonym;
typedef std::string DesignEntity;
typedef std::unordered_map<Synonym, DesignEntity> Map;

typedef std::string Parameter;
typedef std::vector<Parameter> ParameterVector;
//refers to ref-ref/syn assign
typedef std::pair<DesignEntity, ParameterVector> SyntaxPair;
class ClauseSyntax;
typedef std::vector<std::shared_ptr<ClauseSyntax>> ClauseSyntaxPtrList;


typedef std::vector<std::string> ResultHeader;
typedef std::vector<std::string> ResultRow;
typedef std::vector<std::vector<std::string>> ResultTable;
typedef std::vector<std::pair<int, int>> Intercept;
typedef std::vector<int> NonIntercept;
typedef std::pair<Intercept, NonIntercept> InterceptResult;
