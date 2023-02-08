//! Preserving the stub written previously
/*
#pragma once
#include <unordered_set>
#include "PKB/Types/PkbTypes.h"
#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/PKB.h"
#include "PKB/Interfaces/PkbReadFacade.h"

class StubPkbReadFacade : public PkbReadFacade {
 public:
  StubPkbReadFacade(PKB& pkb) : PKBReadFacade(pkb);

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
  PairConstraintSet GetModifiesProcedureVariablePairs(bool is_call);
  SingleConstraintSet GetProceduresModifiesVariable(std::string var_name, bool is_call);
  SingleConstraintSet GetProceduresThatModify(bool is_call);
  bool HasModifiesProcedureRelationship(std::string procedure_name, std::string var_name);

  //!API for Follows
  PairConstraintSet GetFollowPairs(StatementType statement_type, StatementType statement_type_follower);
  SingleConstraintSet GetStatementsFollowedBy(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsFollowing(std::string statement_num, StatementType statement_type);
  SingleConstraintSet GetStatementsWithFollowers(StatementType statement_type);
  SingleConstraintSet GetStatementThatAreFollowers(StatementType statement_type);
  bool HasFollowsRelationship(std::string statement_num, std::string statement_num_follower);
  bool IsAnyFollowsRelationshipPresent();


};
*/