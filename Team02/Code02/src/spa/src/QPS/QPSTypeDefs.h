#pragma once
#include <iostream>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include "QPS/Clause/ClauseSyntax.h"
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

typedef std::vector<std::shared_ptr<ClauseSyntax>> ClauseSyntaxPtrList;
typedef std::pair<Synonym, std::pair<ClauseSyntaxPtrList, Map>> ParserOutput;

typedef std::string SingleConstraint;
//! E.g. {1,2,3,4} for Select a (assign) is a SingleConstraintSet
typedef  std::unordered_set<SingleConstraint> SingleConstraintSet;

typedef std::pair<std::string, std::string> PairConstraint;
//! E.g. Uses(s,v) gives a PairConstraintSet {(1,v1), (2,v2)}
typedef std::unordered_set<PairConstraint> PairConstraintSet;
