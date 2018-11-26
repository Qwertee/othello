#include "display_state.h"
#include "game.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

const int FPS = 60;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

int main() {
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    bool running = true;
    bool redraw = false;
    game *g;

    display_state *dstate = new display_state;

    if (!al_init()) {
        std::cout << "ERROR: couldn't initialize allegro..." << std::endl;
        exit(-1);
    }

    if (!al_install_mouse()) {
        std::cout << "ERROR: failed to initialize mouse..." << std::endl;
        exit(-1);
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        std::cout << "ERROR: couldn't initialize timer..." << std::endl;
        exit(-1);
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        std::cout << "ERROR: couldn't initialize display..." << std::endl;
        al_destroy_timer(timer);
        exit(-1);
    }

    event_queue = al_create_event_queue();

    if (!event_queue) {
        std::cout << "ERROR: couldn't initialize event queue..." << std::endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        exit(-1);
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(al_map_rgb(0, 0, 0));

    al_flip_display();
    al_start_timer(timer);

    // set up the display state
    dstate->screen_width = SCREEN_WIDTH;
    dstate->screen_height = SCREEN_HEIGHT;
    dstate->display = display;

    g = new game(dstate);

    // start the main loop
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }

        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
        }

        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            g->process_click(event.mouse.x, event.mouse.y);
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(117, 199, 255));

            g->draw(dstate);

            al_flip_display();
        }
    }

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);

    return 0;
}
