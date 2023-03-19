//! Preserving the stub written previously

#include "StubPKBReadFacade.h"

#include <memory>
#include "PKB/Pkb.h"
#include "PKB/Interfaces/PkbReadFacade.h"

StubPkbReadFacade::StubPkbReadFacade(Pkb &pkb): PkbReadFacade(pkb) {}

StubPkbReadFacade::~StubPkbReadFacade() {}

PkbReadFacade::SingleSet StubPkbReadFacade::GetVariables() {
  SingleSet var_set({"a", "x", "y", "g"});
  return var_set;
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetConstants() {
  SingleSet set({"22", "23", "24"});
  return set;
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetProcedures() {
  SingleSet set({"execute", "anya"});
  return set;
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatements() {
  return {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetReadStatements() {
  SingleSet set({"1"});
  return set;
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetPrintStatements() {
  SingleSet print_set({"4", "9"});
  return print_set;
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetCallStatements() {
  SingleSet set({"3"});
  return set;
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetWhileStatements() {
  return {"8"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetIfStatements() {
  return {"5"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAssignStatements() {
  SingleSet set({"2", "6", "7"});
  return set;
}


//! Modifies Statement API
PkbReadFacade::PairSet StubPkbReadFacade::GetModifiesStatementVariablePairs(
    const StatementType& statement_type
    ) {
  if (statement_type == StatementType::READ) {
    return {std::make_pair("1", "x")};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {{"2", "a"}, {"6", "y"}, {"7", "y"}};
  }
  return {};
}


PkbReadFacade::SingleSet StubPkbReadFacade::GetVariablesModifiedByStatement(
    const StatementNumber& statement_number
    ) {
  if (statement_number == "1") {
    return {"x"};
  }
  if (statement_number == "2") {
    return {"a"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsModifiesVariable(
    const Variable& variable,
    const StatementType& statement_type
    ) {
  if (variable == "x" && statement_type == StatementType::READ) {
    return {"1"};
  }
  if (variable == "a" && statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatModify(const StatementType& statement_type) {
  if (statement_type == StatementType::READ) {
    return {"1"};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

bool StubPkbReadFacade::HasModifiesStatementRelationship(const StatementNumber& statement_number,
                                                         const Variable& variable) {
  if (statement_number == "1" && variable == "x") {
    return true;
  }
  if (statement_number == "2" && variable == "a") {
    return true;
  }
  return false;
}


//! Modifies Procedure API
PkbReadFacade::PairSet StubPkbReadFacade::GetModifiesProcedureVariablePairs() {
  return {std::make_pair("execute", "x"), std::make_pair("execute", "a")};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetVariablesModifiedByProcedure(
    const Procedure& procedure
    ) {
  if (procedure == "execute") {
    return {"x", "a"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetProceduresModifiesVariable(const Variable& variable) {
  if (variable == "x") {
    return {"execute"};
  }
  if (variable == "a") {
    return {"execute"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetProceduresThatModify() {
  return {"execute"};
}

bool StubPkbReadFacade::HasModifiesProcedureRelationship(const Procedure& procedure, const Variable& variable) {
  if (procedure == "execute" && variable == "x") {
    return true;
  }
  if (procedure == "execute" && variable == "a") {
    return true;
  }
  return false;
}

//! Uses Statement API
PkbReadFacade::PairSet StubPkbReadFacade::GetUsesStatementVariablePairs(
    const StatementType& statement_type
    ) {
  if (statement_type == StatementType::ASSIGN) {
    return {{"2", "a"}, {"2", "y"}, {"6", "g"}, {"7", "y"}};
  }
  return {{"2", "x"}, {"2", "y"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatUses(const StatementType& statement_type) {
  return {"2"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetVariablesUsedByStatement(
    const StatementNumber& statement_number
    ) {
  if (statement_number == "2") {
    return {"x", "y"};
  }

  if (statement_number == "6") {
    return {"g"};
  }

  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsUsesVariable(
    const StatementType& statement_type, const Variable& variable
    ) {
  if (statement_type == StatementType::ASSIGN && variable == "g") {
    return {"6"};
  }
  return {"2"};
}

bool StubPkbReadFacade::HasUsesStatementRelationship(const StatementNumber& statement_number,
                                                     const Variable& variable) {
  if (statement_number == "2") {
    return true;
  }
  if (statement_number == "6" && variable == "g") {
    return true;
  }
  return false;
}


//! Uses Procedure API
PkbReadFacade::PairSet StubPkbReadFacade::GetUsesProcedureVariablePairs() {
  return {{"anya", "x"}, {"anya", "y"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetProceduresThatUse() {
  return {"anya"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetVariablesUsedByProcedure(const Procedure& procedure) {
  if (procedure == "anya") {
    return {"x", "y"};
  } else {
    return {};
  }
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetProceduresUsesVariable(const Variable& variable) {
  return {"anya"};
}

bool StubPkbReadFacade::HasUsesProcedureRelationship(const Procedure& procedure, const Variable& variable) {
  if (procedure == "anya") {
    return true;
  } else {
    return false;
  }
}

//! Follows API
PkbReadFacade::PairSet StubPkbReadFacade::GetFollowPairs(
    const StatementType& statement_type,
    const StatementType& statement_type_follower
    ) {
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::ASSIGN) {
    return {std::make_pair("1", "2")};
  }
  if (statement_type == StatementType::READ && statement_type_follower == StatementType::CALL) {
    return {std::make_pair("1", "3")};
  }
  return {};
}


PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementFollowedBy(
    const StatementNumber& statement_number,
    const StatementType& statement_type
    ) {
  if (statement_number == "3" && statement_type == StatementType::STATEMENT) {
    return {"2"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementFollowing(
    const StatementNumber& statement_number,
    const StatementType& statement_type
    ) {
  if (statement_number == "1" && (statement_type == StatementType::STATEMENT ||
  statement_type == StatementType::ASSIGN)) {
    return {"2"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsWithFollowers(
    const StatementType& statement_type
    ) {
  if (statement_type == StatementType::PRINT) {
    return {"1"};
  }
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementThatAreFollowers(
    const StatementType& statement_type
    ) {
  if (statement_type == StatementType::ASSIGN) {
    return {"2"};
  }
  if (statement_type == StatementType::READ) {
    return {"3"};
  }
  return {};
}


bool StubPkbReadFacade::HasFollowsRelationship(const StatementNumber& statement_number,
                                               const StatementNumber& statement_number_follower) {
  if (statement_number == "1" && statement_number_follower == "2") {
    return true;
  }
  if (statement_number == "1" && statement_number_follower == "3") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsAnyFollowsRelationshipPresent() {
  return true;
}

//! Follows* API
PkbReadFacade::PairSet StubPkbReadFacade::GetFollowsStarPairs(const StatementType& statement_type_1,
                                                                            const StatementType& statement_type_2) {
  return {{"1", "2"}, {"1", "3"}, {"2", "3"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetFollowsStar(const StatementNumber& statement_number,
                                                                         const StatementType& statement_type) {
  if (statement_number == "1") {
    return {"2", "3"};
  } else if (statement_number == "2") {
    return {"3"};
  } else {
    return {};
  }
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetFollowsStarBy(const StatementNumber& statement_number,
                                                                           const StatementType& statement_type) {
  if (statement_number == "2") {
    return {"1"};
  } else if (statement_number == "3") {
    return {"1", "2"};
  } else {
    return {};
  }
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetFollowsStarFirst(const StatementType& statement_type) {
  return {"1", "2"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetFollowsStarSecond(const StatementType& statement_type) {
  return {"2", "3"};
}

bool StubPkbReadFacade::HasFollowsStarRelationship() {
  return true;
}

bool StubPkbReadFacade::HasFollowsStar(const StatementNumber& statement_number) {
  if (statement_number == "1" || statement_number == "2") {
    return true;
  } else {
    return false;
  }
}

bool StubPkbReadFacade::HasFollowsStarBy(const StatementNumber& statement_number) {
  if (statement_number == "2" || statement_number == "3") {
    return true;
  } else {
    return false;
  }
}

bool StubPkbReadFacade::IsFollowsStar(const StatementNumber& statement_number_1,
                                      const StatementNumber& statement_number_2) {
  if (statement_number_1 == "1" && statement_number_2 == "2") {
    return true;
  } else {
    return false;
  }
}

//! Parent API
PkbReadFacade::PairSet StubPkbReadFacade::GetParentChildPairs(
    const StatementType& statement_type,
    const StatementType& statement_type_child
    ) {
  if (statement_type == StatementType::IF && statement_type_child == StatementType::ASSIGN) {
    return {std::make_pair("5", "6"), std::make_pair("5", "7")};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementThatIsParentOf(
    const StatementNumber& statement_number,
    const StatementType& statement_type
    ) {
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatAreChildrenOf(
    const StatementNumber& statement_number,
    const StatementType& statement_type
    ) {
  if (statement_number == "5" &&
  (statement_type == StatementType::STATEMENT || statement_type == StatementType::ASSIGN)) {
    return {"6", "7"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatAreParents(
    const StatementType& statement_type
    ) {
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatAreChildren(
    const StatementType& statement_type
    ) {
  if (statement_type == StatementType::ASSIGN) {
    return {"6", "7"};
  }
  return {};
}

bool StubPkbReadFacade::HasParentChildRelationship(const StatementNumber& statement_number,
                                                   const StatementNumber& statement_number_child) {
  if (statement_number == "5" && statement_number_child == "6") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsAnyParentRelationshipPresent() {
  return true;
}

PkbReadFacade::PairSet StubPkbReadFacade::GetAncestorDescendantPairs(
    const StatementType& statement_type,
    const StatementType& statement_type_descendant
    ) {
  if (statement_type == StatementType::IF && statement_type_descendant == StatementType::PRINT) {
    return {std::make_pair("5", "9")};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatAreAncestorOf(
    const StatementNumber& statement_number,
    const StatementType& statement_type
    ) {
  if (statement_number == "9" && (statement_type == StatementType::STATEMENT || statement_type == StatementType::IF)) {
    return {"5"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatAreDescendantsOf(
    const StatementNumber& statement_number,
    const StatementType& statement_type
    ) {
  if (statement_number == "5" && (statement_type == StatementType::STATEMENT ||
  statement_type == StatementType::PRINT)) {
    return {"9"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatAreAncestors(
    const StatementType& statement_type
    ) {
  if (statement_type == StatementType::IF) {
    return {"5"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetStatementsThatAreDescendants(
    const StatementType& statement_type
    ) {
  if (statement_type == StatementType::PRINT) {
    return {"9"};
  }
  return {};
}

bool StubPkbReadFacade::HasAncestorDescendantRelationship(const StatementNumber& statement_number,
                                                          const StatementNumber& statement_number_descendant) {
  if (statement_number == "5" && statement_number_descendant == "9") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsAnyAncestorDescendantRelationshipPresent() {
  return true;
}

//! Pattern API
PkbReadFacade::SingleSet StubPkbReadFacade::GetAssignWithExactExpression(
    const std::shared_ptr<Expression> &expr
    ) {
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAssignWithPartialExpression(
    const std::shared_ptr<Expression> &sub_expr
    ) {
  if (sub_expr->GetName() == "g") {
    return {"6"};
  }
  return {"2"};
}

PkbReadFacade::PairSet StubPkbReadFacade::GetIfConditionVariablePair() {
  return {{"4", "x"}, {"4", "y"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetIfWithConditionVariable(const std::string &variable) {
  if (variable == "x") {
    return {"4"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetIfThatHasConditionVariable() {
  return {"4"};
}

PkbReadFacade::PairSet StubPkbReadFacade::GetWhileConditionVariablePair() {
  return {{"6", "x"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetWhileWithConditionVariable(
    const std::string &variable
    ) {
  if (variable == "x") {
    return {"6"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetWhileThatHasConditionVariable() {
  return {"6"};
}

//! Next API
PkbReadFacade::PairSet StubPkbReadFacade::GetNextPairs(const StatementType& statement_type_1,
                                                                         const StatementType& statement_type_2) {
  return {{"1", "2"}, {"2", "3"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetNext(const StatementNumber& statement_number,
                                                                      const StatementType& statement_type) {
  if (statement_number == "1") {
    return {"2"};
  }
  return {"3"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetNextBy(const StatementNumber& statement_number,
                                                                        const StatementType& statement_type) {
  if (statement_number == "3") {
    return {"2"};
  }
  return {"1"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetNextFirst(const StatementType& statement_type) {
  return {"1", "2"};
}
PkbReadFacade::SingleSet StubPkbReadFacade::GetNextSecond(const StatementType& statement_type) {
  return {"2", "3"};
}

bool StubPkbReadFacade::HasNextRelationship() {
  return true;
}

bool StubPkbReadFacade::HasNext(const StatementNumber& statement_number) {
  if (statement_number == "1" || statement_number == "2") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::HasNextBy(const StatementNumber& statement_number) {
  if (statement_number == "2" || statement_number == "3") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsNext(const StatementNumber& statement_number_1, const StatementNumber& statement_number_2) {
  if (statement_number_1 == "1" && statement_number_2 == "2") {
    return true;
  }
  return false;
}

//! Next* API
PkbReadFacade::PairSet StubPkbReadFacade::GetNextStarPairs(const StatementType& statement_type_1,
                                                                             const StatementType& statement_type_2) {
  return {{"4", "5"}, {"5", "6"}, {"4", "6"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetNextStar(const StatementNumber& statement_number,
                                                                          const StatementType& statement_type) {
  if (statement_number == "4") {
    return {"5", "6"};
  }
  return {"6"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetNextStarBy(const StatementNumber& statement_number,
                                                                            const StatementType& statement_type) {
  if (statement_number == "6") {
    return {"4", "5"};
  }
  return {"4"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetNextStarFirst(const StatementType& statement_type) {
  return {"4"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetNextStarSecond(const StatementType& statement_type) {
  return {"6"};
}

bool StubPkbReadFacade::HasNextStarRelationship() {
  return true;
}

bool StubPkbReadFacade::HasNextStar(const StatementNumber& statement_number) {
  if (statement_number == "4" || statement_number == "5") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::HasNextStarBy(const StatementNumber& statement_number) {
  if (statement_number == "5" || statement_number == "6") {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsNextStar(const StatementNumber& statement_number_1,
                                   const StatementNumber& statement_number_2) {
  if (statement_number_1 == "4" && statement_number_2 == "6") {
    return true;
  }
  return false;
}

// Affects API
PkbReadFacade::PairSet  StubPkbReadFacade::GetAffectsPairs() {
  return {{"1", "5"}, {"3", "5"}, {"2", "4"}, {"2", "6"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAssignsAffectedBy(const StatementNumber& statement_number) {
  if (statement_number == "1") {
    return {"5"};
  }
  if (statement_number == "3") {
    return {"5"};
  }
  if (statement_number == "2") {
    return {"4", "6"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAssignsAffecting(const StatementNumber& statement_number) {
  if (statement_number == "5") {
    return {"1", "3"};
  }
  if (statement_number == "4") {
    return {"2"};
  }
  if (statement_number == "6") {
    return {"2"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAllAssignsThatAreAffected() {
  return {"4", "5", "6"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAllAssignsThatAffect() {
  return {"1", "2", "3"};
}

bool StubPkbReadFacade::HasAffectsRelationship(const StatementNumber& statement_number,
                                               const StatementNumber& statement_number_being_affected) {
  if ((statement_number == "1") && (statement_number_being_affected == "5")) {
    return true;
  }
  if ((statement_number == "3") && (statement_number_being_affected == "5")) {
    return true;
  }
  if ((statement_number == "2") && (statement_number_being_affected == "4")) {
    return true;
  }
  if ((statement_number == "2") && (statement_number_being_affected == "6")) {
    return true;
  }
  return false;
}

bool StubPkbReadFacade::IsThereAnyAffectsRelationship() {
  return true;
}

// Affects* API
PkbReadFacade::PairSet StubPkbReadFacade::GetAffectsStarPairs() {
  return {{"1", "4"}, {"1", "10"}, {"1", "11"}, {"9", "12"},
          {"12", "13"}, {"9", "13"}};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAssignsAffectedStarBy(const StatementNumber& statement_number) {
  if (statement_number == "1") {
    return {"4", "10", "11"};
  }
  if (statement_number == "9") {
    return {"12", "13"};
  }
  if (statement_number == "12") {
    return {"13"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAssignsAffectingStar(const StatementNumber& statement_number) {
  if (statement_number == "4" || statement_number == "10" || statement_number == "11") {
    return {"1"};
  }
  if (statement_number == "12") {
    return {"9"};
  }
  if (statement_number == "13") {
    return {"9", "12"};
  }
  return {};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAllAssignsThatAreAffectedStar() {
  return {"4", "10", "11", "12", "13"};
}

PkbReadFacade::SingleSet StubPkbReadFacade::GetAllAssignsThatAffectStar() {
  return {"1", "9", "12"};
}

bool StubPkbReadFacade::HasAffectsStarRelationship(const StatementNumber& statement_number,
                                                   const StatementNumber& statement_number_being_affected) {
  if (statement_number == "1") {
    if (statement_number_being_affected == "4" || statement_number_being_affected == "10" ||
    statement_number_being_affected == "11") {
      return true;
    }
  }
  if (statement_number == "9") {
    if (statement_number_being_affected == "12" || statement_number_being_affected == "13") {
      return true;
    }
  }
  if (statement_number == "12") {
    if (statement_number_being_affected == "13") {
      return true;
    }
  }
  return false;
}

bool StubPkbReadFacade::IsThereAnyAffectsStarRelationship() {
  return true;
}
