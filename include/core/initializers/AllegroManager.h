#pragma once

#include "Configuration.h"
#include "Core.h"
#include "InputLayer.h"
#include "LocationLayer.h"
#include "Logger.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "RendererLayer.h"
#include "Screen.h"
#include "UIInputController.h"
#include "allegro_font.h"
#include "display.h"
#include "events.h"
#include "timer.h"

namespace Akr::Init {

struct AllegroManager {
public:
  // static int Initialize(Akr::Core& coreInstance) {
  //   // void initializeAllegro(ALLEGRO_DISPLAY * &display, ALLEGRO_EVENT_QUEUE * &event_queue, ALLEGRO_FONT * &font) {
  //   // Initialize Allegro.
  //   if (!al_init()) {
  //     spdlog::error("Failed to initialize Allegro.");
  //     exit(-1);
  //   }

  //   // Initialize the font add-on.
  //   al_init_font_addon();
  //   al_init_ttf_addon();
  //   al_init_primitives_addon();
  //   al_init_image_addon();

  //   // Initialize the event addon for keyboard and mouse input.
  //   if (!al_install_keyboard()) {
  //     // Handle keyboard initialization failure.
  //     fprintf(stderr, "Failed to initialize keyboard addon!\n");
  //     al_uninstall_system();
  //     exit(-1);
  //   }

  //   if (!al_install_mouse()) {
  //     // Handle mouse initialization failure.
  //     fprintf(stderr, "Failed to initialize mouse addon!\n");
  //     al_uninstall_keyboard();
  //     al_uninstall_system();
  //     exit(-1);
  //   }

  //   // Create the display.
  //   auto display = al_create_display(800, 600);
  //   if (!display) {
  //     spdlog::error("Failed to create Allegro display.");
  //     exit(-1);
  //   }
  //   Akr::Screen::RegisterDisplay(display);

  //   // Load a font.
  //   auto font = al_load_ttf_font("/usr/local/share/fonts/i/InputMono_Regular.ttf", 36, 0);
  //   if (!font) {
  //     spdlog::error("Failed to load font.");
  //     exit(-1);
  //   }

  //   // Create an event queue and a timer.
  //   auto event_queue = al_create_event_queue();
  //   if (!event_queue) {
  //     spdlog::error("Failed to create event queue.");
  //     exit(-1);
  //   }

  //   auto mainTimer = al_create_timer(1.0 / FPS);
  //   spdlog::trace("[main] Setting FPS to {}", FPS);
  //   al_register_event_source(event_queue, al_get_timer_event_source(mainTimer));
  //   al_start_timer(mainTimer);

  //   al_register_event_source(event_queue, al_get_display_event_source(display));

  //   Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetCoreRenderer().Initialize();
  //   Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetDebugRenderer().Initialize();

  //   //   // Initialize test ship
  //   //   testShip = std::make_shared<Akr::TestShip>("a");
  //   //   testShip->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  //   //   testShip->GetBody()->SetAngularVelocity(std::cos(5 * M_PI / 180.0f));
  //   //   testShip->GetBody()->SetLinearVelocity(b2Vec2(20, 20));

  //   //   Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(testShip);

  //   //   // Initialize button
  //   //   // int x, int y, int width, int height,
  //   //   resetShipDbgButton = std::make_shared<Akr::UI::Button>(0, 400, 200, 40, "Reset ship");
  //   //   resetShipDbgButton->SetOnClick([&]() {
  //   //     spdlog::trace("Reseting ship position!");
  //   //     testShip->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  //   //   });

  //   //   addRandomImpulseShipDbgButton = std::make_shared<Akr::UI::Button>(0, 450, 200, 40, "Add random impulse");
  //   //   addRandomImpulseShipDbgButton->SetOnClick([&]() {
  //   //     // Generate random impulse values in the range of -80 to 80
  //   //     float impulseX = Akr::Math::Utils::getRandomInRange(-120, 120);
  //   //     float impulseY = Akr::Math::Utils::getRandomInRange(-120, 120);

  //   //     spdlog::trace("Adding impulse: (dX: {}, dY: {})", impulseX, impulseY);

  //   //     // Apply the random impulse to the ship's body
  //   //     testShip->GetBody()->SetLinearVelocity(b2Vec2(impulseX, impulseY));
  //   //   });

  //   //   Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(resetShipDbgButton);
  //   //   Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListener(resetShipDbgButton);

  //   //   Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(addRandomImpulseShipDbgButton);
  //   //   Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListener(addRandomImpulseShipDbgButton);
  //   return 0;
  // };

  // static int CleanUp(Akr::Core& coreInstance) { return 0; };
  static constexpr uint DEFAULT_FPS = 60;

  inline static ALLEGRO_EVENT_QUEUE* mainQueue = nullptr;
  inline static ALLEGRO_DISPLAY* systemDisplay = nullptr;
  inline static ALLEGRO_DISPLAY* internalBuffer = nullptr;
  inline static ALLEGRO_FONT* mainFont = nullptr;
};
}  // namespace Akr::Init