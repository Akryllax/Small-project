#include "CoreManager.h"
#include "AllegroManager.h"
#include "FrameHandler.h"
#include "Core.h"

int main(int argc, char** argv) {
    Akr::Core& coreInstance = Akr::Core::GetInstance();

    // Initialize core components
    Akr::Init::CoreManager::Initialize(coreInstance);

    Akr::Init::AllegroManager::Initialize(coreInstance);

    // Run the main loop
    Akr::Init::FrameManager::RunMainLoop(coreInstance);

    // Clean up Allegro resources
    Akr::Init::AllegroManager::Cleanup(coreInstance);

    return 0;
}
