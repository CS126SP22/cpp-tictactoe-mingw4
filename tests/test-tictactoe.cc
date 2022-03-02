#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("Empty string") {
      REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }

  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board("xxxxoooo"), std::invalid_argument);
  }

  SECTION("String is too long") {
    REQUIRE_THROWS_AS(Board("xxxxxooooo"), std::invalid_argument);
  }
}


TEST_CASE("Boards with no winner") {
  SECTION("Empty board with special characters") {
    REQUIRE(Board("!@#$%^&*(").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Full board with no winner") {
    REQUIRE(Board("xoxxxooxo").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress, X moved last") {
    REQUIRE(Board(".xo.x.xo.").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress, O moves last") {
    REQUIRE(Board("xoxoxo...").EvaluateBoard() == BoardState::NoWinner);
  }
}
