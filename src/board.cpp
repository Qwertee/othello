#include "board.h"

// constexpr board::space_types default_board_state[BOARD_WIDTH][BOARD_HEIGHT];

board::board() {
  load_default_board();

}

void board::load_default_board() {
  for (int x = 0; x < BOARD_WIDTH; x++) {
    for (int y = 0; y < BOARD_HEIGHT; y++) {
      board_array[x][y] = default_board_state[x][y];
    }
  }
}


bool place_move(int x, int y, board::space_types current_player) {

  return false;
}
