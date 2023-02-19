#include <catch.hpp>
#include <memory>
#include <string>
#include <unordered_set>

#include "PKB/Stores/AssignmentStore.h"
#include "SP/Parser/AssignStatementParser.h"

TEST_CASE("Testcases for Assignment Store") {
  SECTION("Singleton (One Constant)") {
    auto assignment_store = new AssignmentStore();
    std::shared_ptr<Expression> root;
    root = std::make_shared<Constant>("7");

    assignment_store->addAssignmentExpression("1", root);

//    REQUIRE(assignment_store->);
  }
}

