#include "StringUtil.h"

/*
 * Trims trailing space off left of string
 * Reference: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
 */
std::string string_util::Ltrim(const std::string &s) {
  return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

/*
 * Trims trailing space off right of string
 * Reference: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
 */
std::string string_util::Rtrim(const std::string &s) {
  return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

/*
 * Trims trailing space off left and right of string
 * Reference: https://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string
 */
std::string string_util::Trim(const std::string &s) {
  return Ltrim(Rtrim(s));
}

/*
 * Splits a string by a specified delimiter. The delimiter will be excluded.
 */
std::vector<std::string> string_util::SplitStringByDelimiter(std::string s, const std::string &delimiter) {
  // Reference: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
  std::vector<std::string> tokens;
  std::string token;

  size_t delimiter_index = s.find(delimiter);
  while (delimiter_index != std::string::npos) {
    token = string_util::Trim(s.substr(0, delimiter_index));
    tokens.push_back(token);
    s.erase(0, delimiter_index + delimiter.length());
    delimiter_index = s.find(delimiter);
  }

  if (s.length() > 0) {
    tokens.push_back(string_util::Trim(s));
  }

  return tokens;
}

/*
 * Returns the first word in a string by finding the first whitespace in the string.
 * If there is no whitespace, then the input string is returned.
 */
std::string string_util::GetFirstWord(const std::string &s) {
  size_t white_space_index = s.length();
  for (int i = 0; i < s.length(); i++) {
    if (std::isspace(s[i])) {
      white_space_index = i;
      break;
    }
  }
  std::string first_word = Trim(s.substr(0, white_space_index));
  return first_word;
}

/*
 * Gets the trimmed substring after the first keyword found in a clause.
 */
std::string string_util::GetSubStringAfterKeyword(const std::string &clause, const std::string &keyword) {
  size_t new_start_index = clause.find(keyword) + keyword.length();
  return Trim(clause.substr(new_start_index, clause.length() - 1));
}

/*
 * Trims extra whitespace left and right of string as well as inside the string.
 * Reference: https://stackoverflow.com/questions/35301432/remove-extra-white-spaces-in-c
 */
std::string string_util::RemoveExtraWhitespacesInString(const std::string &input) {
  std::string output;
  std::unique_copy(input.begin(), input.end(), std::back_insert_iterator<std::string>(output),
                   [](char a, char b) { return std::isspace(a) && std::isspace(b); });
  return Trim(output);
}
