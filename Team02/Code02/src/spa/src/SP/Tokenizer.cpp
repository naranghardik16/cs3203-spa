#include "Tokenizer.h"
#include "General/LexicalRuleValidator.h"

Tokenizer::Tokenizer() {}

vector<string> Tokenizer::SplitLines(istream &stream) {
  vector<string> lines;
  string line;
  while (getline(stream, line)) {
    lines.push_back(line);
  }
  return lines;
}

Token* Tokenizer::MatchToken(int first_char_index, string line, int* skip_index) {
  string first_char = line.substr(first_char_index, 1);
  string first_and_second_char = line.substr(first_char_index, 2);

  if (regex_match(first_char, regex(ARITHMETIC_OPERATOR_RULE))) {
//    cout << first_char << " matched\n";
    return new ArithmeticOperatorToken(first_char, ARITHMETIC_OPERATOR_TYPES.find(first_char)->second);
  }

  if (regex_match(first_and_second_char, regex(CONDITIONAL_OPERATOR_RULE))) {
//    cout << first_and_second_char << " matched\n";
    *skip_index = first_char_index + 1;
    return new ConditionalOperatorToken(first_and_second_char, CONDITONAL_OPERATOR_TYPES.find(first_and_second_char)->second);
  }

  if (regex_match(first_char, regex(CONDITIONAL_OPERATOR_RULE))) {
//    cout << first_char << " matched\n";
    return new ConditionalOperatorToken(first_char, CONDITONAL_OPERATOR_TYPES.find(first_char)->second);
  }

  if (regex_match(first_and_second_char, regex(RELATIONAL_OPERATOR_RULE))) {
//    cout << first_and_second_char << " matched\n";
    *skip_index = first_char_index + 1;
    return new RelationalOperatorToken(first_and_second_char, RELATIONAL_OPERATOR_TYPES.find(first_and_second_char)->second);
  }

  if (regex_match(first_char, regex(RELATIONAL_OPERATOR_RULE))) {
//    cout << first_char << " matched\n";
    return new RelationalOperatorToken(first_char, RELATIONAL_OPERATOR_TYPES.find(first_char)->second);
  }

  if (regex_match(first_char, regex(PUNCTUATION_OPERATOR_RULE))) {
//    cout << first_char << " matched\n";
    return new PunctuationToken(first_char, PUNCTUATION_TYPES.find(first_char)->second);
  }
  return NULL;
}

void Form_Name_Or_Integer(int *start_index, int *end_index, int current_index) {
  if (*start_index != -1) {
    *end_index = current_index;
  } else {
    *start_index = current_index;
  }
}

//void Form_Integer(int *start_index, int *end_index, int current_index) {
//
//}

vector<vector<Token>>* Tokenizer::Tokenize(istream &stream) {
  vector<string> lines = SplitLines(stream);
  LexicalRuleValidator *lrv = new LexicalRuleValidator();
  int i;
  int skip_index = -1;
  bool is_forming_name = false;
  bool is_forming_integer = false;
  int start_index = -1;
  int end_index = -1;
  for (i = 0; i < lines.size(); i++) {
    cout << "Line no: " << i+1 << " contains: "  << lines[i] << "\n";
    for(string::size_type j = 0; j < lines[i].size(); j++) {
      if (j == skip_index) {
//        cout << "skip_index: " << skip_index << "\n";
        continue;
      }
      if (lrv->IsLetter(lines[i][j])) {
        is_forming_name = true;
        Form_Name_Or_Integer(&start_index, &end_index, j);
      } else if (lrv->IsDigit(lines[i][j])) {

      } else {

      }

      Token* t = MatchToken(j, lines[i], &skip_index);

    }
  }

  return NULL;
}