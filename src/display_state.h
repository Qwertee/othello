#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

typedef struct {
  ALLEGRO_DISPLAY *display;
  int screen_width, screen_height;
} display_state;
