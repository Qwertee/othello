#include "colors.h"

namespace colors {
    // TODO: whyyyyyyy do I have to define them like this??
    ALLEGRO_COLOR BLACK = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR WHITE = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR GREEN = al_map_rgb(0, 0, 0);

    void load_colors() {
        BLACK = al_map_rgb(0, 0, 0);
        WHITE = al_map_rgb(255, 255, 255);
        GREEN = al_map_rgb(0, 255, 0);
    }
} // namespace colors
