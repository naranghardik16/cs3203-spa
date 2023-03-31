#include "ClauseSyntax.h"

ClauseSyntax::ClauseSyntax(const SyntaxPair& pair) {
  pair_ = pair;
  expr_ = nullptr;
}

int ClauseSyntax::GetSynonymCount() {
  return syn_.size();
}

int ClauseSyntax::GetArgumentScore(Map &declaration_map) {
  int score  = 0;
  auto score_map = pql_constants::kSynTypeScoreMap;
  for (const auto& syn:syn_) {
    score += score_map[declaration_map[syn]];
  }
  return score;
}

std::string ClauseSyntax::GetEntity() const {
  return pair_.first;
}

std::string ClauseSyntax::GetFirstParameter() {
  return pair_.second[0];
}

std::string ClauseSyntax::GetSecondParameter() {
  return pair_.second[1];
}

std::string ClauseSyntax::GetThirdParameter() {
  return pair_.second[2];
}

SyntaxPair ClauseSyntax::GetSyntaxPair() {
  return pair_;
}

ParameterVector ClauseSyntax::GetParameters() const {
  return pair_.second;
}

std::shared_ptr<Expression> ClauseSyntax::GetExpression() {
  return expr_;
}

void ClauseSyntax::SetExpression(std::shared_ptr<Expression> expr) {
  expr_ = std::move(expr);
}

bool ClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  return this->GetEntity() == other.GetEntity() && this->GetFirstParameter() == other.GetFirstParameter() &&
    this->GetSecondParameter() == other.GetSecondParameter();
}
