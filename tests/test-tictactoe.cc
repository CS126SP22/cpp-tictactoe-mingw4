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

  SECTION("Game in progress, X moved last, case-insensitive") {
    REQUIRE(Board(".xo.X.xo.").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Game in progress, O moves last, case-insensitive") {
    REQUIRE(Board("xOxoxO...").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("Boards in unreachableState, case-insensitive") {
  SECTION("numX < numO") {
    REQUIRE(Board("x.o.O....").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX > numO + 1") {
    REQUIRE(Board("x0X0Xx...").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX == numO when X has three-in-a-row, horizontally") {
    REQUIRE(Board("o..XxXoO.").EvaluateBoard() == BoardState::UnreachableState);
  }

  SECTION("numX == numO + 1, when O has three-in-a-row, vertically") {
    REQUIRE(Board(".oxxO.xox").EvaluateBoard() == BoardState::UnreachableState);
  }
}

TEST_CASE("Boards with X wins, case-insensitive") {
  SECTION("X vertically wins, second-row") {
    REQUIRE(Board(".xooX..x.").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("X horizontally wins, third-row") {
    REQUIRE(Board("...oo.XxX").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("X right-diagonally wins") {
    REQUIRE(Board("..xoX.x.o").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("X has two three-in-a-rows, not in the same direction") {
    REQUIRE(Board("xooxooXxx").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("X has one three-in-a-rows and one-three-in-a-diagonal") {
    REQUIRE(Board("xoxxxoXoo").EvaluateBoard() == BoardState::Xwins);
  }
}

TEST_CASE("Boards with O wins, case-insensitive") {
  SECTION("O vertically wins, third row") {
    REQUIRE(Board("..Oxxox.o").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("O horizontally wins, first-row") {
    REQUIRE(Board("ooO.xx.x.").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("O left-diagonally wins") {
    REQUIRE(Board("o..xO.xxO").EvaluateBoard() == BoardState::Owins);
  }
}
