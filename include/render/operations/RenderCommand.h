#pragma once

#include <climits>

namespace Akr::Renderer {
class RenderCommand {
public:
  enum class RenderCommandPriority { NONE = 0, DEFAULT = 1, MAXIMUM = INT_MAX };
  const RenderCommandPriority renderPriority;
  explicit RenderCommand(RenderCommandPriority const& _renderPriority = RenderCommandPriority::DEFAULT) : renderPriority(_renderPriority){};

  virtual void prepare() {
    // Implement preframe logic
  };
  virtual void execute() = 0;
  virtual void release() {
    /// Implement postframe logic
  };

  virtual ~RenderCommand() = default;
};
} // namespace Akr::Renderer