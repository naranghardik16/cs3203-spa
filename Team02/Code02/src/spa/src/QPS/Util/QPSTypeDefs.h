#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "HashPair.h"
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

typedef std::string SingleConstraint;
//! E.g. {1,2,3,4} for Select a (assign) is a SingleConstraintSet
typedef std::unordered_set<SingleConstraint> SingleConstraintSet;

typedef std::pair<std::string, std::string> PairConstraint;
//! E.g. Uses(s,v) gives a PairConstraintSet {(1,v1), (2,v2)}
typedef std::unordered_set<PairConstraint, hash_pair> PairConstraintSet;

typedef std::vector<std::string> ResultHeader;
typedef std::vector<std::string> ResultRow;
typedef std::vector<std::vector<std::string>> ResultTable;
typedef std::vector<std::pair<int, int>> Intercept;
typedef std::vector<int> NonIntercept;
typedef std::pair<Intercept, NonIntercept> InterceptResult;
