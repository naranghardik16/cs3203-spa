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
  /**
   * Constructor for Entity store.
   */
  EntityStore();

  /**
   * Destructor for Entity store.
   */
  ~EntityStore();

  /**
   * Adds a constant entity to the constant store.
   *
   * @param constant - The constant to be inserted.
   * @return The index at which the inserted constant is mapped to.
   */
  PkbTypes::INDEX addConstant(PkbTypes::CONSTANT constant);

  /**
   * Adds a variable entity to the variable store.
   *
   * @param variable - The variable to be inserted.
   * @return The index at which the inserted variable is mapped to.
   */
  PkbTypes::INDEX addVariable(PkbTypes::VARIABLE variable);

  /**
   * Adds a procedure entity to the procedure store.
   *
   * @param procedure - The procedure to be inserted.
   * @return The index at which the inserted procedure is mapped to.
   */
  PkbTypes::INDEX addProcedure(PkbTypes::PROCEDURE procedure);

  /**
   * Retrieves all the variable entities present in the entity store.
   *
   * @return Set of variable entities.
   */
  std::unordered_set<PkbTypes::VARIABLE> getVariables();

  /**
   * Retrieves all the procedure entities present in the entity store.
   *
   * @return Set of procedure entities.
   */
  std::unordered_set<PkbTypes::PROCEDURE> getProcedures();

  /**
   * Retrieves all the procedure entities present in the entity store.
   *
   * @return Set of procedure entities.
   */
  std::unordered_set<PkbTypes::CONSTANT> getConstants();

 protected:
  OneToOneStore<PkbTypes::VARIABLE, PkbTypes::INDEX> variable_store_;
  OneToOneStore<PkbTypes::PROCEDURE, PkbTypes::INDEX> procedure_store_;
  OneToOneStore<PkbTypes::CONSTANT, PkbTypes::INDEX> constant_store_;
};

