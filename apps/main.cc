#include <iostream>
#include <string>

#include <tictactoe/tictactoe.h>

using tictactoe::BoardState;

int main() {
  std::cout << "Type a board string: ";

  std::string board_string;
  std::cin >> board_string;

  BoardState state = tictactoe::Board(board_string).EvaluateBoard();

  std::string message;
  switch (state) {
    case BoardState::NoWinner:
      message = "No won has won this game";
      break;
    case BoardState::Xwins:
      message = "X won, congratulations!";
      break;
    case BoardState::Owins:
      message = "O won, that's an impressive feat for the second player!";
      break;
    case BoardState::UnreachableState:
      message = "This board is unreachable, someone must've cheated...";
      break;
  }

  std::cout << message << std::endl;
  return 0;
}
