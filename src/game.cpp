#include "game.h"
#include <iostream>
#include <math.h>

game::game(display_state *s) {
  brd = board();
  current_player = BLACK;
  this->dstate = s;
}

void game::draw(display_state *state) {

  // boarder of one tile around the ones that are drawn for a nice boarder
  // effect
  int display_grid_width = BOARD_WIDTH + 2;
  int display_grid_height = BOARD_HEIGHT + 2;

  // pixel width and height of an individual tile that will be drawn to the
  // screen
  float tile_width = state->screen_width / display_grid_width;
  float tile_height = state->screen_height / display_grid_height;

  for (int x = 0; x < BOARD_WIDTH; x++)
    for (int y = 0; y < BOARD_HEIGHT; y++) {

      // upper left and bottom right coordinates for the current tile
      float tile_x1 = tile_width + (x * tile_width);
      float tile_y1 = tile_height + (y * tile_height);
      float tile_x2 = tile_x1 + tile_width;
      float tile_y2 = tile_y1 + tile_height;

      // need to draw the background tile for every square
      al_draw_filled_rectangle(tile_x1, tile_y1, tile_x2, tile_y2,
                               al_map_rgb(0, 255, 0));

      // switch y1 and y2 to prevent boarder from being drawn 'inside out'
      al_draw_rectangle(tile_x1, tile_y1, tile_x2, tile_y2, al_map_rgb(0, 0, 0), 10);

      // check to see if a piece needs to be drawn
      switch (brd.get_at_position(x, y)) {
      case BLACK:
        al_draw_filled_ellipse((tile_x1 + tile_x2) / 2, (tile_y1 + tile_y2) / 2,
                               tile_width / 3, tile_height / 3,
                               al_map_rgb(0, 0, 0));
        break;

      case WHITE:
        al_draw_filled_ellipse((tile_x1 + tile_x2) / 2, (tile_y1 + tile_y2) / 2,
                               tile_width / 3, tile_height / 3,
                               al_map_rgb(255, 255, 255));
        break;

      default:
        break;
      }
    }
}

void game::process_click(int x, int y) {
  // need to determine which tile was click on.
  position *tile = get_tile_from_screen_pos(x, y);
  if (tile == nullptr) {
    return;
  }
  // std::cout << "click point: " << tile->x << ", " << tile->y << std::endl;

  // clicked a tile, process it!
  process_move(tile);

  // done with tile for this click
  delete tile;
}

void game::process_move(position *pos) {
  // check if the tile is empty in the first place
  if (brd.get_at_position(*pos) != EMPTY) {
    std::cout << "clicked tile not empty" << std::endl;
    return;
  }

  // check if the move is valid
  if (!is_move_valid(pos)) {
    std::cout << "clicked tile is not a valid move" << std::endl;
    return;
  }

  brd.place_move(pos, current_player);

  current_player = current_player == WHITE ? BLACK : WHITE;

}

bool game::is_move_valid_helper(position *pos, int delta_x, int delta_y) {
  const space_types other_player = current_player == WHITE ? BLACK : WHITE;

  int start_x = pos->x + delta_x;
  int start_y = pos->y + delta_y;

  if (start_x < 0 || start_x >= BOARD_WIDTH) {
    return false;
  }
  if (start_y < 0 || start_y >= BOARD_HEIGHT) {
    return false;
  }

  // if (delta_x == 0) delta_x = BOARD_WIDTH + 1;
  // if (delta_y == 0) delta_y = BOARD_HEIGHT + 1;

  bool matching = false;
  // need one loop
  int y = start_y; // initialize second loop variable
  for (int x = start_x;
       x < BOARD_WIDTH && x >= 0 && y < BOARD_HEIGHT && y >= 0;
       x += delta_x) {

    space_types iterator_tile = brd.get_at_position(x, y);

    if (iterator_tile == current_player && !matching) {
      // ERROR - placed tile has a tile with matching color directly adjacent to it!
      return false;
    } else if (iterator_tile == current_player && matching) {
      // found the end of a chain - MATCH!
      return true;
    } else if (iterator_tile == other_player) {
      matching = true;
    } else if (iterator_tile == EMPTY) {
      return false;
    } else {
      return false;
    }

    // increment second loop variable
    y += delta_y;
  }
  return false;
}

bool game::is_move_valid(position *pos) {
  // do some sick shit here...
  // space_types other_player = current_player == WHITE ? BLACK : WHITE;

  // need to check 8 directoions to determine whether the move is valid or not.
  // TODO: stop after finding one move (since this is just to check whether it is valid or not)?

  return
    is_move_valid_helper(pos, 0, 1)   || // up
    is_move_valid_helper(pos, 1, 1)   || // up right
    is_move_valid_helper(pos, 1, 0)   || // right
    is_move_valid_helper(pos, 1, -1)  || // down right
    is_move_valid_helper(pos, 0, -1)  || // down
    is_move_valid_helper(pos, -1, -1) || // down left
    is_move_valid_helper(pos, -1, 0)  || // left
    is_move_valid_helper(pos, -1, 1);    // upper left

}

position *game::get_tile_from_screen_pos(int x, int y) {
  position *pos = new position;

  int tilesX = dstate->screen_width / (BOARD_WIDTH + 2);
  int tilesY = dstate->screen_height / (BOARD_HEIGHT + 2);

  pos->x = static_cast<int>(floor((float)x / tilesX)) - 1;
  pos->y = static_cast<int>(floor((float)y / tilesY)) - 1;

  // validate the calculations and return null if invalid coords are returned
  if ((pos->x < 0 || pos->x >= BOARD_WIDTH) ||
      (pos->y < 0 || pos->y >= BOARD_HEIGHT)) {
    return nullptr;
  }

  return pos;
}
