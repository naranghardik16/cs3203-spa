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
    return new ArithmeticOperatorToken(first_char, TOKEN_TYPES.find(first_char)->second);
  }

  if (regex_match(first_and_second_char, regex(CONDITIONAL_OPERATOR_RULE))) {
    *skip_index = first_char_index + 1;
    return new ConditionalOperatorToken(first_and_second_char, TOKEN_TYPES.find(first_and_second_char)->second);
  }

  if (regex_match(first_and_second_char, regex(RELATIONAL_OPERATOR_RULE))) {
    *skip_index = first_char_index + 1;
    return new RelationalOperatorToken(first_and_second_char, TOKEN_TYPES.find(first_and_second_char)->second);
  }

  if (regex_match(first_char, regex(CONDITIONAL_OPERATOR_RULE))) {
    return new ConditionalOperatorToken(first_char, TOKEN_TYPES.find(first_char)->second);
  }

  if (regex_match(first_char, regex(RELATIONAL_OPERATOR_RULE))) {
    return new RelationalOperatorToken(first_char, TOKEN_TYPES.find(first_char)->second);
  }

  if (regex_match(first_char, regex(PUNCTUATION_OPERATOR_RULE))) {
    return new PunctuationToken(first_char, TOKEN_TYPES.find(first_char)->second);
  }
  return NULL;
}

void Tokenizer::FormNameOrInteger(int *start_index, int current_index) {
  if (*start_index == NOT_SET) {
    *start_index = current_index;
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

Parser::TokenStream* Tokenizer::Tokenize(istream &stream) {
  Parser::TokenStream *token_stream = new Parser::TokenStream();
  vector<Token*> line_of_tokens = {};
  LexicalRuleValidator *lrv = new LexicalRuleValidator();

  vector<string> lines = SplitLines(stream);
  int i;
  int skip_index = NOT_SET;
  int type = NOT_SET;
  int start_index = NOT_SET;
  for (i = 0; i < lines.size(); i++) {
    for(string::size_type j = 0; j < lines[i].size(); j++) {
      char current_char = lines[i][j];
      if ((j == skip_index) || (isspace(current_char) && type == NOT_SET)) {
        skip_index = NOT_SET;
        continue;
      }

      if (lrv->IsLetter(current_char)) {
        type = NAME_TYPE;
        FormNameOrInteger(&start_index, j);
        continue;
      } else if (lrv->IsDigit(current_char)) {
        type = INTEGER_TYPE;
        FormNameOrInteger(&start_index, j);
        continue;
      }

      // non-alphanumeric character (e.g. space, punctuation, operations) will be used as delimiter for name/integer
      Token* current_token = MatchOtherToken(j, lines[i], &skip_index);
      Token* prev_token = NULL;

      // check if it is time to form the name/integer token
      if (type != NOT_SET && (isspace(current_char) || (current_token != NULL && !(current_token->GetType() == NAME || current_token->GetType() == INTEGER)))) {
        prev_token = MatchNameOrIntegerToken(lrv, lines[i].substr(start_index, j - start_index), type);
      }

      // check if a name/integer token was formed
      if (type != NOT_SET && prev_token != NULL) {
        line_of_tokens.push_back(prev_token);
        type = NOT_SET;
        start_index = NOT_SET;
      } else if (type != NOT_SET && prev_token == NULL) {
        throw SyntaxErrorException(lines[i].substr(start_index, j - start_index) + " is an invalid token");
      }

      if (current_token == NULL && prev_token != NULL) {
        continue;
      } else if (current_token == NULL) {
        throw SyntaxErrorException(current_char + " is an invalid token");
      }

      line_of_tokens.push_back(current_token);

      // check if this is the end of the line
      auto it = END_OF_LINE_TOKENS.find(current_token->GetType());
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