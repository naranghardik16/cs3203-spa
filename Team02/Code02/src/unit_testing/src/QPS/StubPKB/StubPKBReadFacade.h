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

  //! API for Uses - Statement
  PkbCommunicationTypes::PairConstraintSet GetUsesStatementVariablePairs(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatUses(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetVariablesUsedByStatement(std::string statement_number) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsUsesVariable(StatementType statement_type, std::string variable) override;
  bool HasUsesStatementRelationship(std::string statement_number, std::string variable) override;

  //! API for Uses - Procedure
  PkbCommunicationTypes::PairConstraintSet GetUsesProcedureVariablePairs() override;
  PkbCommunicationTypes::SingleConstraintSet GetProceduresThatUse() override;
  PkbCommunicationTypes::SingleConstraintSet GetVariablesUsedByProcedure(std::string procedure) override;
  PkbCommunicationTypes::SingleConstraintSet GetProceduresUsesVariable(std::string variable) override;
  bool HasUsesProcedureRelationship(std::string procedure, std::string variable) override;

  //!API for Follows
  PkbCommunicationTypes::PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementFollowedBy(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementFollowing(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type) override;
  bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower) override;
  bool IsAnyFollowsRelationshipPresent() override;

  //!API for FollowsStar
  PkbCommunicationTypes::PairConstraintSet GetFollowsStarPairs(StatementType statement_type_1, StatementType statement_type_2) override;
  PkbCommunicationTypes::SingleConstraintSet GetFollowsStar(std::string statement_number, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetFollowsStarBy(std::string statement_number, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetFollowsStarFirst(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetFollowsStarSecond(StatementType statement_type) override;
  bool HasFollowsStarRelationship() override;
  bool HasFollowsStar(std::string statement_number) override;
  bool HasFollowsStarBy(std::string statement_number) override;
  bool IsFollowsStar(std::string statement_number_1, std::string statement_number_2) override;

  //!API for Parent
  PkbCommunicationTypes::PairConstraintSet GetParentChildPairs(StatementType statement_type, StatementType statement_type_child) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreParents(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildren(StatementType statement_type) override;
  bool HasParentChildRelationship(std::string statement_num, std::string statement_num_child) override;
  bool IsAnyParentRelationshipPresent() override;

  //!API for ParentStar
  PkbCommunicationTypes::PairConstraintSet GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendantsOf(std::string statement_num, StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestors(StatementType statement_type) override;
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendants(StatementType statement_type) override;
  bool HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant) override;
  bool IsAnyAncestorDescendantRelationshipPresent() override;

  //!API for pattern
  PkbCommunicationTypes::SingleConstraintSet GetAssignWithExactExpression(const std::shared_ptr<Expression> &expr) override;
  PkbCommunicationTypes::SingleConstraintSet GetAssignWithPartialExpression(const std::shared_ptr<Expression> &sub_expr) override;
  PkbCommunicationTypes::PairConstraintSet GetIfConditionVariablePair() override;
  PkbCommunicationTypes::SingleConstraintSet GetIfWithConditionVariable(const std::string &var_name) override;
  PkbCommunicationTypes::SingleConstraintSet GetIfThatHasConditionVariable() override;
  PkbCommunicationTypes::PairConstraintSet GetWhileConditionVariablePair() override;
  PkbCommunicationTypes::SingleConstraintSet GetWhileWithConditionVariable(const std::string &var_name) override;
  PkbCommunicationTypes::SingleConstraintSet GetWhileThatHasConditionVariable() override;

  //!API for Next
  PkbCommunicationTypes::PairConstraintSet GetNextPairs(StatementType type_1, StatementType type_2);
  PkbCommunicationTypes::SingleConstraintSet GetNext(std::string statement_number, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetNextBy(std::string statement_number, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetNextFirst(StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetNextSecond(StatementType statement_type);
  bool HasNextRelationship();
  bool HasNext(std::string statement_number);
  bool HasNextBy(std::string statement_number);
  bool IsNext(std::string statement_num_1, std::string statement_num_2);

  //!API for Next*
  PkbCommunicationTypes::PairConstraintSet GetNextStarPairs(StatementType type_1, StatementType type_2);
  PkbCommunicationTypes::SingleConstraintSet GetNextStar(std::string statement_number, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetNextStarBy(std::string statement_number, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetNextStarFirst(StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetNextStarSecond(StatementType statement_type);
  bool HasNextStarRelationship();
  bool HasNextStar(std::string statement_number);
  bool HasNextStarBy(std::string statement_number);
  bool IsNextStar(std::string statement_num_1, std::string statement_num_2);
};
