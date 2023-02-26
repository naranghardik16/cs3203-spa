#include "DesignEntityGetter.h"

GetterFunc DesignEntityGetter::get_procedure_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetProcedures();};

GetterFunc DesignEntityGetter::get_statement_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetStatements();};

GetterFunc DesignEntityGetter::get_read_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetReadStatements();};

GetterFunc DesignEntityGetter::get_print_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetPrintStatements();};

GetterFunc DesignEntityGetter::get_call_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetCallStatements();};

GetterFunc DesignEntityGetter::get_while_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetWhileStatements();};

GetterFunc DesignEntityGetter::get_if_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetIfStatements();};

GetterFunc DesignEntityGetter::get_assign_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetAssignStatements();};

GetterFunc DesignEntityGetter::get_variable_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetVariables();};

GetterFunc DesignEntityGetter::get_constant_entity_func_ =
    [] (const std::shared_ptr<PkbReadFacade>& pkb) {return pkb->GetConstants();};

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
    {pql_constants::kPqlConstantEntity, get_constant_entity_func_}
};

PkbCommunicationTypes::SingleConstraintSet DesignEntityGetter::GetEntitySet(const std::shared_ptr<PkbReadFacade> &pkb,
                                                                            const std::string& entity) {
  return getter_map_[entity](pkb);
}
