#pragma once

#include "RenderCommand.h"
#include <allegro5/allegro5.h>
#include <memory>
#include <queue>
#include <vector>

namespace Akr::Renderer {

/**
 * @brief CoreRenderer class for managing rendering stages and commands.
 */
class CoreRenderer {
public:
  /**
   * @brief Constructs a new CoreRenderer object.
   */
  CoreRenderer();

  /**
   * @brief Initializes the CoreRenderer.
   */
  void Initialize();

  // Render stages
  /**
   * @brief Renders the early frame.
   */
  void earlyFrameRender();

  /**
   * @brief Renders the main frame.
   */
  void mainFrameRender();

  /**
   * @brief Renders the late frame.
   */
  void lateFrameRender();

  /**
   * @brief Renders all stages.
   */
  void render();

  // Add command to each queue
  /**
   * @brief Adds a render command to the early render queue.
   * @param cmd The render command to add.
   */
  void addEarlyRenderCommand(std::shared_ptr<RenderCommand> const cmd);

  /**
   * @brief Adds a render command to the main render queue.
   * @param cmd The render command to add.
   */
  void addMainRenderCommand(std::shared_ptr<RenderCommand> const cmd);

  /**
   * @brief Adds a render command to the late render queue.
   * @param cmd The render command to add.
   */
  void addLateRenderCommand(std::shared_ptr<RenderCommand> const cmd);

  /**
   * @brief Comparator struct for comparing RenderCommand objects.
   */
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
  void processCommands(PriorityRenderQueue& commandQueue);

  PriorityRenderQueue earlyRenderCmds; /**< Priority queue for early render commands. */
  PriorityRenderQueue mainRenderCmds; /**< Priority queue for main render commands. */
  PriorityRenderQueue lateRenderCmds; /**< Priority queue for late render commands. */
};

} // namespace Akr::Renderer
