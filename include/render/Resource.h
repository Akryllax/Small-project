#pragma once

#include "allegro5/bitmap.h"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <filesystem>  // For cross-platform path handling
#include <string>

#ifdef __unix__
#include <unistd.h>  // For readlink
#endif
#ifdef WIN32
#include <windows.h>
#endif

namespace Akr {

/**
 * @brief Resource class for managing resources.
 */
class Resource {
public:
  /**
   * @brief Constructs a Resource object with the specified filename.
   * @param filename The filename of the resource.
   */
  explicit Resource(std::string const& filename) : filename(filename) {}

  /**
   * @brief Virtual destructor for Resource objects.
   */
  virtual ~Resource() = default;

  /**
   * @brief Loads the resource.
   * @return True if the resource is loaded successfully, false otherwise.
   */
  virtual bool load() = 0;

  /**
   * @brief Unloads the resource.
   */
  virtual void unload() = 0;

  /**
   * @brief Gets the filename of the resource.
   * @return The filename of the resource.
   */
  std::string const& getFilename() const { return filename; }

public:
  static std::filesystem::path GetResourceFolderPath() { return GetExecutableFolderPath().append("res"); }

protected:
  /**
   * @brief Gets the full path to the resource file.
   * @return The full path to the resource file.
   */
  std::filesystem::path getFullPath() const {
    // Assuming resources are in the "res" folder next to the binary
    return GetResourceFolderPath().append(filename);
  }

private:
  std::string filename; /**< The filename of the resource. */

  /**
   * @brief Gets the path to the directory containing the executable.
   * @return The path to the directory containing the executable.
   */
  static std::filesystem::path GetExecutableFolderPath() {
    // Get the path to the directory containing the executable
    std::filesystem::path const executablePath = std::filesystem::path(getExecutableFullPath()).parent_path();
    spdlog::trace("[Resource] GetExecutableFolderPath() returned: {}", executablePath.string());
    return executablePath;
  }

  /**
   * @brief Gets the full path to the executable.
   * @return The full path to the executable.
   */
  static std::filesystem::path getExecutableFullPath() {
    // Get the full path to the executable
#if defined(_WIN32)
    char buffer[MAX_PATH];
    DWORD length = GetModuleFileName(nullptr, buffer, MAX_PATH);
    std::filesystem::path exePath;
    if (length == 0) {
      spdlog::error("[Resource] GetModuleFileName() returned empty name!");
      return "";
    } else {
      exePath = std::filesystem::path(std::string(buffer, length));
    }
    return exePath;
#else
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
      buffer[len] = '\0';
      return std::string(buffer);
    } else {
      // Error handling: You may want to throw an exception or return an empty string
      return "";
    }
#endif
  }
};

/**
 * @brief BitmapResource class for managing bitmap resources.
 */
class BitmapResource : public Resource {
  ALLEGRO_BITMAP* bitmap; /**< Pointer to the loaded bitmap. */

public:
  using Resource::Resource;

  /**
   * @brief Gets the loaded bitmap.
   * @return Pointer to the loaded bitmap.
   */
  ALLEGRO_BITMAP* getBitmap() const { return bitmap; };

  bool load() override {
    // Initialize Allegro and Allegro Image
    if (!al_init() || !al_init_image_addon()) {
      // Handle initialization failure
      spdlog::error("Failed to initialize Allegro or Allegro Image");
      return false;
    }

    // Example using Allegro 5 and Allegro Image to load a PNG bitmap
    std::filesystem::path bitmapPath = getFullPath();
    bitmap = al_load_bitmap(bitmapPath.string().c_str());
    if(!bitmap)
    {
      spdlog::error("[BitmapResource] Couldn't load bitmap at path: {}", bitmapPath.string());
    }

    // Check if the bitmap was loaded successfully
    return bitmap != nullptr;
  }

  void unload() override {
    // Implement bitmap unloading logic using Allegro 5 or any other library
    // Example using Allegro 5:
    al_destroy_bitmap(bitmap);
  }
};

/**
 * @brief AudioResource class for managing audio resources.
 */
class AudioResource : public Resource {
public:
  explicit AudioResource(std::string const& filename) : Resource(filename) {}

  bool load() override {
    // Implement audio loading logic using Allegro 5 or any other library
    // Example using Allegro 5:
    // sample = al_load_sample(getFullPath().c_str());
    // return sample != nullptr;

    // Placeholder return
    return true;
  }

  void unload() override {
    // Implement audio unloading logic using Allegro 5 or any other library
    // Example using Allegro 5:
    // al_destroy_sample(sample);
  }
};

}  // namespace Akr
