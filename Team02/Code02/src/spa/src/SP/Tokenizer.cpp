#include "Tokenizer.h"

Tokenizer::Tokenizer() {}

template<typename Base, typename T>
bool InstanceOf(const T *ptr) {
  return dynamic_cast<const Base*>(ptr) != nullptr;
}

vector<string> Tokenizer::SplitLines(istream &stream) {
  vector<string> lines;
  string line;
  while (getline(stream, line)) {
    string_util::RemoveExtraWhitespacesInString(line);
    lines.push_back(line);
  }
  return lines;
}

Token* Tokenizer::MatchOtherToken(int first_char_index, string line, int* skip_index) {
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

void FormNameOrInteger(int *start_index, int *end_index, int current_index) {
  if (*start_index != -1) {
    *end_index = current_index;
  } else {
    *start_index = current_index;
    *end_index = current_index;
  }
}

Token* Tokenizer::MatchNameOrIntegerToken(LexicalRuleValidator *lrv, string val, int type) {
  if (type == NAME_TYPE && lrv->IsName(val)) {
    return new NameToken(val);
  }

  if (type == INTEGER_TYPE && lrv->IsInteger(val)) {
    return new IntegerToken(val);
  }

  return NULL;
}

// TODO: Handle for multiple statements in a line by either { or } or ; as delimiter
Parser::TokenStream* Tokenizer::Tokenize(istream &stream) {
  Parser::TokenStream *token_stream = new Parser::TokenStream();
  vector<Token*> line_of_tokens = {};
  LexicalRuleValidator *lrv = new LexicalRuleValidator();

  vector<string> lines = SplitLines(stream);
  int i;
  int skip_index = -1;
  int type = -1;
  int start_index = -1;
  int end_index = -1;
  for (i = 0; i < lines.size(); i++) {
//    cout << "Line no: " << i+1 << " contains: "  << lines[i] << "\n";

    for(string::size_type j = 0; j < lines[i].size(); j++) {
      if ((j == skip_index) || (isspace(lines[i][j]) && type == -1)) {
        skip_index = -1;
        continue;
      }

      if (lrv->IsLetter(lines[i][j])) {
        type = NAME_TYPE;
        FormNameOrInteger(&start_index, &end_index, j);
        continue;
      } else if (lrv->IsDigit(lines[i][j])) {
        type = INTEGER_TYPE;
        FormNameOrInteger(&start_index, &end_index, j);
        continue;
      }

      // only space and punctuation will be used as delimiter for name/integer
      Token* current_token = MatchOtherToken(j, lines[i], &skip_index);
      Token* prev_token = NULL;

      // check if it is time to form the name/integer token
      if (type != -1 && (isspace(lines[i][j]) || (current_token != NULL &&  InstanceOf<PunctuationToken>(current_token)))) {
        prev_token = MatchNameOrIntegerToken(lrv, lines[i].substr(start_index, j - start_index), type);
      }

      // check if a name/integer token was formed
      if (type != -1 && prev_token != NULL) {
//        cout << "NameOrIntegerToken: " << prev_token->GetValue() << "\n";
        line_of_tokens.push_back(prev_token);
        type = -1;
        start_index = -1;
        end_index = -1;
      }

      if (current_token == NULL) {
        continue;

      }

      line_of_tokens.push_back(current_token);

      // check if this is the end of the line
      PunctuationToken *pot = dynamic_cast<PunctuationToken*>(current_token);
      if (!pot) {
        continue;
      }
      auto it = END_OF_LINE_TOKENS.find(pot->GetType());
      // key is not present
      if (it == END_OF_LINE_TOKENS.end()) {
        continue;
      }

      token_stream->push_back(line_of_tokens);
      line_of_tokens.clear();
    }
  }

  return token_stream;
}