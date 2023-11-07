#include "Core.h"
#include "LocationLayer.h"
#include "NamedLayer.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <thread>

inline int _initCore(Akr::Core& coreInstance) {
  coreInstance.AddDataLayer(std::make_shared<Akr::NamedLayer>());
  coreInstance.AddDataLayer(std::make_shared<Akr::LocationLayer>());
  coreInstance.AddDataLayer(std::make_shared<Akr::NamedLayer>());

  return 0;
}

inline int _coreLoop(Akr::Core& coreInstance,
                     const std::chrono::milliseconds delta) {
  coreInstance.Tick(delta);

  return 0;
}

int _allegro_main() {
  ALLEGRO_DISPLAY* display = nullptr;
  ALLEGRO_EVENT_QUEUE* event_queue = nullptr;
  ALLEGRO_FONT* font = nullptr;

  // Initialize Allegro.
  if (!al_init()) {
    return -1;
  }

  // Initialize the font add-on.
  al_init_font_addon();
  al_init_ttf_addon();

  // Create the display.
  display = al_create_display(800, 600);
  if (!display) {
    return -1;
  }

  // Load a font (replace "your_font_file.ttf" with the path to a TTF font
  // file).
  font = al_load_ttf_font("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf", 36, 0);
  if (!font) {
    return -1;
  }

  // Create an event queue.
  event_queue = al_create_event_queue();
  if (!event_queue) {
    return -1;
  }

  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_clear_to_color(al_map_rgb(0, 0, 0));

  // Render "Hello World!" at coordinates (100, 200) in white color.
  al_draw_text(font, al_map_rgb(255, 255, 255), 100, 200, ALLEGRO_ALIGN_LEFT,
               "Hello World!");

  al_flip_display();

  bool quit = false;
  while (!quit) {
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      quit = true;
    }
  }

  al_destroy_font(font);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);

  return 0;
}

int main(int argc, char** argv) {
  _allegro_main();

  auto coreInstance = Akr::Core::GetInstance();
  _initCore(coreInstance);

  auto applicationEpoch = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds targetFrameTime(1000 / 30);  // 30 FPS

  while (true) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds lastTick =
        std::chrono::duration_cast<std::chrono::milliseconds>(currentTime -
                                                              applicationEpoch);

    // Call the core loop only when it's time for the next frame
    if (lastTick >= targetFrameTime) {
      _coreLoop(coreInstance, lastTick);

      // Print frame count and time
      auto now = std::chrono::system_clock::now();
      auto now_time = std::chrono::system_clock::to_time_t(now);
      auto timeinfo = std::localtime(&now_time);
      std::cout << "[" << std::put_time(timeinfo, "%T")
                << " | FrameNumber: " << coreInstance.GetFrameCount() << "]"
                << std::endl;

      // Update the applicationEpoch to the time of the last frame
      applicationEpoch = currentTime;
    }

    // Sleep for the remaining time until the next frame
    std::this_thread::sleep_for(targetFrameTime - lastTick);
  }

  std::cout << "Hello, dataGen!" << std::endl;
  return 0;
}
