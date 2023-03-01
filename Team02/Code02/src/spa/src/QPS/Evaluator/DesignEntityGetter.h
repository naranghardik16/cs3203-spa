#pragma once

#include <unordered_map>
#include <functional>
#include "QPS/Result.h"
#include "QPS/Util/QPSTypeDefs.h"
#include "QPS/Util/PQLConstants.h"
#include "QPS/Evaluator/ClauseEvaluator.h"
#include "PKB/Interfaces/PkbReadFacade.h"

typedef std::function<ResultTable(std::shared_ptr<PkbReadFacade>)> GetterFunc;

class DesignEntityGetter {
 private:
  static GetterFunc get_procedure_entity_func_;
  static GetterFunc get_statement_entity_func_;
  static GetterFunc get_read_entity_func_;
  static GetterFunc get_print_entity_func_;
  static GetterFunc get_call_entity_func_;
  static GetterFunc get_while_entity_func_;
  static GetterFunc get_if_entity_func_;
  static GetterFunc get_assign_entity_func_;
  static GetterFunc get_variable_entity_func_;
  static GetterFunc get_constant_entity_func_;
  static GetterFunc get_read_variable_func_;
  static GetterFunc get_print_variable_func_;
  static GetterFunc get_call_procedure_func_;

  static std::unordered_map<std::string, GetterFunc> getter_map_;

 public:
  static ResultTable GetEntitySet(const std::shared_ptr<PkbReadFacade> &pkb, const std::string &entity);
};
