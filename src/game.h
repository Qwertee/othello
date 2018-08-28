#pragma once
#include "board.h"
#include "display_state.h"

class game {
public:
  game();
  void draw(display_state *);
  void process_click(int, int);

private:
  struct position {
    int x;
    int y;
  };

  struct position get_tile_from_screen_pos(int x, int y);

  board brd;
};
