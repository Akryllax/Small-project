#pragma once

#include "AllegroManager.h"
#include "CompositeRenderCommand.h"
#include "DrawRectAlpha.h"
#include "DrawRectOperation.h"
#include "DrawTextCommand.h"
#include "FIFOList.h"
#include "Rect.h"
#include "Screen.h"
#include <allegro5/color.h>
#include <box2d/b2_math.h>
#include <spdlog/spdlog.h>
#include <sys/types.h>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <queue>
#include <string>

namespace Akr::Debug {
class DebugConsole : public IRenderable {
public:
  enum class LogLevel { LOG, WARNING, ERROR };

  struct LogMessage {
    LogLevel level;
    std::string message;
  };

  [[nodiscard("Don't forget about me")]] static DebugConsole& GetInstance() {
    static DebugConsole instance;  // Define and initialize the static member
    return instance;
  }

  std::shared_ptr<Renderer::RenderCommand> GenerateRenderCommand() override {
    spdlog::trace("[DebugConsole] Generating render command");

    //! DEBT It recalculates every frame, should be done only once per screen resize
    consoleRect = Math::Rect{.x = Screen::getScreenSize().x - width, .y = Screen::getScreenSize().y - height, .w = width, .h = height};

    spdlog::trace("[DebugConsole] ConsoleRect: x={}, y={}, w={}, h={}", consoleRect.x, consoleRect.y, consoleRect.w, consoleRect.h);
    auto composideOperation = std::make_shared<Renderer::CompositeRenderComand>();
    auto drawRectOperation = std::make_shared<Renderer::DrawRectAlphaOperation>(ALLEGRO_COLOR{50/255.0f,50/255.0f,50/255.0f, 0.1f}, consoleRect);
    composideOperation->QueueCommand(drawRectOperation);

    size_t lineIndex = 0;
    for (auto const& logMessage : logQueue_) {
      ALLEGRO_COLOR textColor;

      switch (logMessage.level) {
        case LogLevel::LOG:
          textColor = ALLEGRO_COLOR{0, 255, 0, 1.0f};
          break;
        case LogLevel::WARNING:
          textColor = ALLEGRO_COLOR{255, 255, 0, 1.0f};
          break;
        case LogLevel::ERROR:
          textColor = ALLEGRO_COLOR{255, 0, 0, 1.0f};
          break;

      }
      auto drawTextOperation = std::make_shared<Renderer::DrawTextCommand>(std::string_view(fmt::format("[{}] {}", lineIndex, logMessage.message)), CalculateTextPosition(logMessage.message, lineIndex), AllegroManager::mainFont, textColor);
      composideOperation->QueueCommand(drawTextOperation);
      lineIndex++;
    }

    return composideOperation;
  }

  static void Log(std::string const& message, LogLevel level = LogLevel::LOG) {
    LogMessage logMessage{.level = level, .message = message};

    logQueue_.push(logMessage);

    if (logQueue_.size() > maxMessagesPerQueue) {
      logQueue_.pop();
    }
  }

  static void LogError(std::string const& message) { Log(message, LogLevel::ERROR); }

  static void LogWarning(std::string const& message) { Log(message, LogLevel::WARNING); }

private:
  using StringQueue = FIFOList<LogMessage>;

  static constexpr uint8_t const fontSize = 12;

  static constexpr uint16_t const width = 500;
  static constexpr uint16_t const height = 300;

  static inline StringQueue logQueue_;

  static inline Math::Rect consoleRect =
      Math::Rect{.x = Screen::getScreenSize().x - width, .y = Screen::getScreenSize().y - height, .w = width, .h = height};

  static constexpr uint8_t const maxMessagesPerQueue = 50;

  DebugConsole() {
    spdlog::trace("[DebugConsole] Constructing DebugConsole");
    Akr::Core::GetDataLayer<Akr::RendererLayer>()->RegisterRenderablePtr(this);
    spdlog::trace("[DebugConsole] Registered DebugConsole as renderable");
  }
  ~DebugConsole() override = default;
  DebugConsole(DebugConsole const&) = delete;

  b2Vec2 CalculateTextPosition(std::string const& text, size_t lineIndex) const {
    float textWidth = text.length() * fontSize;
    float textHeight = fontSize;
    float consoleWidth = consoleRect.w;
    float consoleHeight = consoleRect.h;
    float x = consoleRect.x;
    float y = consoleRect.y + lineIndex * fontSize;

    if (textWidth > consoleWidth) {
      x = consoleRect.x - (textWidth - consoleWidth);
    }
    if (y + textHeight > consoleRect.y + consoleHeight) {
      y = consoleRect.y - (textHeight - consoleHeight);
    }

    return b2Vec2{x, y};
  }
};
}  // namespace Akr::Debug