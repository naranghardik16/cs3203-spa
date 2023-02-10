//! Preserving the stub written previously

#pragma once
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"
#include "PKB/Types/PkbCommunicationTypes.h"

//!Should inherit from PKBReadFacade
class StubPkbReadFacade {
 public:
  StubPkbReadFacade(PKB& pkb) {};

  ~StubPkbReadFacade();

  //! API for basic Select statements
  PkbCommunicationTypes::SingleConstraintSet GetVariables();
  PkbCommunicationTypes::SingleConstraintSet GetConstants();
  PkbCommunicationTypes::SingleConstraintSet GetProcedures();
  PkbCommunicationTypes::SingleConstraintSet GetStatements();
  PkbCommunicationTypes::SingleConstraintSet GetReadStatements();
  PkbCommunicationTypes::SingleConstraintSet GetPrintStatements();
  PkbCommunicationTypes::SingleConstraintSet GetCallStatements();
  PkbCommunicationTypes::SingleConstraintSet GetWhileStatements();
  PkbCommunicationTypes::SingleConstraintSet GetIfStatements();
  PkbCommunicationTypes::SingleConstraintSet GetAssignStatements();

  //! API for Modifies - Statement
  PkbCommunicationTypes::SingleConstraintSet GetVariablesModifiedByStatement(std::string statement_number);
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

};
