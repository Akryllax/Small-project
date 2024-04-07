#pragma once

namespace Akr::Game::Squad {

class SquadCommand {
public:
  SquadCommand() = default;
  virtual ~SquadCommand() = default;

private:
  SquadCommand(SquadCommand const&) = delete;
  SquadCommand& operator=(SquadCommand const&) = delete;
};
};  // namespace Akr::Game::Squad