#pragma once

#include "Configuration.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"  // or "../stdout_sinks.h" if no colors needed
#include "spdlog/spdlog.h"
#include <spdlog/common.h>
#include <cassert>

namespace Akr {
class Logger {
public:
  virtual ~Logger() = default;

  static void init() {
    init("core.log");
  };

  static void init(std::string filename) {
    spdlog::info("Running Logger::init({})", filename);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(fmt::format("logs/{}", filename), true);

    // or you can even set multi_sink logger as default logger
    spdlog::set_default_logger(
        std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));
    auto logger = spdlog::get("multi_sink");
    logger->set_pattern("[%Y-%m-%d %T] [%^%l%$] %v");

    auto dbgLevel = Akr::Configuration::getValue("DEBUG_LEVEL", "trace");
    std::transform(dbgLevel.begin(), dbgLevel.end(), dbgLevel.begin(), [](unsigned char c) { return std::tolower(c); });

    if (dbgLevel == "info") {
      spdlog::info("Setting log level to: {}", "INFO");
      logger->set_level(spdlog::level::info);
    } else if (dbgLevel == "trace") {
      spdlog::info("Setting log level to: {}", "TRACE");
      logger->set_level(spdlog::level::trace);
    } else if (dbgLevel == "warn") {
      spdlog::info("Setting log level to: {}", "WARN");
      logger->set_level(spdlog::level::warn);
    } else if (dbgLevel == "error") {
      spdlog::info("Setting log level to: {}", "ERROR");
      logger->set_level(spdlog::level::err);
    } else {
      spdlog::warn("Unknown debug level: \"{}\", defaulting to \"INFO\"", dbgLevel);
      logger->set_level(spdlog::level::err);
      // Set a default log level here if needed
    }

    isInitialized = true;
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