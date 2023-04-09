#include "ClauseEvaluator.h"

ResultTable ClauseEvaluator::ConvertSetToResultTableFormat(const PkbCommunicationTypes::SingleConstraintSet& s) {
  std::vector<std::vector<std::string>> result;
  for (const auto& kElem: s) {
    std::vector<std::string> nested_vector;
    nested_vector.push_back(kElem);
    result.push_back(nested_vector);
  }
  return result;
}

ResultTable ClauseEvaluator::ConvertPairSetToResultTableFormat(const PkbCommunicationTypes::PairConstraintSet& s) {
  std::vector<std::vector<std::string>> result;
  for (const auto& kElem: s) {
    std::vector<std::string> nested_vector;
    nested_vector.push_back(kElem.first);
    nested_vector.push_back(kElem.second);
    result.push_back(nested_vector);
  }
  return result;
}

PkbCommunicationTypes::PairConstraintSet ClauseEvaluator::FilterForSameSynonym(
    const PkbCommunicationTypes::PairConstraintSet& s
    ) {
  PkbCommunicationTypes::PairConstraintSet filtered_set;
  for (const auto& kElem: s) {
    if (kElem.first == kElem.second) {
      filtered_set.insert(kElem);
    }
  }
  return filtered_set;
}
