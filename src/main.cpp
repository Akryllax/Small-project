#include "AllegroManager.h"
#include "Button.h"
#include "Configuration.h"
#include "Core.h"
#include "DebugRenderer.h"
#include "InputLayer.h"
#include "LocationLayer.h"
#include "Logger.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "Random.h"
#include "RendererLayer.h"
#include "Screen.h"
#include "TestShip.h"
#include "UIInputController.h"
#include "box2d/b2_math.h"
#include "events.h"
#include "spdlog/spdlog.h"
#include "timer.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <chrono>
#include <cmath>
#include <memory>

std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<long, std::ratio<1, 1000000000>>>
    applicationEpoch;
bool quit = false;

std::shared_ptr<Akr::TestShip> testShip;
std::shared_ptr<Akr::UI::Button> resetShipDbgButton;
std::shared_ptr<Akr::UI::Button> addRandomImpulseShipDbgButton;

inline int _preAllegroInit(Akr::Core& coreInstance) {
  Akr::Configuration::load();
  Akr::Logger::init("core.log");

  coreInstance.AddDataLayer<Akr::InputLayer>();
  coreInstance.AddDataLayer<Akr::NamedLayer>();
  coreInstance.AddDataLayer<Akr::LocationLayer>();
  coreInstance.AddDataLayer<Akr::RendererLayer>();
  coreInstance.AddDataLayer<Akr::PhysicsLayer>();

  Akr::Core::GetDataLayer<Akr::InputLayer>()->AddController(std::make_shared<Akr::Input::UIInputControler>());

  return 0;
}

void _allegroStableTick(Akr::Core& coreInstance, std::chrono::milliseconds const delta) {
  spdlog::trace("Frame {}", coreInstance.GetFrameCount());

  coreInstance.Tick(delta);
}

void handleFrame(Akr::Core& coreInstance) {
  ALLEGRO_EVENT event;
  al_wait_for_event(Akr::Init::AllegroManager::mainQueue, &event);

  auto currentTime = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds deltaTick =
      std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - applicationEpoch);

  if (event.type == ALLEGRO_EVENT_TIMER) {
    // Update the applicationEpoch to the time of the last frame
    applicationEpoch = currentTime;
    _allegroStableTick(coreInstance, deltaTick);
  } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    // Handle display close event
    quit = true;
  }
}

void cleanupAllegro() {
  al_destroy_font(Akr::Init::AllegroManager::mainFont);
  al_destroy_event_queue(Akr::Init::AllegroManager::mainQueue);
  al_destroy_display(Akr::Init::AllegroManager::systemDisplay);
}

void initializeAllegro() {
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

  // Create the display.
  Akr::Init::AllegroManager::systemDisplay = al_create_display(1920, 1080);
  if (!Akr::Init::AllegroManager::systemDisplay) {
    spdlog::error("Failed to create Allegro display.");
    exit(-1);
  }
  Akr::Screen::RegisterDisplay(Akr::Init::AllegroManager::systemDisplay);

  // Load a font.
  Akr::Init::AllegroManager::mainFont = al_load_ttf_font("/usr/local/share/fonts/i/InputMono_Regular.ttf", 12, 0);
  if (!Akr::Init::AllegroManager::mainFont) {
    spdlog::error("Failed to load font.");
    exit(-1);
  }

  // Create an event queue and a timer.
  Akr::Init::AllegroManager::mainQueue = al_create_event_queue();
  if (!Akr::Init::AllegroManager::mainQueue) {
    spdlog::error("Failed to create event queue.");
    exit(-1);
  }

  auto mainTimer = al_create_timer(1.0 / Akr::Init::AllegroManager::DEFAULT_FPS);
  spdlog::trace("[main] Setting FPS to {}", Akr::Init::AllegroManager::DEFAULT_FPS);
  al_register_event_source(Akr::Init::AllegroManager::mainQueue, al_get_timer_event_source(mainTimer));
  al_start_timer(mainTimer);

  al_register_event_source(Akr::Init::AllegroManager::mainQueue, al_get_display_event_source(Akr::Init::AllegroManager::systemDisplay));

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->GetDebugRenderer().Initialize();

  // Initialize test ship
  testShip = std::make_shared<Akr::TestShip>("a");
  testShip->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  testShip->GetBody()->SetAngularVelocity(std::cos(5 * M_PI / 180.0f));
  testShip->GetBody()->SetLinearVelocity(b2Vec2(20, 20));

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(testShip);

  // Initialize button
  // int x, int y, int width, int height,
  resetShipDbgButton = std::make_shared<Akr::UI::Button>(0, 400, 200, 40, "Reset ship");
  resetShipDbgButton->SetOnClick([&]() {
    spdlog::trace("Reseting ship position!");
    testShip->GetBody()->SetTransform(b2Vec2(200, 200), 0);
  });

  addRandomImpulseShipDbgButton = std::make_shared<Akr::UI::Button>(0, 450, 200, 40, "Add random impulse");
  addRandomImpulseShipDbgButton->SetOnClick([&]() {
    // Generate random impulse values in the range of -80 to 80
    float impulseX = Akr::Math::Utils::getRandomInRange(-120, 120);
    float impulseY = Akr::Math::Utils::getRandomInRange(-120, 120);

    spdlog::trace("Adding impulse: (dX: {}, dY: {})", impulseX, impulseY);

    // Apply the random impulse to the ship's body
    testShip->GetBody()->SetLinearVelocity(b2Vec2(impulseX, impulseY));
  });

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(resetShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListener(resetShipDbgButton);

  Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderable(addRandomImpulseShipDbgButton);
  Akr::Core::GetDataLayer<Akr::InputLayer>()->RegisterRawInputListener(addRandomImpulseShipDbgButton);
}

int _allegro_main(Akr::Core& coreInstance) {
  initializeAllegro();

  applicationEpoch = std::chrono::high_resolution_clock::now();
  quit = false;

  spdlog::trace("[main] Entering main.cpp loop", Akr::Init::AllegroManager::DEFAULT_FPS);
  while (!quit) {
    handleFrame(coreInstance);
  }

  cleanupAllegro();

  return 0;
}

int main(int argc, char** argv) {
  auto& coreInstance = Akr::Core::GetInstance();

  _preAllegroInit(coreInstance);
  _allegro_main(coreInstance);

  return 0;
}
