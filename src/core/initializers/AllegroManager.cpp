#include "AllegroManager.h"
#include "Configuration.h"
#include "Core.h"
#include "InputLayer.h"
#include "LocationLayer.h"
#include "Logger.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "Random.h"
#include "RendererLayer.h"
#include "Screen.h"
#include "UIInputController.h"
#include "allegro5/allegro_font.h"
#include "allegro5/bitmap.h"
#include "allegro5/display.h"
#include "allegro5/events.h"
#include "allegro5/timer.h"

namespace Akr {

int AllegroManager::Initialize() {
  AllegroManager::InstallAllegroSystems();
  AllegroManager::CreateDisplay();
  AllegroManager::LoadBasicResources();
  AllegroManager::CreateEventAndTimers();

  return 0;
}

void AllegroManager::EngineTickFrame(std::chrono::milliseconds const& delta) {}

void AllegroManager::EngineStableTick(std::chrono::milliseconds const& delta) {
  spdlog::trace("[AllegroManager] EngineStableTick(), Frame: {}", Akr::Core::GetInstance().GetFrameCount());

  Akr::Core::GetInstance().Tick(delta);
}

void AllegroManager::HandleEngineLoopTick() {
  ALLEGRO_EVENT event;
  al_wait_for_event(AllegroManager::mainQueue, &event);

  auto currentTime = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds deltaTick =
      std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - applicationEpoch);

  if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    // Handle display close event
    quitApplication_ = true;
  } else if (event.type == ALLEGRO_EVENT_TIMER) {
    // Update the applicationEpoch to the time of the last frame

    // Clear the internal render buffer
    al_set_target_bitmap(AllegroManager::internalBuffer);

    applicationEpoch = currentTime;
    EngineStableTick(deltaTick);

    // Upscale and draw the internal render buffer to the display
    al_set_target_backbuffer(AllegroManager::systemDisplay);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    float scaleX = al_get_display_width(AllegroManager::systemDisplay) /
                   (float)al_get_bitmap_width(AllegroManager::internalBuffer);
    float scaleY = al_get_display_height(AllegroManager::systemDisplay) /
                   (float)al_get_bitmap_height(AllegroManager::internalBuffer);
    float scale = fmin(scaleX, scaleY);

    al_draw_scaled_bitmap(AllegroManager::internalBuffer, 0, 0, al_get_bitmap_width(AllegroManager::internalBuffer),
                          al_get_bitmap_height(AllegroManager::internalBuffer),
                          (al_get_display_width(AllegroManager::systemDisplay) -
                           scale * al_get_bitmap_width(AllegroManager::internalBuffer)) /
                              2,
                          (al_get_display_height(AllegroManager::systemDisplay) -
                           scale * al_get_bitmap_height(AllegroManager::internalBuffer)) /
                              2,
                          scale * al_get_bitmap_width(AllegroManager::internalBuffer),
                          scale * al_get_bitmap_height(AllegroManager::internalBuffer), 0);

    al_flip_display();
  }
}

void AllegroManager::MainLoop() {
  while (!quitApplication_) {
    HandleEngineLoopTick();
  }
}

int AllegroManager::Run() {
  applicationEpoch = std::chrono::high_resolution_clock::now();
  quitApplication_ = false;

  spdlog::trace("[AllegroManager] Run() triggered");

  LoadDevScene();
  MainLoop();

  return 0;
}

int AllegroManager::Cleanup() {
  al_destroy_font(AllegroManager::mainFont);
  al_destroy_event_queue(AllegroManager::mainQueue);
  al_destroy_display(AllegroManager::systemDisplay);
  al_destroy_bitmap(AllegroManager::internalBuffer);
  return 0;
}

void AllegroManager::InstallAllegroSystems() {
  // Initialize Allegro.
  if (!al_init()) {
    spdlog::error("Failed to initialize Allegro.");
    exit(-1);
  }

  // Initialize the font add-on.
  al_init_font_addon();
  al_init_ttf_addon();
  al_init_primitives_addon();
  al_init_image_addon();

  // Initialize the event addon for keyboard and mouse input.
  if (!al_install_keyboard()) {
    // Handle keyboard initialization failure.
    fprintf(stderr, "Failed to initialize keyboard addon!\n");
    al_uninstall_system();
    exit(-1);
  }

  if (!al_install_mouse()) {
    // Handle mouse initialization failure.
    fprintf(stderr, "Failed to initialize mouse addon!\n");
    al_uninstall_keyboard();
    al_uninstall_system();
    exit(-1);
  }
}

void AllegroManager::CreateDisplay() {
  // Create main system the display.
  AllegroManager::systemDisplay = al_create_display(1920, 1080);
  if (!Akr::AllegroManager::systemDisplay) {
    spdlog::error("Failed to create Allegro display.");
    exit(-1);
  }
  Akr::Screen::RegisterDisplay(Akr::AllegroManager::systemDisplay);

  // Create internal render buffer.
  Akr::AllegroManager::internalBuffer = al_create_bitmap(1920, 1080);
  if (!Akr::AllegroManager::internalBuffer) {
    spdlog::error("Failed to create internal render buffer");
    exit(-1);
  }
}

void AllegroManager::LoadBasicResources() {
  // Load a font.
  spdlog::info("Loading font: {}",
               Akr::Resource::GetResourceFolderPath().append("FiraMono-Regular.ttf").string().c_str());
  AllegroManager::mainFont =
      al_load_ttf_font(Akr::Resource::GetResourceFolderPath().append("FiraMono-Regular.ttf").string().c_str(), 12, 0);
  if (!AllegroManager::mainFont) {
    spdlog::error("Failed to load font.");
    AllegroManager::mainFont = al_create_builtin_font();
    if (!AllegroManager::mainFont) {
      spdlog::error("[CRITICAL] Couldn't create default font. Exiting...");
      exit(-1);
    }
  }
}

void AllegroManager::CreateEventAndTimers() {
  // Create an event queue and a timer.
  AllegroManager::mainQueue = al_create_event_queue();
  if (!AllegroManager::mainQueue) {
    spdlog::error("Failed to create event queue.");
    exit(-1);
  }

  auto mainTimer = al_create_timer(1.0 / AllegroManager::DEFAULT_FPS);
  spdlog::trace("[main] Setting FPS to {}", AllegroManager::DEFAULT_FPS);
  al_register_event_source(AllegroManager::mainQueue, al_get_timer_event_source(mainTimer));
  al_start_timer(mainTimer);

  al_register_event_source(AllegroManager::mainQueue, al_get_display_event_source(AllegroManager::systemDisplay));
}

void AllegroManager::LoadDevScene() {
  // Initialize test ship
  auto testShip = std::make_shared<Akr::TestShip>("a");
  testShip->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  testShip->GetBody()->SetAngularVelocity(std::cos(5 * ALLEGRO_PI / 180.0f));
  testShip->GetBody()->SetLinearVelocity(b2Vec2(20, 20));

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(testShip);

  // Initialize button
  // int x, int y, int width, int height,
  auto resetShipDbgButton = std::make_shared<Akr::UI::Button>(0, 400, 200, 40, "Reset ship");
  resetShipDbgButton->SetOnClick([&]() {
    spdlog::trace("Reseting ship position!");
    testShip->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  });

  const float impulseMultiplier = 300;

  auto addRandomImpulseShipDbgButton = std::make_shared<Akr::UI::Button>(0, 450, 200, 40, "Add random impulse");
  addRandomImpulseShipDbgButton->SetOnClick([&]() {
    // Generate random impulse values in the range of -80 to 80
    float impulseX = (Akr::Math::Utils::getRandomInRange(-100.0f, 100.0f) / 100.0f) * impulseMultiplier;
    float impulseY = (Akr::Math::Utils::getRandomInRange(-100.0f, 100.0f) / 100.0f) * impulseMultiplier;

    spdlog::trace("Adding impulse: (dX: {}, dY: {})", impulseX, impulseY);

    // Apply the random impulse to the ship's body
    testShip->GetBody()->SetLinearVelocity(b2Vec2(impulseX, impulseY));
  });

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(resetShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListener(resetShipDbgButton);

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(addRandomImpulseShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListener(addRandomImpulseShipDbgButton);
}

}  // namespace Akr
