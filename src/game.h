#pragma once

#include "board.h"
#include "display_state.h"
#include "position.h"

class game {
  private:
    position *get_tile_from_screen_pos(int x, int y);

    board brd;

    display_state *dstate;

    space_types current_player;

    bool is_move_valid_helper(position *, int, int);
    bool is_move_valid(position *);

  public:
    game(display_state *s);
    void draw(display_state *);
    void process_click(int, int);
    void process_move(position *);
};
