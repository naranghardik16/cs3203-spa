#include "General/LexicalRuleValidator.h"
#include "catch.hpp"
#include "QPS/Util/QueryUtil.h"

auto lexical_rule_validator = std::shared_ptr<LexicalRuleValidator>();

TEST_CASE("Check if isLetter follows rules correctly") {
  SECTION("Test all lowercase characters") {
    std::string alphabets = "abcdefghijklmnopqrstuvwxyz";
    for (char c : alphabets) {
      REQUIRE(lexical_rule_validator->IsLetter(c));
    }
  }

  SECTION("Test all uppercase characters") {
    std::string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char c : alphabets) {
      REQUIRE(lexical_rule_validator->IsLetter(c));
    }
  }

  SECTION("Test negative cases with digit") {
    std::string digits = "0123456789";
    for (char c : digits) {
      REQUIRE_FALSE(lexical_rule_validator->IsLetter(c));
    }
  }


  SECTION("Test negative cases with punctuation") {
    std::string punctuation = "!@#$%^&*(){}:<>?/";
    for (char c : punctuation) {
      REQUIRE_FALSE(lexical_rule_validator->IsLetter(c));
    }
  }
}

TEST_CASE("Check if isDigit follows rules correctly") {
  SECTION("Test cases with digit") {
    std::string digits = "0123456789";
    for (char c : digits) {
      REQUIRE(lexical_rule_validator->IsDigit(c));
    }
  }

  SECTION("Test negative case with all alphabets") {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char c : alphabet) {
      REQUIRE_FALSE(lexical_rule_validator->IsDigit(c));
    }
  }

  SECTION("Test negative cases with punctuation") {
    std::string punctuation = "!@#$%^&*(){}:<>?/";
    for (char c : punctuation) {
      REQUIRE_FALSE(lexical_rule_validator->IsDigit(c));
    }
  }
}

TEST_CASE("Check if isNZDigit follows rules correctly") {
  SECTION("Test cases with 1-9 digit") {
    std::string digits = "123456789";
    for (char c : digits) {
      REQUIRE(lexical_rule_validator->IsNzDigit(c));
    }
  }

  SECTION("Test negative case with 0 digit") {
    std::string digits = "0";
    for (char c : digits) {
      REQUIRE_FALSE(lexical_rule_validator->IsNzDigit(c));
    }
  }

  SECTION("Test negative case with all alphabets") {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char c : alphabet) {
      REQUIRE_FALSE(lexical_rule_validator->IsNzDigit(c));
    }
  }

  SECTION("Test negative cases with punctuation") {
    std::string punctuation = "!@#$%^&*(){}:<>?/";
    for (char c : punctuation) {
      REQUIRE_FALSE(lexical_rule_validator->IsNzDigit(c));
    }
  }
}

TEST_CASE("Check if isIdent, isName, isSynonym follows rules correctly") {
  SECTION("Test valid single letter variable") {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (char c : alphabet) {
      std::string s;
      s.push_back(c);
      REQUIRE(lexical_rule_validator->IsIdent(s));
      REQUIRE(lexical_rule_validator->IsName(s));
    }
  }

  SECTION("Test valid cases") {
    std::string s = "a0123afbDS";
    REQUIRE(lexical_rule_validator->IsIdent(s));
    REQUIRE(lexical_rule_validator->IsName(s));
  }

  SECTION("Test invalid cases") {
    std::vector<std::string> invalid_vector {"0", "0a", "00", "!", "!a", "!0", "a0123!"};
    for (const auto& kS : invalid_vector) {
      REQUIRE_FALSE(lexical_rule_validator->IsIdent(kS));
      REQUIRE_FALSE(lexical_rule_validator->IsName(kS));
    }
  }
}

TEST_CASE("Check if isInteger follows rules correctly") {
  SECTION("Test valid cases") {
    std::vector<std::string> valid_vector {"0", "1343242", "223", "9432"};
    for (const auto& kS : valid_vector) {
      REQUIRE(lexical_rule_validator->IsInteger(kS));
    }
  }

  SECTION("Test invalid cases") {
    REQUIRE_FALSE(lexical_rule_validator->IsInteger("01234"));
  }
}
