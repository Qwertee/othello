#include "game.h"
#include <iostream>
#include <list>
#include <math.h>
#include "colors.h"

game::game(display_state *s) {
    brd = board();
    current_player = BLACK;
    this->dstate = s;
}

void game::draw_piece(float x, float y, float radius, ALLEGRO_COLOR color) {
    al_draw_filled_ellipse(x, y, radius, radius, color);
}

void game::draw(display_state *state) {

    // boarder of one tile around the ones that are drawn for a nice boarder effect
    int display_grid_width = BOARD_WIDTH + 2;
    int display_grid_height = BOARD_HEIGHT + 2;

    // pixel width and height of an individual tile that will be drawn to the screen
    float tile_width = state->screen_width / display_grid_width;
    float tile_height = state->screen_height / display_grid_height;

    float piece_radius = std::min(tile_width, tile_height) / 3;

    // draw the current player's color to the screen so players can tell who is going
    ALLEGRO_COLOR player_color =
        current_player == WHITE ? colors::WHITE : colors::BLACK;

    draw_piece(tile_width / 2, tile_height / 2, piece_radius, player_color);

    for (int x = 0; x < BOARD_WIDTH; x++)
        for (int y = 0; y < BOARD_HEIGHT; y++) {

            // upper left and bottom right coordinates for the current tile
            float tile_x1 = tile_width + (x * tile_width);
            float tile_y1 = tile_height + (y * tile_height);
            float tile_x2 = tile_x1 + tile_width;
            float tile_y2 = tile_y1 + tile_height;

            float tile_center_x = (tile_x1 + tile_x2) / 2;
            float tile_center_y = (tile_y1 + tile_y2) / 2;

            // need to draw the background tile for every square
            al_draw_filled_rectangle(tile_x1, tile_y1, tile_x2, tile_y2,
                                     al_map_rgb(0, 255, 0));

            // switch y1 and y2 to prevent boarder from being drawn 'inside out'
            al_draw_rectangle(tile_x1, tile_y1, tile_x2, tile_y2, colors::BLACK, 10);

            // check to see if a piece needs to be drawn
            switch (brd.get_at_position(x, y)) {
            case BLACK:
                draw_piece(tile_center_x, tile_center_y, piece_radius, colors::BLACK);
                break;

            case WHITE:
                draw_piece(tile_center_x, tile_center_y, piece_radius, colors::WHITE);

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

    std::list<position> to_flip = std::list<position>();

    bool matching = false;
    // need one loop
    int y = start_y; // initialize second loop variable
    for (int x = start_x; x < BOARD_WIDTH && x >= 0 && y < BOARD_HEIGHT && y >= 0;
         x += delta_x) {

        space_types iterator_tile = brd.get_at_position(x, y);

        if (iterator_tile == current_player && !matching) {
            // ERROR - placed tile has a tile with matching color directly
            // adjacent to it!
            return false;
        }

        else if (iterator_tile == current_player && matching) {
            // found the end of a chain - MATCH!
            // flip tiles that were found while matching.
            for (position p : to_flip) {
                brd.place_move(&p, current_player);
            }
            return true;
        }

        else if (iterator_tile == other_player) {
            // currently looking at other color, keep searching...
            matching = true;
            position p;
            p.x = x;
            p.y = y;
            to_flip.push_front(p);
        }

        else if (iterator_tile == EMPTY) {
            // empty tile - BAD!
            return false;
        }

        else {
            // everything else that may possibly happen can't get _good_, so
            // fail
            return false;
        }

        // increment second loop variable
        y += delta_y;
    }
    return false;
}

// returns false if given position is an invalid move for the current player.
// returns true if the move is possible and flips the appropriate tiles to the opposing
// color.
bool game::is_move_valid(position *pos) {
    // keep backup incase move is invalid
    board board_backup = board(brd);

    // need to check 8 directoions to determine whether the move is valid or not.
    // has to be written like this to avoid short-circuit evaluation.
    // (we want ALL conditions to evaluate, chained ORs would stop evaluation on the
    // first TRUE result found and may not flip all necessary tiles)

    // there has GOT to be a better way to do this...
    bool u = is_move_valid_helper(pos, 0, 1);    // up
    bool ur = is_move_valid_helper(pos, 1, 1);   // up right
    bool r = is_move_valid_helper(pos, 1, 0);    // right
    bool dr = is_move_valid_helper(pos, 1, -1);  // down right
    bool d = is_move_valid_helper(pos, 0, -1);   // down
    bool dl = is_move_valid_helper(pos, -1, -1); // down left
    bool l = is_move_valid_helper(pos, -1, 0);   // left
    bool ul = is_move_valid_helper(pos, -1, 1);  // upper left
    bool result = u || ur || r || dr || d || dl || l || ul;

    if (result == false) {
        // don't keep modifications when move is invalid
        brd = board_backup;
    }

    return result;
}

position *game::get_tile_from_screen_pos(int x, int y) {
    position *pos = new position;

    int tilesX = dstate->screen_width / (BOARD_WIDTH + 2);
    int tilesY = dstate->screen_height / (BOARD_HEIGHT + 2);

    pos->x = static_cast<int>(floor((float)x / tilesX)) - 1;
    pos->y = static_cast<int>(floor((float)y / tilesY)) - 1;

    // validate the calculations and return null if invalid coords are returned
    if ((pos->x < 0 || pos->x >= BOARD_WIDTH) || (pos->y < 0 || pos->y >= BOARD_HEIGHT)) {
        return nullptr;
    }

    return pos;
}
