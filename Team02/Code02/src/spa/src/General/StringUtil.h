#pragma once
#include <iostream>
#include <vector>
#include <regex>

namespace string_util {

std::string Ltrim(const std::string &s);

std::string Rtrim(const std::string &s);

std::string Trim(const std::string &s);

std::vector<std::string> SplitStringByDelimiter(std::string s, const std::string& delimiter);

std::string GetFirstWord(const std::string& s);

bool IsWhiteSpace(char c);

std::string GetClauseAfterKeyword(const std::string& clause, const std::string& keyword);

}