#pragma once
#include "WithClauseSyntax.h"
#include "QPS/Evaluator/WithClauseEvaluator/WithClauseEvaluator.h"
#include "QPS/Util/PQLConstants.h"

WithClauseSyntax::WithClauseSyntax(SyntaxPair pair) : ClauseSyntax(pair) {}

bool WithClauseSyntax::Equals(ClauseSyntax &other) {
  // make sure that the passed type is the same
  WithClauseSyntax *pc = dynamic_cast<WithClauseSyntax*>(&other);
  if (pc) {
    return (this->GetEntity() == pc->GetEntity()) && (this->GetFirstParameter() == pc->GetFirstParameter()) &&
        (this->GetSecondParameter() == pc->GetSecondParameter());
  }
  return false;
}


bool WithClauseSyntax::IsAttrCondContainMismatchedAttrRef(std::string attrRef_1, std::string attrRef_2) {
  auto attr_name_1 = QueryUtil::GetAttrNameFromAttrRef(attrRef_1);
  auto attr_name_2 = QueryUtil::GetAttrNameFromAttrRef(attrRef_2);

  bool is_attr_name_1_return_int = ((attr_name_1 == pql_constants::kStmtNo) || (attr_name_1 == pql_constants::kValue));
  bool is_attr_name_2_return_int = ((attr_name_2 == pql_constants::kStmtNo) || (attr_name_2 == pql_constants::kValue));
  bool both_return_int = is_attr_name_1_return_int && is_attr_name_2_return_int;

  bool is_attr_name_1_return_ident = ((attr_name_1 == pql_constants::kProcName) || (attr_name_1 == pql_constants::kVarname));
  bool is_attr_name_2_return_ident = ((attr_name_2 == pql_constants::kProcName) || (attr_name_2 == pql_constants::kVarname));
  bool both_return_ident = is_attr_name_1_return_ident && is_attr_name_2_return_ident;

  if (both_return_ident) {
    return false;
  } else if (both_return_int) {
    return false;
  } else {
    return true;
  }
}

bool WithClauseSyntax::IsAttrCondContainFalseAttrRefComparison(std::string attrRef, std::string comparison_value) {
  auto attr_name = QueryUtil::GetAttrNameFromAttrRef(attrRef);

  bool is_attr_name_return_int = ((attr_name == pql_constants::kStmtNo) || (attr_name == pql_constants::kValue));
  //either IDENT or INT
  //e.g. a.stmt# = ""v""
  bool is_comparison_value_int = LexicalRuleValidator::IsInteger(comparison_value);
  if (is_attr_name_return_int) {
    return !is_comparison_value_int;
  } else {
    //attr_name return ident -- e.g. procName or varName which must follow the NAME lexical rule and cannot be an integer
    //e.g. p.procName = "5"
    return is_comparison_value_int;
  }
}


bool WithClauseSyntax::IsBooleanClause(Map &declaration_map) {
  auto first_arg = this->GetFirstParameter();
  auto second_arg = this->GetSecondParameter();

  //If not, the only case left is int or ident
  bool is_first_arg_an_attr_ref = QueryUtil::IsAttrRef(first_arg);
  bool is_second_arg_an_attr_ref = QueryUtil::IsAttrRef(second_arg);

  if (is_first_arg_an_attr_ref && is_second_arg_an_attr_ref) {
    //e.g. p.procName = c.value
    if (IsAttrCondContainMismatchedAttrRef(first_arg, second_arg)) {
      return true;
    } else {
      return false;
    }
  } else if (is_first_arg_an_attr_ref) {
    //e.g. p.procName = 5, a.stmt# = "v"
    return IsAttrCondContainFalseAttrRefComparison(first_arg, second_arg);
  } else if (is_second_arg_an_attr_ref) {
    //e.g. p.procName = 5, a.stmt# = "v"
    return IsAttrCondContainFalseAttrRefComparison(second_arg, first_arg);
  } else {
    // 5 = 6, v = 5 -- no synonym present
    return true;
  }
}

std::shared_ptr<ClauseEvaluator> WithClauseSyntax::CreateClauseEvaluator(Map &declaration_map) {
  std::shared_ptr<ClauseEvaluator> eval = std::make_shared<WithClauseEvaluator>(declaration_map, ClauseSyntax::GetSyntaxPair());
  return eval;
}