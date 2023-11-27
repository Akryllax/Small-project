#include "config.h"
#include <any>
#include <filesystem>  // For cross-platform path handling
#include <stdexcept>   // For std::runtime_error
#include <string>

class Configuration {
  ALLEGRO_CONFIG* config;

 private:
  Configuration() = default;

 public:
  static inline Configuration& GetInstance()
  {
    static Configuration instance;
    return instance;
  };

  static bool load() {
    // Get the path to the config file
    std::string configFilePath = getConfigFilePath();

    GetInstance().config = al_load_config_file(configFilePath.c_str());
    if (!GetInstance().config) {
      GetInstance().config = al_create_config();
    }

    return GetInstance().config != nullptr;
  };

  static bool save() {
    if (GetInstance().config) {
      // Get the path to the config file
      std::string configFilePath = getConfigFilePath();

      return al_save_config_file(configFilePath.c_str(), GetInstance().config);
    }
    return false;
  }

  static std::string getValue(std::string_view const& key,
                              std::string defaultValue = "") {
    if (GetInstance().config) {
      char const* value =
          al_get_config_value(GetInstance().config, nullptr, key.data());
      return value ? value : defaultValue.c_str();
    }
    return defaultValue;
  }

  static void setValue(std::string_view const& key, std::string const& value) {
    if (GetInstance().config) {
      al_set_config_value(GetInstance().config, nullptr, key.data(), value.c_str());
    }
  }

 private:
  static std::string getConfigFilePath() {
    // Determine the platform-specific directory for config files
    std::string configDir;
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
        throw std::runtime_error("Failed to create config directory: " +
                                 std::string(e.what()));
      }
    }

    // Append the config file name to the directory
    return configDir + "/config.ini";
  }
};
