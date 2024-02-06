#include "CoreRenderer.h"

namespace Akr::Renderer {
CoreRenderer::CoreRenderer() = default;

void CoreRenderer::Initialize() {
    // Initialization code
}

void CoreRenderer::earlyFrameRender() {
    processCommands(earlyRenderCmds);
}

void CoreRenderer::mainFrameRender() {
    processCommands(mainRenderCmds);
}

void CoreRenderer::lateFrameRender() {
    processCommands(lateRenderCmds);
}

void CoreRenderer::render() {
    // Clear screen
    al_clear_to_color(al_map_rgb(0, 0, 0)); // Example clear color: black

    // Render stages
    earlyFrameRender();
    mainFrameRender();
    lateFrameRender();

    // Flip buffer
    al_flip_display();
}

void CoreRenderer::addEarlyRenderCommand(std::shared_ptr<RenderCommand> const cmd) {
    earlyRenderCmds.push(cmd);
}

void CoreRenderer::addMainRenderCommand(std::shared_ptr<RenderCommand> const cmd) {
    mainRenderCmds.push(cmd);
}

void CoreRenderer::addLateRenderCommand(std::shared_ptr<RenderCommand> const cmd) {
    lateRenderCmds.push(cmd);
}

void CoreRenderer::processCommands(PriorityRenderQueue& commandQueue) {
    while (!commandQueue.empty()) {
        commandQueue.top()->execute();
        commandQueue.pop();
    }
}
} // namespace Akr::Renderer
