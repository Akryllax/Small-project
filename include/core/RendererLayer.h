#pragma once

#include "CoreRenderer.h"
#include "DataLayer.h"
#include "DebugRenderer.h"
#include "UiRenderer.h"
#include "IRenderable.h"
#include "RenderCommand.h"
#include <memory>
#include <vector>

namespace Akr {

/**
 * @brief The RendererLayer class manages rendering tasks and interacts with the rendering subsystem.
 */
class RendererLayer : public DataLayer {
public:
    /**
     * @brief Gets the debug renderer instance.
     * @return A reference to the debug renderer.
     */
    inline Renderer::DebugRenderer& GetDebugRenderer() { return debugRenderer_; }

    /**
     * @brief Gets the debug renderer instance.
     * @return A reference to the debug renderer.
     */
    inline Renderer::UiRenderer& GetUiRenderer() { return uiRenderer_; }

    /**
     * @brief Gets the core renderer instance.
     * @return A reference to the core renderer.
     */
    inline Renderer::CoreRenderer& GetCoreRenderer() { return renderer_; }

    /**
     * @brief Performs rendering operations.
     * @param delta The time elapsed since the last rendering update.
     */
    void Tick(std::chrono::milliseconds const& delta) override;

    /**
     * @brief Registers an IRenderable object for rendering.
     * @param _renderable The IRenderable object to register.
     */
    void RegisterRenderable(std::shared_ptr<Akr::IRenderable> _renderable);

    /**
     * @brief Registers an IRenderable pointer for rendering.
     * @param _renderablePtr The pointer to the IRenderable object to register.
     */
    void RegisterRenderablePtr(Akr::IRenderable* _renderablePtr);

    /**
     * @brief Registers an IRenderable pointer for rendering.
     * @param _renderablePtr The pointer to the IRenderable object to register.
     */
    void RegisterUIRenderablePtr(Akr::IRenderable* _renderablePtr);

    /**
     * @brief Adds a render command to be executed early in the rendering process.
     * @param command The render command to add.
     */
    void AddEarlyRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command);

    /**
     * @brief Adds a render command to be executed during the main rendering process.
     * @param command The render command to add.
     */
    void AddMainRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command);

    /**
     * @brief Adds a render command to be executed late in the rendering process.
     * @param command The render command to add.
     */
    void AddLateRenderCommand(std::shared_ptr<Akr::Renderer::RenderCommand> command);

private:
    Akr::Renderer::CoreRenderer renderer_; /**< The core renderer instance. */
    Akr::Renderer::DebugRenderer debugRenderer_; /**< The debug renderer instance. */
    Akr::Renderer::UiRenderer uiRenderer_; /**< The UI renderer instance. */

    std::vector<std::shared_ptr<IRenderable>> renderables_; /**< Vector of registered IRenderable objects. */
    std::vector<IRenderable*> purePtrRenderables_; /**< Vector of pointers to registered IRenderable objects. */
    std::vector<IRenderable*> pureUIPtrRenderables_; /**< Vector of pointers to registered IRenderable objects. */
};

}  // namespace Akr
