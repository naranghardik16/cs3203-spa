#pragma once
#include "WithClauseEvaluator.h"
#include "General/LexicalRuleValidator.h"
#include "QPS/Util/QueryUtil.h"
#include "PKB/Types/PkbCommunicationTypes.h"


Synonym  WithClauseEvaluator::ProcessArgumentForEvaluation(Synonym syn, Map &declaration_map) {
  bool is_syn_a_type_of_attr_ref = QueryUtil::IsAttrRef(syn);
  if (is_syn_a_type_of_attr_ref) {
    //want r instead of r.stmt# for e.g. since stmt# is trivial
    return QueryUtil::AdjustSynonymWithTrivialAttrRefValue(syn, declaration_map);
  } else if (QueryUtil::IsQuoted(syn)) {
    //Will directly create a result with this value so we want to store "x" in the table and not ""x""
    return string_util::Trim(syn.substr(1, syn.length()-2));
  } else {
    //int can just return as it is
    return syn;
  }
}

bool WithClauseEvaluator::EvaluateBooleanConstraint(std::shared_ptr<PkbReadFacade> pkb) {
  // only int = int or ident = ident
  return first_arg_ == second_arg_;
}

std::vector<std::string> WithClauseEvaluator::Intersection(std::vector<std::string> v1,
                                      std::vector<std::string> v2){
  std::vector<std::string> v3;

  std::sort(v1.begin(), v1.end());
  std::sort(v2.begin(), v2.end());

  std::set_intersection(v1.begin(),v1.end(),
                        v2.begin(),v2.end(),
                        back_inserter(v3));
  return v3;
}

std::shared_ptr<Result> WithClauseEvaluator::EvaluateClause(std::shared_ptr<PkbReadFacade> pkb) {
  auto declaration_map = ClauseEvaluator::GetDeclarationMap();
  //Check before processing because trivial attr-refs will be adjusted e.g. r.stmt#-->r
  bool is_first_arg_a_type_of_attr_ref = QueryUtil::IsAttrRef(first_arg_);
  bool is_second_arg_a_type_of_attr_ref = QueryUtil::IsAttrRef(second_arg_);

  first_arg_ = ProcessArgumentForEvaluation(first_arg_, declaration_map);
  second_arg_ = ProcessArgumentForEvaluation(second_arg_, declaration_map);

  ResultHeader header;
  ResultTable table;

  // to be non boolean, there must be at least one attr-ref
  if (is_first_arg_a_type_of_attr_ref && is_second_arg_a_type_of_attr_ref) {
    auto result = DesignEntityGetter::GetIntersectionOfTwoAttr(first_arg_, second_arg_, pkb, declaration_map);

    return result;
  } else if (is_first_arg_a_type_of_attr_ref) {
    //Need to evaluate to know if the second arg is present and can constraint e.g. p.procName = "NonExistent"
    auto first_arg_evaluation_result = DesignEntityGetter::EvaluateBasicSelect(first_arg_, pkb, declaration_map);
    header.push_back(first_arg_);
    table = {{second_arg_}};
    std::shared_ptr<Result> filter_result = std::make_shared<Result>(header, table);
    first_arg_evaluation_result->JoinResult(filter_result);
    return first_arg_evaluation_result;
  } else {
    auto second_arg_evaluation_result = DesignEntityGetter::EvaluateBasicSelect(second_arg_, pkb, declaration_map);
    header.push_back(second_arg_);
    table = {{first_arg_}};
    std::shared_ptr<Result> filter_result = std::make_shared<Result>(header, table);
    second_arg_evaluation_result->JoinResult(filter_result);
    return second_arg_evaluation_result;
  }
}

