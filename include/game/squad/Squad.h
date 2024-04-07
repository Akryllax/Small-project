#pragma once

namespace Akr::Game::Squad {

class Squad {
public:
  Squad() = default;
  virtual ~Squad() = default;

private:
  Squad(Squad const&) = delete;
  Squad& operator=(Squad const&) = delete;
};
};  // namespace Akr::Game::Squad