#pragma once

#include "config.h"
#include "spdlog.h"
#include <filesystem> // For cross-platform path handling
#include <stdexcept>  // For std::runtime_error
#include <string>

namespace Akr {

/**
 * @brief Configuration class for handling application configuration.
 */
class Configuration {
public:
  /**
   * @brief Retrieves the singleton instance of Configuration.
   * @return Reference to the Configuration instance.
   */
  static inline Configuration& GetInstance() {
    static Configuration instance;
    return instance;
  };

  /**
   * @brief Loads the configuration from file.
   * @return True if the configuration is loaded successfully, false otherwise.
   */
  static bool load() {
    // Get the path to the config file
    static std::string configFilePath = getConfigFilePath();
    spdlog::trace("[Configuration] Loading config file from \'{}\'", configFilePath);

    GetInstance().config = al_load_config_file(configFilePath.c_str());
    if (!GetInstance().config) {
      GetInstance().config = al_create_config();
    }

    return GetInstance().config != nullptr;
  };

  /**
   * @brief Saves the current configuration to file.
   * @return True if the configuration is saved successfully, false otherwise.
   */
  static bool save() {
    if (GetInstance().config) {
      // Get the path to the config file
      std::string configFilePath = getConfigFilePath();

      return al_save_config_file(configFilePath.c_str(), GetInstance().config);
    }
    return false;
  }

  /**
   * @brief Retrieves the value associated with the specified key from the configuration.
   * @param key The key whose value is to be retrieved.
   * @param defaultValue The default value to return if the key is not found.
   * @return The value associated with the key, or the defaultValue if the key is not found.
   */
  static std::string getValue(std::string_view const& key, std::string defaultValue = "") {
    if (GetInstance().config) {
      char const* value = al_get_config_value(GetInstance().config, nullptr, key.data());
      return value ? value : defaultValue.c_str();
    }
    return defaultValue;
  }

  /**
   * @brief Sets the value associated with the specified key in the configuration.
   * @param key The key whose value is to be set.
   * @param value The value to set.
   */
  static void setValue(std::string_view const& key, std::string const& value) {
    if (GetInstance().config) {
      al_set_config_value(GetInstance().config, nullptr, key.data(), value.c_str());
    }
  }

  /**
   * @brief Retrieves the file path for the configuration file.
   * @return The file path for the configuration file.
   * @throws std::runtime_error if the directory creation fails.
   */
  static std::string getConfigFilePath() {
    // Determine the platform-specific directory for config files
    std::filesystem::path configDir;
#if defined(_WIN32)
    configDir = std::getenv("APPDATA");
#elif defined(__linux__)
    configDir = std::getenv("HOME");
    configDir += "/.starDissident";
#else
    // Add other platform-specific logic as needed
    // You may want to define a default path if the platform is not recognized
#endif

    // Create the directory if it doesn't exist
    if (!std::filesystem::exists(configDir)) {
      try {
        std::filesystem::create_directory(configDir);
      } catch (std::exception const& e) {
        // Throw an error if directory creation fails
        throw std::runtime_error("Failed to create config directory: " + std::string(e.what()));
      }
    }

    // Append the config file name to the directory
    return configDir.string() + "/config.ini";
  }

private:
  ALLEGRO_CONFIG* config; /**< Pointer to the Allegro configuration object. */

  /**
   * @brief Default constructor for Configuration.
   */
  Configuration() = default;
};

} // namespace Akr
