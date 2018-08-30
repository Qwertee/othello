#pragma once

const int BOARD_WIDTH = 8;
const int BOARD_HEIGHT = 8;

class board {
public:
  board();

  enum space_types
    {
     EMPTY = 0,
     WHITE = 1,
     BLACK = 2
    };

  bool place_move(int, int, space_types);

  space_types board_array[BOARD_WIDTH][BOARD_HEIGHT];

private:
  static constexpr space_types default_board_state[BOARD_WIDTH][BOARD_HEIGHT] =
    {
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, WHITE, BLACK, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, BLACK, WHITE, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
     {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
    };

  void load_default_board();
};
