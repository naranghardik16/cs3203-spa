#pragma once
#include <iostream>
#include <regex>

/**
 * Organises all constants that are used in QPS
 */
namespace pql_constants {

const std::string kTupleOpeningBracket = "<";
const std::string kTupleClosingBracket = ">";
const std::string kOpeningBracket = "(";
const std::string kClosingBracket = ")";
const std::string kComma = ",";
const std::string kEqual = "=";
const std::string kSemicolon = ";";
const std::string kFullStop = ".";

const std::string kSelectBoolean = "BOOLEAN";
const std::string kSelectKeyword = "Select";

//such that should have a relationship ref next e.g. "Modifies" etc. which start with a letter
const std::regex kSuchThatRegex("such that [A-Za-z]");
// next token should be a syn-assign, which starts with a letter rather than , or ) e.g. (pattern, pattern)
const std::regex kPatternRegex("pattern [A-Za-z]");
const std::regex kWithRegex("with [A-Za-z0-9\"]");
const std::regex kAndRegex("and [A-Za-z0-9\"]");

const std::string kPqlStatementEntity = "stmt";
const std::string kPqlReadEntity = "read";
const std::string kPqlPrintEntity = "print";
const std::string kPqlWhileEntity = "while";
const std::string kPqlIfEntity = "if";
const std::string kPqlCallEntity = "call";
const std::string kPqlAssignEntity = "assign";
const std::string kPqlVariableEntity = "variable";
const std::string kPqlConstantEntity = "constant";
const std::string kPqlProcedureEntity = "procedure";

const std::string kPqlFollowsRel = "Follows";
const std::string kPqlFollowsStarRel = "Follows*";
const std::string kPqlParentRel = "Parent";
const std::string kPqlParentStarRel = "Parent*";
const std::string kPqlUsesRel = "Uses";
const std::string kPqlModifiesRel = "Modifies";

const std::unordered_set<std::string> kRelRefs({kPqlFollowsRel, kPqlFollowsStarRel, kPqlParentRel, kPqlParentStarRel, kPqlUsesRel, kPqlModifiesRel});
const std::unordered_set<std::string> kStmtRefEntities({kPqlStatementEntity, kPqlReadEntity, kPqlPrintEntity, kPqlAssignEntity, kPqlIfEntity, kPqlWhileEntity, kPqlCallEntity});
const std::unordered_set<std::string> kStmtToStmtRel({kPqlFollowsRel, kPqlFollowsStarRel, kPqlParentRel, kPqlParentStarRel});
const std::unordered_set<std::string> kStmtProcToStmtRel({kPqlUsesRel, kPqlModifiesRel});
const std::unordered_set<std::string> kStmtProcRefEntities({kPqlStatementEntity, kPqlReadEntity, kPqlPrintEntity, kPqlAssignEntity, kPqlIfEntity, kPqlWhileEntity, kPqlCallEntity, kPqlProcedureEntity});
}