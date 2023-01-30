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

const std::string kDeclarationKey = "Declarations";
const std::string kSelectKey = "Select";
const std::string kSynonymKey = "Synonym";
const std::string kSuchThatKey = "Such That";
const std::string kPatternKey = "Pattern";

const std::string kEntityKey = "Entity";
const std::string kFirstParameterKey = "First Parameter";
const std::string kSecondParameterKey = "Second Parameter";

//such that should have a relationship ref next e.g. "Modifies" etc. which start with a letter
const std::regex kSuchThatRegex("such that [A-Z]");
// next token should be a syn-assign, which starts with a letter rather than , or ) e.g. (pattern, pattern)
const  std::regex kPatternRegex("pattern [A-Za-z]");

}