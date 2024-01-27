#pragma once

#include "RenderCommand.h"
#include <allegro5/allegro5.h>
#include <memory>
#include <queue>
#include <vector>

namespace Akr::Renderer {
class CoreRenderer {
public:
  CoreRenderer() = default;

  void Initialize() {};

  // Render stages
  void earlyFrameRender() { processCommands(earlyRenderCmds); }

  void mainFrameRender() { processCommands(mainRenderCmds); }

  void lateFrameRender() { processCommands(lateRenderCmds); }

  void render() {
    // Clear screen
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Example clear color: black

    // Render stages
    earlyFrameRender();
    mainFrameRender();
    lateFrameRender();

    // Flip buffer
    al_flip_display();
  }

  // Add command to each queue
  void addEarlyRenderCommand(std::shared_ptr<RenderCommand> const cmd) { earlyRenderCmds.push(cmd); }

  void addMainRenderCommand(std::shared_ptr<RenderCommand> const cmd) { mainRenderCmds.push(cmd); }

  void addLateRenderCommand(std::shared_ptr<RenderCommand> const cmd) { lateRenderCmds.push(cmd); }

  // Define a custom comparator for RenderCommand objects
  struct RenderCommandComparator {
    bool operator()(std::shared_ptr<RenderCommand> const& lhs, std::shared_ptr<RenderCommand> const& rhs) const {
      return lhs->renderPriority > rhs->renderPriority; // Compare renderPriority values
    }
  };

  // Define priority queue type using RenderCommand and the custom comparator
  using PriorityRenderQueue = std::priority_queue<std::shared_ptr<RenderCommand>, std::vector<std::shared_ptr<RenderCommand>>, RenderCommandComparator>;

private:
    CoreRenderer& operator=(CoreRenderer const&) = delete;
    CoreRenderer(CoreRenderer const&) = delete;

    // Process commands in the specified priority queue
    void processCommands(PriorityRenderQueue& commandQueue) {
        while (!commandQueue.empty()) {
            commandQueue.top()->execute();
            commandQueue.pop();
        }
    }

    PriorityRenderQueue earlyRenderCmds;
    PriorityRenderQueue mainRenderCmds;
    PriorityRenderQueue lateRenderCmds;

};
} // namespace Akr::Renderer
