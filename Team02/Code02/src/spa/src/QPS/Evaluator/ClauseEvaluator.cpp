#include "ClauseEvaluator.h"

Map ClauseEvaluator::GetDeclarationMap() {
  return declaration_map_;
}

ResultTable ClauseEvaluator::ConvertSetToResultTableFormat(PkbCommunicationTypes::SingleConstraintSet s) {
  std::vector<std::vector<std::string>> result;
  for (const auto& kElem: s) {
    std::vector<std::string> nested_vector;
    nested_vector.push_back(kElem);
    result.push_back(nested_vector);
  }
  return result;
}

ResultTable ClauseEvaluator::ConvertPairSetToResultTableFormat(PkbCommunicationTypes::PairConstraintSet s) {
  std::vector<std::vector<std::string>> result;
  for (const auto& kElem: s) {
    std::vector<std::string> nested_vector;
    nested_vector.push_back(kElem.first);
    nested_vector.push_back(kElem.second);
    result.push_back(nested_vector);
  }
  return result;
}
