#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

struct display_state {
    ALLEGRO_DISPLAY *display;
    int screen_width;
    int screen_height;
};
