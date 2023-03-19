//! Preserving the stub written previously
#pragma once
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Pkb.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Types/PkbCommunicationTypes.h"

//!Should inherit from PKBReadFacade
class StubPkbReadFacade: public PkbReadFacade {
 public:
  StubPkbReadFacade(Pkb& pkb);

  ~StubPkbReadFacade();

  //! API for basic Select statements
  SingleSet GetVariables() override;
  SingleSet GetConstants() override;
  SingleSet GetProcedures() override;
  SingleSet GetStatements() override;
  SingleSet GetReadStatements() override;
  SingleSet GetPrintStatements() override;
  SingleSet GetCallStatements() override;
  SingleSet GetWhileStatements() override;
  SingleSet GetIfStatements() override;
  SingleSet GetAssignStatements() override;

  //! API for Modifies - Statement
  SingleSet GetVariablesModifiedByStatement(const StatementNumber& statement_number) override;
  PairSet GetModifiesStatementVariablePairs(const StatementType& statement_type) override;
  SingleSet GetStatementsModifiesVariable(const Variable& variable, const StatementType& statement_type) override;
  SingleSet GetStatementsThatModify(const StatementType& statement_type) override;
  bool HasModifiesStatementRelationship(const StatementNumber& statement_number, const Variable& variable) override;

  //! API for Modifies - Procedure
  SingleSet GetVariablesModifiedByProcedure(const Procedure& procedure) override;
  PairSet GetModifiesProcedureVariablePairs() override;
  SingleSet GetProceduresModifiesVariable(const Variable& variable) override;
  SingleSet GetProceduresThatModify() override;
  bool HasModifiesProcedureRelationship(const Procedure& procedure, const Variable& variable) override;

  //! API for Uses - Statement
  PairSet GetUsesStatementVariablePairs(const StatementType& statement_type) override;
  SingleSet GetStatementsThatUses(const StatementType& statement_type) override;
  SingleSet GetVariablesUsedByStatement(const StatementNumber& statement_number) override;
  SingleSet GetStatementsUsesVariable(const StatementType& statement_type, const Variable& variable) override;
  bool HasUsesStatementRelationship(const StatementNumber& statement_number, const Variable& variable) override;

  //! API for Uses - Procedure
  PairSet GetUsesProcedureVariablePairs() override;
  SingleSet GetProceduresThatUse() override;
  SingleSet GetVariablesUsedByProcedure(const Procedure& procedure) override;
  SingleSet GetProceduresUsesVariable(const Variable& variable) override;
  bool HasUsesProcedureRelationship(const Procedure& procedure, const Variable& variable) override;

  //!API for Follows
  PairSet GetFollowPairs(const StatementType& statement_type, const StatementType& statement_type_follower) override;
  SingleSet GetStatementFollowedBy(const StatementNumber& statement_number,
                                   const StatementType& statement_type) override;
  SingleSet GetStatementFollowing(const StatementNumber& statement_number,
                                  const StatementType& statement_type) override;
  SingleSet GetStatementsWithFollowers(const StatementType& statement_type) override;
  SingleSet GetStatementThatAreFollowers(const StatementType& statement_type) override;
  bool HasFollowsRelationship(const StatementNumber& statement_number,
                              const StatementNumber& statement_number_follower) override;
  bool IsAnyFollowsRelationshipPresent() override;

  //!API for FollowsStar
  PairSet GetFollowsStarPairs(const StatementType& statement_type_1, const StatementType& statement_type_2) override;
  SingleSet GetFollowsStar(const StatementNumber& statement_number, const StatementType& statement_type) override;
  SingleSet GetFollowsStarBy(const StatementNumber& statement_number, const StatementType& statement_type) override;
  SingleSet GetFollowsStarFirst(const StatementType& statement_type) override;
  SingleSet GetFollowsStarSecond(const StatementType& statement_type) override;
  bool HasFollowsStarRelationship() override;
  bool HasFollowsStar(const StatementNumber& statement_number) override;
  bool HasFollowsStarBy(const StatementNumber& statement_number) override;
  bool IsFollowsStar(const StatementNumber& statement_number_1, const StatementNumber& statement_number_2) override;

  //!API for Parent
  PairSet GetParentChildPairs(const StatementType& statement_type, const StatementType& statement_type_child) override;
  SingleSet GetStatementThatIsParentOf(const StatementNumber& statement_number,
                                       const StatementType& statement_type) override;
  SingleSet GetStatementsThatAreChildrenOf(const StatementNumber& statement_number,
                                           const StatementType& statement_type) override;
  SingleSet GetStatementsThatAreParents(const StatementType& statement_type) override;
  SingleSet GetStatementsThatAreChildren(const StatementType& statement_type) override;
  bool HasParentChildRelationship(const StatementNumber& statement_number,
                                  const StatementNumber& statement_number_child) override;
  bool IsAnyParentRelationshipPresent() override;

  //!API for ParentStar
  PairSet GetAncestorDescendantPairs(const StatementType& statement_type,
                                     const StatementType& statement_type_descendant) override;
  SingleSet GetStatementsThatAreAncestorOf(const StatementNumber& statement_number,
                                           const StatementType& statement_type) override;
  SingleSet GetStatementsThatAreDescendantsOf(const StatementNumber& statement_number,
                                              const StatementType& statement_type) override;
  SingleSet GetStatementsThatAreAncestors(const StatementType& statement_type) override;
  SingleSet GetStatementsThatAreDescendants(const StatementType& statement_type) override;
  bool HasAncestorDescendantRelationship(const StatementNumber& statement_number,
                                         const StatementNumber& statement_number_descendant) override;
  bool IsAnyAncestorDescendantRelationshipPresent() override;

  //!API for pattern
  SingleSet GetAssignWithExactExpression(const ExpressionPtr& expr) override;
  SingleSet GetAssignWithPartialExpression(const ExpressionPtr& sub_expr) override;
  PairSet GetIfConditionVariablePair() override;
  SingleSet GetIfWithConditionVariable(const Variable& variable) override;
  SingleSet GetIfThatHasConditionVariable() override;
  PairSet GetWhileConditionVariablePair() override;
  SingleSet GetWhileWithConditionVariable(const Variable& variable) override;
  SingleSet GetWhileThatHasConditionVariable() override;

  //!API for Next
  PairSet GetNextPairs(const StatementType& statement_type_1, const StatementType& statement_type_2) override;
  SingleSet GetNext(const StatementNumber& statement_number, const StatementType& statement_type) override;
  SingleSet GetNextBy(const StatementNumber& statement_number, const StatementType& statement_type) override;
  SingleSet GetNextFirst(const StatementType& statement_type) override;
  SingleSet GetNextSecond(const StatementType& statement_type) override;
  bool HasNextRelationship() override;
  bool HasNext(const StatementNumber& statement_number) override;
  bool HasNextBy(const StatementNumber& statement_number) override;
  bool IsNext(const StatementNumber& statement_number_1, const StatementNumber& statement_number_2) override;

  //!API for Next*
  PairSet GetNextStarPairs(const StatementType& statement_type_1, const StatementType& statement_type_2) override;
  SingleSet GetNextStar(const StatementNumber& statement_number, const StatementType& statement_type) override;
  SingleSet GetNextStarBy(const StatementNumber& statement_number, const StatementType& statement_type) override;
  SingleSet GetNextStarFirst(const StatementType& statement_type) override;
  SingleSet GetNextStarSecond(const StatementType& statement_type) override;
  bool HasNextStarRelationship() override;
  bool HasNextStar(const StatementNumber& statement_number) override;
  bool HasNextStarBy(const StatementNumber& statement_number) override;
  bool IsNextStar(const StatementNumber& statement_number_1, const StatementNumber& statement_number_2) override;

  // !API for Affects
  PairSet GetAffectsPairs() override;
  SingleSet GetAssignsAffectedBy(const StatementNumber& statement_number) override;
  SingleSet GetAssignsAffecting(const StatementNumber& statement_number) override;
  SingleSet GetAllAssignsThatAreAffected() override;
  SingleSet GetAllAssignsThatAffect() override;
  bool HasAffectsRelationship(const StatementNumber& statement_number, 
                              const StatementNumber& statement_number_being_affected) override;
  bool IsThereAnyAffectsRelationship() override;

  // !API for Affects*
  PairSet GetAffectsStarPairs() override;
  SingleSet GetAssignsAffectedStarBy(const StatementNumber& statement_number) override;
  SingleSet GetAssignsAffectingStar(const StatementNumber& statement_number) override;
  SingleSet GetAllAssignsThatAreAffectedStar() override;
  bool IsThereAnyAffectsStarRelationship() override;
  bool HasAffectsStarRelationship(const StatementNumber& statement_number, 
                                  const StatementNumber& statement_number_being_affected) override;
  SingleSet GetAllAssignsThatAffectStar() override;
};
