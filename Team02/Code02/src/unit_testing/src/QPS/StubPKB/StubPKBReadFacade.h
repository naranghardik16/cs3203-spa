//! Preserving the stub written previously

#pragma once
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

//!Should inherit from PKBReadFacade
class StubPkbReadFacade {
 public:
  StubPkbReadFacade(PKB& pkb) {};

  ~StubPkbReadFacade();

  //! API for basic Select statements
  SingleConstraintSet GetVariables();
  SingleConstraintSet GetConstants();
  SingleConstraintSet GetProcedures();
  SingleConstraintSet GetStatements();
  SingleConstraintSet GetReadStatements();
  SingleConstraintSet GetPrintStatements();
  SingleConstraintSet GetCallStatements();
  SingleConstraintSet GetWhileStatements();
  SingleConstraintSet GetIfStatements();
  SingleConstraintSet GetAssignStatements();

  //! API for Modifies - Statement
  SingleConstraintSet GetVariablesModifiedByStatement(std::string statement_number);
  PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type);
  SingleConstraintSet GetStatementsModifiesVariable(std::string var_name, StatementType statement_type);
  SingleConstraintSet GetStatementsThatModify(StatementType stmt_type);
  bool HasModifiesStatementRelationship(std::string stmt_num, std::string var_name);

  //! API for Modifies - Procedure
  SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name);
  PairConstraintSet GetModifiesProcedureVariablePairs();
  SingleConstraintSet GetProceduresModifiesVariable(std::string var_name);
  SingleConstraintSet GetProceduresThatModify();
  bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name);

  //!API for Follows
  PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower);
  SingleConstraintSet GetStatementsFollowedBy(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsFollowing(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type);
  SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type);
  bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower);
  bool IsAnyFollowsRelationshipPresent();

  //!API for Parent

  PairConstraintSet GetParentChildPairs(StatementType statement_type, StatementType statement_type_child);
  SingleConstraintSet GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsThatAreParents(StatementType statement_type);
  SingleConstraintSet GetStatementsThatAreChildren(StatementType statement_type);
  bool HasParentChildRelationship(std::string statement_num, std::string statement_num_child);
  bool IsAnyParentRelationshipPresent();

  //!API for ParentStar
  PairConstraintSet GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant);
  SingleConstraintSet GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsThatAreDescendantsOf(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsThatAreAncestors(StatementType statement_type);
  SingleConstraintSet GetStatementsThatAreDescendants(StatementType statement_type);
  bool HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant);
  bool IsAnyAncestorDescendantRelationshipPresent();
};
