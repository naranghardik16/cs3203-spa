#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include <algorithm>


namespace string_util {

std::string Ltrim(const std::string &s);

std::string Rtrim(const std::string &s);

std::string Trim(const std::string &s);

std::pair<std::vector<std::string>, std::string> SplitStringByDelimiter(std::string s, const std::string& delimiter);

std::string GetFirstWord(const std::string& s);

std::string GetSubStringAfterKeyword(const std::string& clause, const std::string& keyword);

std::string RemoveExtraWhitespacesInString(const std::string &input);
}