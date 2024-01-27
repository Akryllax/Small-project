#pragma once

#include "RenderCommand.h"
#include <memory>
#include <queue>
namespace Akr::Renderer {

// This render command handles multiple render commands into one package
class CompositeRenderComand : public RenderCommand {
public:
  void execute() override {
    while (!commands.empty()) {
      commands.front()->execute();
      commands.pop();
    }
  };

  void QueueCommand(std::shared_ptr<RenderCommand> renderCommand) { commands.push(renderCommand); }

  // Queue multiple render commands from a std::queue
  void QueueCommands(std::queue<std::shared_ptr<RenderCommand>>& renderCommands) {
    while (!renderCommands.empty()) {
      commands.push(renderCommands.front()); // Add the command to the queue
      renderCommands.pop();                  // Remove the command from the original queue
    }
  }

private:
  std::queue<std::shared_ptr<RenderCommand>> commands;
};
} // namespace Akr::Renderer