#include "ClauseEvaluator.h"
Synonym ClauseEvaluator::GetSynonym() {
  return synonym_;
}

Map ClauseEvaluator::GetDeclarationMap() {
  return declaration_map_;
}

SyntaxPair ClauseEvaluator::GetSyntaxPair() {
  return syntax_pair_;
}

std::shared_ptr<PkbReadFacade> ClauseEvaluator::GetPKB() {
  return pkb_;
}