#include "Button.h"
#include "Core.h"
#include "LocationLayer.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "TestShip.h"
#include "timer.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>

float const FPS = 60;
std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>>
    applicationEpoch;
bool quit = false;

Akr::TestShip* testShip;

inline int _initCore(Akr::Core& coreInstance) {
  coreInstance.AddDataLayer<Akr::NamedLayer>();
  coreInstance.AddDataLayer<Akr::LocationLayer>();
  coreInstance.AddDataLayer<Akr::NamedLayer>();
  coreInstance.AddDataLayer<Akr::PhysicsLayer>();

  return 0;
}

void _allegroStableTick(Akr::Core& coreInstance, std::chrono::milliseconds const delta) {
  coreInstance.Tick(delta);

  // Print frame count and time
  auto now = std::chrono::system_clock::now();
  auto now_time = std::chrono::system_clock::to_time_t(now);
  auto timeinfo = std::localtime(&now_time);

  std::cout << "Frame " << coreInstance.GetFrameCount() << ":\t[" << std::put_time(timeinfo, "%T") << "] - "
            << std::endl;

  al_clear_to_color(al_map_rgb(0, 0, 0));

  if(testShip) testShip->Render();

  al_flip_display();
}

void handleFrame(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue, Akr::Core& coreInstance) {
  ALLEGRO_EVENT event;
  al_wait_for_event(event_queue, &event);

  auto currentTime = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds lastTick =
      std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - applicationEpoch);

  if (event.type == ALLEGRO_EVENT_TIMER) {
    // Update the applicationEpoch to the time of the last frame
    applicationEpoch = currentTime;
    _allegroStableTick(coreInstance, lastTick);
  } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    // Handle display close event
    quit = true;
  }
}

void cleanupAllegro(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT_QUEUE* event_queue, ALLEGRO_FONT* font) {
  al_destroy_font(font);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
}

void initializeAllegro(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& event_queue, ALLEGRO_FONT*& font) {
  // Initialize Allegro.
  if (!al_init()) {
    std::cerr << "Failed to initialize Allegro." << std::endl;
    exit(-1);
  }

  // Initialize the font add-on.
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_primitives_addon();
  al_init_image_addon();

  // Create the display.
  display = al_create_display(800, 600);
  if (!display) {
    std::cerr << "Failed to create Allegro display." << std::endl;
    exit(-1);
  }

  // Load a font.
  font = al_load_ttf_font("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf", 36, 0);
  if (!font) {
    std::cerr << "Failed to load font." << std::endl;
    exit(-1);
  }

  // Create an event queue and a timer.
  event_queue = al_create_event_queue();
  if (!event_queue) {
    std::cerr << "Failed to create event queue." << std::endl;
    exit(-1);
  }

  auto mainTimer = al_create_timer(1.0 / FPS);
  al_register_event_source(event_queue, al_get_timer_event_source(mainTimer));
  al_start_timer(mainTimer);

  al_register_event_source(event_queue, al_get_display_event_source(display));

  testShip = new Akr::TestShip("a");
}

int _allegro_main(Akr::Core& coreInstance) {
  ALLEGRO_DISPLAY* display = nullptr;
  ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
  ALLEGRO_FONT* font = nullptr;

  initializeAllegro(display, event_queue, font);

  applicationEpoch = std::chrono::high_resolution_clock::now();
  quit = false;

  while (!quit) {
    handleFrame(display, event_queue, coreInstance);
  }

  cleanupAllegro(display, event_queue, font);

  return 0;
}

int main(int argc, char** argv) {
  auto coreInstance = Akr::Core::GetInstance();
  _initCore(coreInstance);
  _allegro_main(coreInstance);

  return 0;
}
