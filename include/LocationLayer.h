#include "DataLayer.h"
#include "ITickable.h"
#include "Location.h"
#include <iostream>
#include <unordered_map>
#include <vector>

namespace Akr {
class LocationLayer : public DataLayer {
 protected:
  std::unordered_map<std::string, Location> locationVector;
  void Tick(const std::chrono::milliseconds delta) override {
    std::cout << "LocationLayer" << "::Tick()" << std::endl;
  }
};
}  // namespace Akr