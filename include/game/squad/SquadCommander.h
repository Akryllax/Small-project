#pragma once

namespace Akr::Game::Squad {

class SquadCommander {
public:
  SquadCommander() = default;
  virtual ~SquadCommander() = default;

private:
  SquadCommander(SquadCommander const&) = delete;
  SquadCommander& operator=(SquadCommander const&) = delete;
};
};  // namespace Akr::Game::Squad