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
  PkbCommunicationTypes::PairConstraintSet GetModifiesStatementVariablePairs(StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsModifiesVariable(std::string var_name, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatModify(StatementType stmt_type);
  bool HasModifiesStatementRelationship(std::string stmt_num, std::string var_name);

  //! API for Modifies - Procedure
  PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByProcedure(std::string procedure_name);
  PkbCommunicationTypes::PairConstraintSet GetModifiesProcedureVariablePairs();
  PkbCommunicationTypes::SingleConstraintSet GetProceduresModifiesVariable(std::string var_name);
  PkbCommunicationTypes::SingleConstraintSet GetProceduresThatModify();
  bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name);

  //!API for Follows
  PkbCommunicationTypes::PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsFollowedBy(std::string statement_num, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsFollowing(std::string statement_num, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type);
  bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower);
  bool IsAnyFollowsRelationshipPresent();

  //!API for Parent

  PkbCommunicationTypes::PairConstraintSet GetParentChildPairs(StatementType statement_type, StatementType statement_type_child);
  PkbCommunicationTypes::SingleConstraintSet GetStatementThatIsParentOf(std::string statement_num, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildrenOf(std::string statement_num, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreParents(StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreChildren(StatementType statement_type);
  bool HasParentChildRelationship(std::string statement_num, std::string statement_num_child);
  bool IsAnyParentRelationshipPresent();

  //!API for ParentStar
  PkbCommunicationTypes::PairConstraintSet GetAncestorDescendantPairs(StatementType statement_type, StatementType statement_type_descendant);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestorOf(std::string statement_num, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendantsOf(std::string statement_num, StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreAncestors(StatementType statement_type);
  PkbCommunicationTypes::SingleConstraintSet GetStatementsThatAreDescendants(StatementType statement_type);
  bool HasAncestorDescendantRelationship(std::string statement_num, std::string statement_num_descendant);
  bool IsAnyAncestorDescendantRelationshipPresent();
};
