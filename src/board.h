#pragma once

#include "position.h"
#include "space_types.h"

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

class board {
public:
  board();

  bool place_move(position *, space_types);
  space_types get_at_position(position);
  space_types get_at_position(int, int);


private:
  static constexpr space_types default_board_state[BOARD_WIDTH][BOARD_HEIGHT] =
    {
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, // row 0
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, WHITE, BLACK, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, BLACK, WHITE, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}, // row 7
    };

  space_types board_array[BOARD_WIDTH][BOARD_HEIGHT];
  void load_default_board();
};
