#include <stdexcept>
#include <string>
#include <stdbool.h>
#include <iostream>

#include "tictactoe/tictactoe.h"

namespace tictactoe {

using std::string;

Board::Board(const string& board) {
  this->dimension_ = 3;
  this->board_ = board;
  if (board.length() != (this->dimension_ * this->dimension_)) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }
}

size_t Board::CheckHorizontals(char player) const {
  //Unify the board by changing all characters into lower cases.
  std::string unified_board = "";
  size_t dimension = this->dimension_;
  for (size_t i = 0; i < board_.length(); i++) {
    unified_board.push_back(tolower(board_[i]));
  }
  //count times at which requirements are satisfied.
  size_t count = 0;
  for (size_t row = 0; row < dimension; row++) {
    bool win = true;
    for (size_t column = 0; column < dimension; column++) {
      if (unified_board[row * dimension + column] != player) {
        win = false;
        break;
      }
    }
    if (win) {
      count++;
    }
  }
  return count;
}

size_t Board::CheckVerticals(char player) const {
  //Unify the board by changing all characters into lower cases.
  std::string unified_board = "";
  size_t dimension = this->dimension_;
  for (size_t i = 0; i < board_.length(); i++) {
    unified_board.push_back(tolower(board_[i]));
  }
  size_t count = 0;
  for (size_t column = 0; column < dimension; column++) {
    bool win = true;
    for (size_t row = 0; row < dimension; row++) {
      if (unified_board[row * dimension + column] != player) {
        win = false;
        break;
      }
    }
    if (win) {
      count++;
    }
  }
  return count;
}

size_t Board::CheckDiagonals(char player) const {
  //Unify the board by changing all characters into lower cases.
  std::string unified_board = "";
  size_t dimension = this->dimension_;
  for (size_t i = 0; i < board_.length(); i++) {
    unified_board.push_back(tolower(board_[i]));
  }
    size_t countRight = 1;
    for (size_t column = 0; column < dimension; column++) {
      if (unified_board[column * dimension + column] != player) {
        countRight = 0;
      }
    }
    int countLeft = 1;
    for (size_t row = dimension; row > 0; row--) {
      if (unified_board[row * dimension - row] != player) {
        countLeft = 0;
      }
    }
    return countLeft + countRight;
}




BoardState Board::EvaluateBoard() const {
  //Check whether the board is legal by checking length.
  size_t dimension = this->dimension_;
  if (board_.length() != (dimension * dimension)) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }

  //Unify the board by changing all characters into lower cases.
  std::string unified_board = "";
  for (size_t i = 0; i < board_.length(); i++) {
    unified_board.push_back(tolower(board_[i]));
  }

  //Count the number of moves of x and o;
  size_t xnum = 0;
  size_t onum = 0;

  for (size_t pos = 0; pos < board_.length(); pos++) {
    char curr = unified_board[pos];
    if (curr == 'x') {
      xnum++;
    } else if (curr == 'o') {
      onum++;
    }
  }
  //Check whether the board is invalid.

  //Check number of moves.
  if (xnum > onum + 1 || xnum < onum) {
    return BoardState::UnreachableState;
  }

  //Count win times.
  size_t xWinTimes;
  size_t oWinTimes;
  xWinTimes = CheckDiagonals('x') + CheckHorizontals('x') + CheckVerticals('x');
  oWinTimes = CheckDiagonals('o') + CheckHorizontals('o') + CheckVerticals('o');

  //Check different players double win.
  if (xWinTimes != 0 && oWinTimes != 0) {
    return BoardState::UnreachableState;
  }

  //Check same player, the number of same type of Horizontal or Vertical win is larger than 1.
  if (CheckHorizontals('x') > 1 || CheckHorizontals('y') > 1
      || CheckVerticals('x') > 1 || CheckVerticals('y') > 1) {
    return BoardState::UnreachableState;
  }

  //Check when numX == numO when X has three-in-a-row/column/diagonal
  if (xnum == onum && xWinTimes >= 1) {
    return BoardState::UnreachableState;
  }

  //Check when numX == numO + 1 when O has three-in-a-row/column/diagonal
  if (xnum == (onum + 1) && oWinTimes >= 1) {
    return BoardState::UnreachableState;
  }


  //Check if x wins.
  if (CheckDiagonals('x') == 1 || CheckDiagonals('x') == 2 || CheckHorizontals('x') == 1 || CheckVerticals('x') == 1) {
    return BoardState::Xwins;
  }

  //Check if o wins.
  if (CheckDiagonals('o') == 1 || CheckDiagonals('o') == 2 || CheckHorizontals('o') == 1 || CheckVerticals('o') == 1) {
    return BoardState::Owins;
  }

  //If x didn't win, o didn't win, and the board is valid, then there is no winner.
  return BoardState::NoWinner;
}

}  // namespace tictactoe
