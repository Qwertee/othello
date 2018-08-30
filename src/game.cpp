#include <iostream>
#include <math.h>
#include "game.h"

game::game(display_state * s) {
  brd = board();
  current_player = board::BLACK;
  this->dstate = s;

}

void game::draw(display_state *state) {

  // boarder of one tile around the ones that are drawn for a nice boarder effect
  int display_grid_width = BOARD_WIDTH + 2;
  int display_grid_height = BOARD_HEIGHT + 2;

  // pixel width and height of an individual tile that will be drawn to the screen
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
      al_draw_filled_rectangle(tile_x1, tile_y1, tile_x2, tile_y2, al_map_rgb(0, 255, 0));
      al_draw_rectangle(tile_x1, tile_y1, tile_x2, tile_y2, al_map_rgb(0, 0, 0), 10);

      // check to see if a piece needs to be drawn
      switch (brd.board_array[x][y]) {
      case board::WHITE:
        al_draw_filled_ellipse((tile_x1 + tile_x2) / 2,
                               (tile_y1 + tile_y2) / 2,
                               tile_width / 3,
                               tile_height / 3,
                               al_map_rgb(0, 0, 0));
        break;


      case board::BLACK:
        al_draw_filled_ellipse((tile_x1 + tile_x2) / 2,
                               (tile_y1 + tile_y2) / 2,
                               tile_width / 3,
                               tile_height / 3,
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
  std::cout << "click point: " << tile->x << ", " << tile->y << std::endl;

  // clicked a tile, process it!
  process_move(tile);


  // done with tile for this click
  delete tile;
}

void game::process_move(game::position *tile) {

}

game::position* game::get_tile_from_screen_pos(int x, int y) {
  position *pos = new position;

  int tilesX = dstate->screen_width / (BOARD_WIDTH + 2);
  int tilesY = dstate->screen_height / (BOARD_HEIGHT + 2);

  pos->x = static_cast<int>(floor((float)x / tilesX)) - 1;
  pos->y = BOARD_HEIGHT - static_cast<int>(floor((float)y / tilesY));

  // validate the calculations and return null if invalid coords are returned
  if ((pos->x < 0 || pos->x >= BOARD_WIDTH) ||
      (pos->y < 0 || pos->y >= BOARD_HEIGHT)) {
    return nullptr;
  }

  return pos;
}
