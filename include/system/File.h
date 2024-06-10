#include <fstream>
#include <string>

namespace Akr::Util {
class File {
public:
  static File Open(std::string const& filename) { return File(filename); }

  static std::string Read(std::string const& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      return "";
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content;
  }

  static void Write(std::string const& filename, std::string const& data) {
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
      return;
    }

    file << data;
    file.close();
  }

  static void WriteAll(std::string const& filename, std::string const& data) {
    std::ofstream file(filename);
    if (!file.is_open()) {
      return;
    }

    file << data;
    file.close();
  }

  static std::string ReadAll(std::string const& filename) { return Read(filename); }

private:
  explicit File(std::string const& filename) : m_filename(filename) {}

  std::string m_filename;
};
}  // namespace Akr::Util
