#pragma once

#include "Configuration.h"
#include "Core.h"
#include "RenderCommand.h"
#include <allegro5/allegro5.h>

namespace Akr::Renderer {
class CoreRenderer {
    CoreRenderer& operator=(const CoreRenderer&) = delete;
    CoreRenderer(const CoreRenderer&) = delete;
};
} // namespace Akr::Renderer