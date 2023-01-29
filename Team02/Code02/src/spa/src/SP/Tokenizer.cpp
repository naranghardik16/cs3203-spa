#include "Tokenizer.h"

Tokenizer::Tokenizer() {}

vector<string> splitLines(istream & stream) {
  vector<string> lines;
  string line;
  while (getline(stream, line)) {
    lines.push_back(line);
  }
  return lines;
}

vector<vector<Token>>* Tokenizer::tokenize(istream & stream) {
  vector<string> lines = splitLines(stream);
  int i;
  for (i = 0; i < lines.size(); i++) {
//    cout << "Line no: " << i+1 << " contains: "  << lines[i] << "\n";
  }

  return NULL;
}