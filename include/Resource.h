#include "bitmap.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <filesystem>  // For cross-platform path handling
#include <iostream>
#include <string>
#include <unistd.h>  // For readlink

namespace Akr {
class Resource {
 public:
  explicit Resource(std::string const& filename) : filename(filename) {}

  virtual bool load() = 0;
  virtual void unload() = 0;

  std::string const& getFilename() const { return filename; }

 protected:
  std::string getFullPath() const {
    // Assuming resources are in the "res" folder next to the binary
    return getExecutablePath() + "/res/" + filename;
  }

 private:
  std::string filename;

  static std::string getExecutablePath() {
    // Get the path to the directory containing the executable
    std::string const executablePath = std::filesystem::path(getExecutableFullPath()).parent_path();
    return executablePath;
  }

  static std::string getExecutableFullPath() {
    // Get the full path to the executable
#if defined(_WIN32)
    char buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);
    return buffer;
#else
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
      buffer[len] = '\0';
      return buffer;
    } else {
      // Handle error
      // You may want to throw an exception or return an empty string
      return "";
    }
#endif
  }
};

class BitmapResource : public Resource {
  ALLEGRO_BITMAP* bitmap;

 public:
  explicit BitmapResource(std::string const& filename) : Resource(filename) {}

  ALLEGRO_BITMAP* getBitmap() const { return bitmap; };

  bool load() override {
    // Initialize Allegro and Allegro Image
    if (!al_init() || !al_init_image_addon()) {
      // Handle initialization failure
      std::cerr << "Failed to initialize Allegro or Allegro Image" << std::endl;
      return false;
    }

    // Example using Allegro 5 and Allegro Image to load a PNG bitmap
    std::string bitmapPath = getFullPath();
    bitmap = al_load_bitmap(bitmapPath.c_str());

    // Check if the bitmap was loaded successfully
    return bitmap != nullptr;
  }

  void unload() override {
    // Implement bitmap unloading logic using Allegro 5 or any other library
    // Example using Allegro 5:
    al_destroy_bitmap(bitmap);
  }

 private:
  // Allegro 5 bitmap object or any other specific data for bitmaps
};

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

 private:
  // Allegro 5 sample object or any other specific data for audio
};
};  // namespace Akr