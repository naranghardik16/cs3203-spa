//! Preserving the stub written previously

#pragma once
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Types/PkbCommunicationTypes.h"

//!Should inherit from PKBReadFacade
class StubPkbReadFacade: public PkbReadFacade {
 public:
  StubPkbReadFacade(PKB& pkb);

  ~StubPkbReadFacade();

  //! API for basic Select statements
  PkbCommunicationTypes::SingleConstraintSet GetVariables() override;
  PkbCommunicationTypes::SingleConstraintSet GetConstants() override;
  PkbCommunicationTypes::SingleConstraintSet GetProcedures() override;
  PkbCommunicationTypes::SingleConstraintSet GetStatements() override;
  PkbCommunicationTypes::SingleConstraintSet GetReadStatements() override;
  PkbCommunicationTypes::SingleConstraintSet GetPrintStatements() override;
  PkbCommunicationTypes::SingleConstraintSet GetCallStatements() override;
  PkbCommunicationTypes::SingleConstraintSet GetWhileStatements() override;
  PkbCommunicationTypes::SingleConstraintSet GetIfStatements() override;
  PkbCommunicationTypes::SingleConstraintSet GetAssignStatements() override;

  //! API for Modifies - Statement
  PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByStatement(std::string statement_number) override;
  PkbCommunicationTypes::PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsModifiesVariable(std::string var_name, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatModify(StatementType stmt_type) override;
  bool HasModifiesStatementRelationship(std::string stmt_num, std::string var_name) override;

  //! API for Modifies - Procedure
  PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name) override;
  PkbCommunicationTypes::PairConstraintSet GetModifiesProcedureVariablePairs() override;
  PkbCommunicationTypes::SingleConstraintSet GetProceduresModifiesVariable(std::string var_name) override;
  PkbCommunicationTypes::SingleConstraintSet GetProceduresThatModify() override;
  bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name) override;

  //!API for Follows
  PkbCommunicationTypes::PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementFollowedBy(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementFollowing(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type) override;
  bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) override;
  bool IsAnyFollowsRelationshipPresent() override;

  //!API for Parent
  PkbCommunicationTypes::PairConstraintSet GetParentChildPairs(StatementType statement_type, StatementType statement_type_child) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreParents(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildren(StatementType statement_type) override;
  bool HasParentChildRelationship(std::string statement_num, std::string statement_num_child) override;
  bool IsAnyParentRelationshipPresent();

  //!API for ParentStar
  PkbCommunicationTypes::PairConstraintSet GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendantsOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestors(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendants(StatementType statement_type) override;
  bool HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant) override;
  bool IsAnyAncestorDescendantRelationshipPresent() override;
};
