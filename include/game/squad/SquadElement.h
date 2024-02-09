#pragma once

namespace Akr::Game::Squad {

class SquadElement {
public:
  SquadElement() = default;
  virtual ~SquadElement() = default;

private:
  SquadElement(SquadElement const&) = delete;
};
};  // namespace Akr::Game::Squad