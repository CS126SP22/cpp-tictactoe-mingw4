#include <stdexcept>
#include <string>

#include "tictactoe/tictactoe.h"

namespace tictactoe {

using std::string;

Board::Board(const string& board) {
  throw std::invalid_argument("The string provided is not a valid board.");
}

BoardState Board::EvaluateBoard() const {
  return BoardState::NoWinner;
}

}  // namespace tictactoe
