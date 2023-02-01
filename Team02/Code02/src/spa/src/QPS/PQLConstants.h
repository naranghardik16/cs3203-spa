#pragma once
#include <iostream>
#include <regex>

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

}