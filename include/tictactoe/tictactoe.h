#pragma once

#include <string>
#include <vector>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard() const;

 private:
  /// TODO: add your helper functions and member variables here
  size_t dimension_;
  std::string board_;
  /**
   * This method should return the result whether certain player fills all positions on a certain row.
   * @param player the checked player in lower case.
   * @return times horizontal conditions for possible wins are reached.
   */
  size_t CheckHorizontals(char player) const;

  /**
   * This method should return the result whether certain player fills all positions on a certain column.
   * @param player the checked player in lower case.
   * @return times vertical conditions for possible wins are reached.
   */
  size_t CheckVerticals(char player) const;

  /**
   *This method should return the result whether certain player fills all positions on the diagonal.
   * @param player the checked player in lower case.
   * @return times Diagonal condition for possible wins are reached.
   */
  size_t CheckDiagonals(char player) const;

};

}  // namespace tictactoe
