#include "DesignEntityGetter.h"

GetterFunc DesignEntityGetter::get_procedure_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetProcedures());
};

GetterFunc DesignEntityGetter::get_statement_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetStatements());
};

GetterFunc DesignEntityGetter::get_read_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetReadStatements());
};

GetterFunc DesignEntityGetter::get_print_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetPrintStatements());
};

GetterFunc DesignEntityGetter::get_call_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetCallStatements());
};

GetterFunc DesignEntityGetter::get_while_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetWhileStatements());
};

GetterFunc DesignEntityGetter::get_if_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetIfStatements());
};

GetterFunc DesignEntityGetter::get_assign_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetAssignStatements());
};

GetterFunc DesignEntityGetter::get_variable_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetVariables());
};

GetterFunc DesignEntityGetter::get_constant_entity_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertSetToResultTableFormat(pkb->GetConstants());
};

GetterFunc DesignEntityGetter::get_read_variable_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertPairSetToResultTableFormat(
      pkb->GetModifiesStatementVariablePairs(StatementType::READ));
};

GetterFunc DesignEntityGetter::get_print_variable_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertPairSetToResultTableFormat(
      pkb->GetUsesStatementVariablePairs(StatementType::PRINT));
};

GetterFunc DesignEntityGetter::get_call_procedure_func_ = [] (const std::shared_ptr<PkbReadFacade>& pkb) {
  return ClauseEvaluator::ConvertPairSetToResultTableFormat(pkb->GetCallProcedurePair());
};

std::unordered_map<std::string, GetterFunc> DesignEntityGetter::getter_map_ = {
    {pql_constants::kPqlProcedureEntity, get_procedure_entity_func_},
    {pql_constants::kPqlStatementEntity, get_statement_entity_func_},
    {pql_constants::kPqlReadEntity, get_read_entity_func_},
    {pql_constants::kPqlPrintEntity, get_print_entity_func_},
    {pql_constants::kPqlCallEntity, get_call_entity_func_},
    {pql_constants::kPqlWhileEntity, get_while_entity_func_},
    {pql_constants::kPqlIfEntity, get_if_entity_func_},
    {pql_constants::kPqlAssignEntity, get_assign_entity_func_},
    {pql_constants::kPqlVariableEntity, get_variable_entity_func_},
    {pql_constants::kPqlConstantEntity, get_constant_entity_func_},
    {pql_constants::kPqlProcedureEntity + pql_constants::kProcName, get_procedure_entity_func_},
    {pql_constants::kPqlVariableEntity + pql_constants::kVarname, get_variable_entity_func_},
    {pql_constants::kPqlConstantEntity + pql_constants::kValue, get_constant_entity_func_},
    {pql_constants::kPqlStatementEntity + pql_constants::kStmtNo, get_statement_entity_func_},
    {pql_constants::kPqlReadEntity + pql_constants::kStmtNo, get_read_entity_func_},
    {pql_constants::kPqlReadEntity + pql_constants::kVarname, get_read_variable_func_},
    {pql_constants::kPqlPrintEntity + pql_constants::kStmtNo, get_print_entity_func_},
    {pql_constants::kPqlPrintEntity + pql_constants::kVarname, get_print_variable_func_},
    {pql_constants::kPqlWhileEntity + pql_constants::kStmtNo, get_while_entity_func_},
    {pql_constants::kPqlIfEntity + pql_constants::kStmtNo, get_if_entity_func_},
    {pql_constants::kPqlCallEntity + pql_constants::kStmtNo, get_call_entity_func_},
    {pql_constants::kPqlCallEntity + pql_constants::kProcName, get_call_procedure_func_},
    {pql_constants::kPqlAssignEntity + pql_constants::kStmtNo, get_assign_entity_func_}
};

ResultTable DesignEntityGetter::GetEntitySet(const std::shared_ptr<PkbReadFacade> &pkb, const std::string& entity) {
  return getter_map_[entity](pkb);
}

std::shared_ptr<Result> DesignEntityGetter::EvaluateBasicSelect(const Synonym& synonym, const std::shared_ptr<PkbReadFacade> &pkb, Map &declaration_map) {
  std::vector<std::string> token_lst = QueryUtil::SplitAttrRef(synonym);
  std::string attr_name = token_lst.size() == 1 ? "" : token_lst[1];

  ResultHeader header;
  header[token_lst[0]] = header.size();
  if (token_lst.size() == 2) {
    header[synonym] = header.size();
  }

  ResultTable table = DesignEntityGetter::GetEntitySet(pkb, declaration_map[token_lst[0]] + attr_name);

  std::shared_ptr<Result> result_ptr = std::make_shared<Result>(header, table);
  return result_ptr;
}

std::shared_ptr<Result> DesignEntityGetter::GetIntersectionOfTwoAttr(
    const Synonym &syn_1, const Synonym &syn_2, const std::shared_ptr<PkbReadFacade> &pkb, Map &declaration_map) {
  auto result_1 = EvaluateBasicSelect(syn_1, pkb, declaration_map);
  auto result_2 = EvaluateBasicSelect(syn_2, pkb, declaration_map);

  int index = result_2->header_.size() == 1 ? 0 : 1;
  result_2->header_.push_back(syn_1);

  for (auto &row : result_2->table_) {
    row.push_back(row[index]);
  }
  result_1->JoinResult(result_2);
  return result_1;
}
