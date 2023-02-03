#pragma once
#include <iostream>
#include <regex>
#include <unordered_set>

namespace pql_constants {

const char kOpeningBracket = '(';
const char kClosingBracket = ')';
const char kComma = ',';

const std::string kSuchThatStartIndicator = "such that ";
const std::string kPatternStartIndicator = "pattern ";
const std::string kSelectKeyword = "Select";

//such that should have a relationship ref next e.g. "Modifies" etc. which start with a letter
const std::regex kSuchThatRegex("such that [A-Za-z]");
// next token should be a syn-assign, which starts with a letter rather than , or ) e.g. (pattern, pattern)
const  std::regex kPatternRegex("pattern [A-Za-z]");

const std::string kStmtEntity = "stmt";
const std::string kReadEntity = "read";
const std::string kPrintEntity = "print";
const std::string kAssignEntity = "assign";
const std::string kIfEntity = "if";
const std::string kWhileEntity = "while";
const std::string kCallEntity = "call";
const std::string kProcedureEntity = "procedure";
const std::string kVariableEntity = "variable";

const std::string kFollowRel = "Follows";
const std::string kFollowTRel = "Follows*";
const std::string kParentRel = "Parent";
const std::string kParentTRel = "Parent*";
const std::string kUseRel = "Uses";
const std::string kModifiesRel = "Modifies";

const std::unordered_set<std::string> kRelRefs({kFollowRel, kFollowTRel, kParentRel, kParentTRel, kUseRel, kModifiesRel});
const std::unordered_set<std::string> kStmtRefEntities({kStmtEntity, kReadEntity, kPrintEntity, kAssignEntity, kIfEntity, kWhileEntity, kCallEntity});
const std::unordered_set<std::string> kStmtToStmtRel({kFollowRel, kFollowTRel, kParentRel, kParentTRel});
const std::unordered_set<std::string> kStmtProcToStmtRel({kUseRel, kModifiesRel});
const std::unordered_set<std::string> kStmtProcRefEntities({kStmtEntity, kReadEntity, kPrintEntity, kAssignEntity, kIfEntity, kWhileEntity, kCallEntity, kProcedureEntity});
}