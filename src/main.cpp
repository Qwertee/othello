#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

const int FPS = 60;

int main () {
  ALLEGRO_DISPLAY *display = nullptr;
  ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
  ALLEGRO_TIMER *timer = nullptr;
  bool running = true;
  bool redraw = false;

  if (!al_init()) {
    std::cout << "ERROR: couldn't initialize allegro..." << std::endl;
    exit(-1);
  }

  timer = al_create_timer(1.0 / FPS);
  if (!timer) {
    std::cout << "ERROR: couldn't initialize timer..." << std::endl;
    exit(-1);
  }

  display = al_create_display(800, 800);
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

  al_clear_to_color(al_map_rgb(0, 0, 0));

  al_flip_display();
  al_start_timer(timer);

  // start the main loop
  while(running) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
      redraw = true;
    }
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      running = false;
    }

    if (redraw && al_is_event_queue_empty(event_queue)) {
      redraw = false;
      al_clear_to_color(al_map_rgb(0, 0, 0));
      al_flip_display();
    }
  }

  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_timer(timer);

  return 0;
}
