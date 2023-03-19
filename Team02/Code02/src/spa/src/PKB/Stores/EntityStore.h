#pragma once

#include <string>
#include <unordered_set>

#include "PKB/AbstractDataModels/OneToOneStore.h"
#include "PKB/Types/PkbTypes.h"

/**
 * @class EntityStore
 * Class to store the list of entities used in the SIMPLE program.
 */
class EntityStore {
 public:
  typedef PkbTypes::INDEX Index;
  typedef PkbTypes::VARIABLE Variable;
  typedef PkbTypes::PROCEDURE Procedure;
  typedef PkbTypes::CONSTANT Constant;
  typedef std::unordered_set<Variable> VariableSet;
  typedef std::unordered_set<Procedure> ProcedureSet;
  typedef std::unordered_set<Constant> ConstantSet;
  typedef OneToOneStore<Variable, Index> VariableToIndexStore;
  typedef OneToOneStore<Procedure, Index> ProcedureToIndexStore;
  typedef OneToOneStore<Constant, Index> ConstantToIndexStore;


  /**
   * Constructor for Entity store.
   */
  EntityStore();

  /**
   * Destructor for Entity store.
   */
  ~EntityStore();

  /**
   * Adds a variable entity to the variable store.
   *
   * @param variable - The variable to be inserted.
   * @return The index at which the inserted variable is mapped to.
   */
  Index AddVariable(const Variable& variable);

  /**
   * Adds a procedure entity to the procedure store.
   *
   * @param procedure - The procedure to be inserted.
   * @return The index at which the inserted procedure is mapped to.
   */
  Index AddProcedure(const Procedure& procedure);

  /**
   * Adds a constant entity to the constant store.
   *
   * @param constant - The constant to be inserted.
   * @return The index at which the inserted constant is mapped to.
   */
  Index AddConstant(const Constant& constant);

  /**
   * Retrieves all the variable entities present in the entity store.
   *
   * @return Set of variable entities.
   */
  VariableSet GetVariables();

  /**
   * Retrieves all the procedure entities present in the entity store.
   *
   * @return Set of procedure entities.
   */
  ProcedureSet GetProcedures();

  /**
   * Retrieves all the procedure entities present in the entity store.
   *
   * @return Set of procedure entities.
   */
  ConstantSet GetConstants();

 protected:
  VariableToIndexStore variable_store_;
  ProcedureToIndexStore procedure_store_;
  ConstantToIndexStore constant_store_;
};

