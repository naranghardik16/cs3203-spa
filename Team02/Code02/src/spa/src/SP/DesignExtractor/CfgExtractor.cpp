#include "CfgExtractor.h"

CfgExtractor::CfgExtractor(shared_ptr<Cfg> cfg) : cfg_(cfg) {}

void CfgExtractor::VisitProcedure(shared_ptr<Procedure> procedure) {
  string proc_name = procedure->GetProcedureName();
  cur_proc_name_ = proc_name;
  cur_cfg_node_ = make_shared<CfgNode>();
  cfg_->AddProcCfg(proc_name, cur_cfg_node_);
}

void CfgExtractor::VisitAssignStatement(shared_ptr<AssignStatement> assign_statement) {
  // assign stmts can only add statements inside the cfg node
  auto stmt_number = assign_statement->GetStatementNumber();
  AddCfgForStmt(stmt_number);
}

void CfgExtractor::VisitReadStatement(shared_ptr<ReadStatement> read_statement) {
  auto stmt_number = read_statement->GetStatementNumber();
  AddCfgForStmt(stmt_number);
}

void CfgExtractor::VisitPrintStatement(shared_ptr<PrintStatement> print_statement) {
  auto stmt_number = print_statement->GetStatementNumber();
  AddCfgForStmt(stmt_number);
}

void CfgExtractor::VisitCallStatement(shared_ptr<CallStatement> call_statement) {
  auto stmt_number = call_statement->GetStatementNumber();
  AddCfgForStmt(stmt_number);
}

void CfgExtractor::VisitIfStatement(shared_ptr<IfStatement> if_statement) {
  // If Statement results in creating new nodes with node transitions
  // based on true or false values of the condition
  int stmt_number = if_statement->GetStatementNumber();
  auto if_cfg_node = make_shared<CfgNode>();
  auto then_cfg_node = make_shared<CfgNode>();
  auto else_cfg_node = make_shared<CfgNode>();
  auto end_cfg_node = make_shared<CfgNode>();

  if (cur_cfg_node_->GetNodeStmts().size() > 0) {
    AddTransitionAndUpdate(if_cfg_node, true);
  } else {
    if_cfg_node = cur_cfg_node_;
  }

  AddCfgForStmt(stmt_number);

  auto then_stmts = if_statement->GetThenStatements();
  auto else_stmts = if_statement->GetElseStatements();

  // Create the CFG nodes for then statements
  AddTransitionAndUpdate(then_cfg_node, true);
  ProcessStatements(then_stmts);

  // Create dummy node for end of if else
  AddTransitionAndUpdate(end_cfg_node, true);

  // Create the CFG nodes for else statements
  cur_cfg_node_ = if_cfg_node;
  AddTransitionAndUpdate(else_cfg_node, false);
  ProcessStatements(else_stmts);

  // Add transition to the dummy node at the end
  AddTransitionAndUpdate(end_cfg_node, true);
}

void CfgExtractor::VisitWhileStatement(shared_ptr<WhileStatement> while_statement) {
  int stmt_number = while_statement->GetStatementNumber();
  auto while_cfg_node = make_shared<CfgNode>();
  auto loop_cfg_node = make_shared<CfgNode>();
  auto end_cfg_node = make_shared<CfgNode>();

  if (cur_cfg_node_->GetNodeStmts().size() > 0) {
    AddTransitionAndUpdate(while_cfg_node, true);
  } else {
    while_cfg_node = cur_cfg_node_;
  }

  AddCfgForStmt(stmt_number);
  auto loop_stmts = while_statement->GetLoopStatements();

  // add CfgNodes for statements
  AddTransitionAndUpdate(loop_cfg_node, true);
  ProcessStatements(loop_stmts);
  // loop back to the while node;
  AddTransitionAndUpdate(while_cfg_node, true);
  // create an end node for while
  AddTransitionAndUpdate(end_cfg_node, false);
}

void CfgExtractor::VisitRelationalOperation(shared_ptr<RelationalOperation> rel_operation) {}

void CfgExtractor::VisitArithmeticalOperation(shared_ptr<ArithmeticOperation> arith_operation) {}

void CfgExtractor::VisitConditionalOperation(shared_ptr<ConditionalOperation> cond_operation) {}

void CfgExtractor::VisitVariable(shared_ptr<Variable> variable) {}

void CfgExtractor::VisitConstant(shared_ptr<Constant> constant) {}

void CfgExtractor::ProcessStatements(const Procedure::StmtListContainer &statements) {
  for (auto const &stmt : statements) {
    auto this_cfg_extractor = make_shared<CfgExtractor>(*this);
    stmt->Accept(this_cfg_extractor);
    cur_cfg_node_ = this_cfg_extractor->cur_cfg_node_;
    cfg_ = this_cfg_extractor->cfg_;
    cur_proc_name_ = this_cfg_extractor->cur_proc_name_;
  }
}

void CfgExtractor::AddCfgForStmt(int stmt_number) {
  cur_cfg_node_->AddStmt(stmt_number);
  cfg_->AddStmtCfg(stmt_number, cur_cfg_node_);
}

void CfgExtractor::AddTransitionAndUpdate(shared_ptr<CfgNode> new_node,
                                          bool value) {
  cur_cfg_node_->AddTransition(value, new_node);
  new_node->AddParent(cur_cfg_node_);
  cur_cfg_node_ = new_node;
}

