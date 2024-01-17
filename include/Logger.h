#pragma once

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"  // or "../stdout_sinks.h" if no colors needed
#include "spdlog/spdlog.h"
#include <cassert>

namespace Akr {
class Logger {
public:
  virtual ~Logger() = default;

  static void init() {
    spdlog::trace("Running Logger::init()");
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/core.log", true);

    // or you can even set multi_sink logger as default logger
    spdlog::set_default_logger(
        std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
    auto logger = spdlog::get("multi_sink");
    logger->set_pattern("[core] [%^%l%$] %v");
    logger->set_level(spdlog::level::trace);
    isInitialized = true;
  };

  static void init(std::string filename) {
    spdlog::trace("Running Logger::init(filename)");
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("logs/{}", filename), true);

    // or you can even set multi_sink logger as default logger
    spdlog::set_default_logger(
        std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
    auto logger = spdlog::get("multi_sink");
    logger->set_pattern("[core] [%^%l%$] %v");
    logger->set_level(spdlog::level::trace);
  }

  static void info(std::string_view view) {
    assert(isInitialized);
    spdlog::info(view);
  }

  static void warn(std::string_view view) {
    assert(isInitialized);
    spdlog::warn(view);
  }

  static void error(std::string_view view) {
    assert(isInitialized);
    spdlog::error(view);
  }

private:
  /**
   * @brief Private constructor for singleton pattern.
   */
  Logger() = default;
  Logger(Logger const& core) = delete;
  static inline bool isInitialized = false;
};
}  // namespace Akr