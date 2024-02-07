#include "AllegroManager.h"
#include "CoreManager.h"

int main(int argc, char** argv) {
  Akr::CoreManager::Initialize();
  Akr::AllegroManager::Initialize();
  Akr::AllegroManager::Run();

  Akr::AllegroManager::Cleanup();
  Akr::CoreManager::Cleanup();

  return 0;
}
