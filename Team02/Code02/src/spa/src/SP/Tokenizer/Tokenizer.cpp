#include "Tokenizer.h"

Tokenizer::Tokenizer() {}

vector<string> Tokenizer::SplitLines(istream &stream) {
  vector<string> lines;
  string line;
  while (getline(stream, line)) {
    string_util::RemoveExtraWhitespacesInString(line);
    lines.push_back(line);
  }
  return lines;
}

shared_ptr<Token> Tokenizer::MatchOtherToken(int first_char_index, string line, shared_ptr<int> skip_index) {
  string first_char = line.substr(first_char_index, 1);
  string first_and_second_char = line.substr(first_char_index, 2);

  if (regex_match(first_char, regex(ARITHMETIC_OPERATOR_RULE))) {
    return make_shared<ArithmeticOperatorToken>(first_char, TOKEN_TYPES.find(first_char)->second);
  }

  if (regex_match(first_and_second_char, regex(CONDITIONAL_OPERATOR_RULE))) {
    *skip_index = first_char_index + 1;
    return make_shared<ConditionalOperatorToken>(first_and_second_char, TOKEN_TYPES.find(first_and_second_char)->second);
  }

  if (regex_match(first_and_second_char, regex(RELATIONAL_OPERATOR_RULE))) {
    *skip_index = first_char_index + 1;
    return make_shared<RelationalOperatorToken>(first_and_second_char, TOKEN_TYPES.find(first_and_second_char)->second);
  }

  if (regex_match(first_char, regex(CONDITIONAL_OPERATOR_RULE))) {
    return make_shared<ConditionalOperatorToken>(first_char, TOKEN_TYPES.find(first_char)->second);
  }

  if (regex_match(first_char, regex(RELATIONAL_OPERATOR_RULE))) {
    return make_shared<RelationalOperatorToken>(first_char, TOKEN_TYPES.find(first_char)->second);
  }

  if (regex_match(first_char, regex(PUNCTUATION_OPERATOR_RULE))) {
    return make_shared<PunctuationToken>(first_char, TOKEN_TYPES.find(first_char)->second);
  }
  return nullptr;
}

void Tokenizer::CombineNameOrInteger(shared_ptr<int> start_index, int current_index) {
  if (*start_index == NOT_SET) {
    *start_index = current_index;
  }
}

shared_ptr<Token> Tokenizer::MatchNameOrIntegerToken(shared_ptr<LexicalRuleValidator> lrv, string val, int type) {
  if (type == NAME_TYPE && lrv->IsName(val)) {
    return make_shared<NameToken>(val);
  }

  if (type == INTEGER_TYPE && lrv->IsInteger(val)) {
    return make_shared<IntegerToken>(val);
  }

  return nullptr;
}

shared_ptr<Parser::TokenStream> Tokenizer::Tokenize(istream &stream) {
  shared_ptr<Parser::TokenStream> token_stream = make_shared<Parser::TokenStream>();
  vector<shared_ptr<Token>> line_of_tokens = {};
  shared_ptr<LexicalRuleValidator> lrv = make_shared<LexicalRuleValidator>();

  vector<string> lines = SplitLines(stream);
  int i;
  shared_ptr<int> skip_index = make_shared<int>(NOT_SET);
  int type = NOT_SET;
  shared_ptr<int> start_index = make_shared<int>(NOT_SET);
  for (i = 0; i < lines.size(); i++) {
    for(string::size_type j = 0; j < lines[i].size(); j++) {
      char current_char = lines[i][j];
      bool is_continue = false;
      if ((j == *skip_index) || (isspace(current_char) && type == NOT_SET)) {
        skip_index = make_shared<int>(NOT_SET);
        continue;
      }

      if (lrv->IsLetter(current_char)) {
        type = NAME_TYPE;
        CombineNameOrInteger(start_index, j);
        is_continue = true;
      } else if (type == NAME_TYPE && lrv->IsDigit(current_char)) {
        CombineNameOrInteger(start_index, j);
        is_continue = true;
      } else if (lrv->IsDigit(current_char)) {
        type = INTEGER_TYPE;
        CombineNameOrInteger(start_index, j);
        is_continue = true;
      }

      if (is_continue && j < lines[i].size() - 1) {
        continue;
      }

      shared_ptr<Token> current_token = MatchOtherToken(j, lines[i], skip_index);
      shared_ptr<Token> prev_token = nullptr;

      // check if it is time to form the name/integer token
      // non-alphanumeric character (e.g. space, punctuation, operations) will be used as delimiter for name/integer
      // else if it is the end of the line it will also be extracted for name/integer
      if (type != NOT_SET &&
          (isspace(current_char)
          || (current_token != nullptr && !(current_token->GetType() == NAME || current_token->GetType() == INTEGER))
          || j == lines[i].size() - 1)) {
        prev_token = MatchNameOrIntegerToken(lrv, lines[i].substr(*start_index, j - *start_index), type);
      }

      // check if a name/integer token was formed
      if (type != NOT_SET && prev_token != nullptr) {
        line_of_tokens.push_back(prev_token);
        type = NOT_SET;
        start_index = make_shared<int>(NOT_SET);
      } else if (type != NOT_SET && prev_token == nullptr) {
        throw SyntaxErrorException(lines[i].substr(*start_index, j - *start_index) + " is an invalid token");
      }

      if (current_token == nullptr && prev_token != nullptr) {
        continue;
      } else if (current_token == nullptr) {
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