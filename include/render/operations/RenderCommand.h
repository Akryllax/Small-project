#pragma once

#include <climits>

namespace Akr::Renderer {
class RenderCommand {
public:
  enum class RenderCommandPriority { NONE = 0, DEFAULT = 1, MAXIMUM = INT_MAX };

  virtual void execute(RenderCommandPriority const& renderPriority = RenderCommandPriority::DEFAULT) = 0;
  virtual ~RenderCommand() = default;
};
} // namespace Akr::Renderer