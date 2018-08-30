#pragma once

#include "board.h"
#include "display_state.h"

class game {
private:
  struct position {
    int x;
    int y;
  };

  position* get_tile_from_screen_pos(int x, int y);

  board brd;

  display_state *dstate;

  board::space_types current_player;

public:
  game(display_state *s);
  void draw(display_state *);
  void process_click(int, int);
  void process_move(position*);


};
