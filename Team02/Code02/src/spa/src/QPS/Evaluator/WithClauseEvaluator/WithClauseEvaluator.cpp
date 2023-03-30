#include "WithClauseEvaluator.h"

Synonym  WithClauseEvaluator::ProcessArgumentForEvaluation(std::string arg, Map &declaration_map) {
  bool is_syn_a_type_of_attr_ref = QueryUtil::IsAttrRef(arg);
  if (is_syn_a_type_of_attr_ref) {
    // want r instead of r.stmt# for e.g. since stmt# is trivial
    return QueryUtil::AdjustSynonymWithTrivialAttrRefValue(arg, declaration_map);
  } else if (QueryUtil::IsQuoted(arg)) {
    // IDENT case -- will directly create a result with this value so we want to store "x" in the table and not ""x""
    return QueryUtil::GetIdent(arg);
  } else {
    // int or synonym case
    return arg;
  }
}

bool WithClauseEvaluator::EvaluateBooleanConstraint() {
  // only int = int or ident = ident
  return first_arg_ == second_arg_;
}

std::shared_ptr<Result> WithClauseEvaluator::HandleOneAttrRefCase(Synonym attr_ref_syn, ResultTable filter_table) {
  // Handles case of e.g. s.stmt# = 5
  ResultHeader header;
  auto evaluation_result = DesignEntityGetter::EvaluateBasicSelect(attr_ref_syn, pkb_, declaration_map_);
  header[attr_ref_syn] = static_cast<int>(header.size());
  std::shared_ptr<Result> filter_result = std::make_shared<Result>(header, filter_table);
  evaluation_result->JoinResult(filter_result);
  return evaluation_result;
}

std::shared_ptr<Result> WithClauseEvaluator::EvaluateClause() {
  // Check before processing because trivial attr-refs will be adjusted e.g. r.stmt#-->r
  bool is_first_arg_a_type_of_attr_ref = QueryUtil::IsAttrRef(first_arg_);
  bool is_second_arg_a_type_of_attr_ref = QueryUtil::IsAttrRef(second_arg_);

  first_arg_ = ProcessArgumentForEvaluation(first_arg_, declaration_map_);
  second_arg_ = ProcessArgumentForEvaluation(second_arg_, declaration_map_);

  ResultHeader header;
  ResultTable table;

  // to be non boolean, there must be at least one attr-ref
  if (is_first_arg_a_type_of_attr_ref && is_second_arg_a_type_of_attr_ref) {
    auto result =
        DesignEntityGetter::GetIntersectionOfTwoAttr(first_arg_, second_arg_, pkb_, declaration_map_);
    return result;
  } else if (is_first_arg_a_type_of_attr_ref) {
    return HandleOneAttrRefCase(first_arg_, {{second_arg_}});
  } else {
    return HandleOneAttrRefCase(second_arg_, {{first_arg_}});
  }
}
