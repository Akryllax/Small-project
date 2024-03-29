#include "NamedLayer.h"
#include "INamedObject.h"
#include "spdlog/spdlog.h"

namespace Akr {
    void NamedLayer::Tick(std::chrono::milliseconds const& delta) {
        spdlog::trace("[NamedLayer] Tick()");
        // Implement tick logic here if needed
    }

    void NamedLayer::RegisterNamedObject(std::string const& name, Akr::Common::INamedObject* namedObject) {
        spdlog::trace("[NamedLayer] Registering NamedObject with name: {}. Current vector size: {}", name, namedObjects_.size());
        // Check if the object with the same name already exists
        auto it = namedObjects_.find(name);
        if (it == namedObjects_.end()) {
            spdlog::trace("[NamedLayer] Key isn't in use, adding with key: {}", name);
            // Object with the given name doesn't exist, so add it directly
            namedObjects_[name] = namedObject;
        } else {
            spdlog::trace("[NamedLayer] Key is in use, generating new name...");
            // Object with the given name already exists, so auto-increment numerically
            int suffix = 1;
            std::string newName = name;
            while (namedObjects_.find(newName) != namedObjects_.end()) {
                // Append a numerical suffix to the name
                newName = name + "_" + std::to_string(suffix);
                suffix++;
            }
            // Add the object with the new name
            namedObjects_[newName] = namedObject;
            // Update the object's name so it is reflected everywhere
            namedObject->SetName(newName);
            spdlog::warn("[NamedLayer] Object with name '{}' already registered. Auto-incremented to '{}'.", name, newName);
        }

        spdlog::trace("[NamedLayer] Final vector size: {}", namedObjects_.size());
    }

    Akr::Common::INamedObject* NamedLayer::FindNamedObject(std::string const& name) const {
        auto it = namedObjects_.find(name);
        if (it != namedObjects_.end()) {
            return it->second;
        } else {
            spdlog::warn("[NamedLayer] Object with name '{}' not found.", name);
            return nullptr;
        }
    }

    void NamedLayer::RemoveNamedObject(std::string const& name) {
        auto it = namedObjects_.find(name);
        if (it != namedObjects_.end()) {
            namedObjects_.erase(it);
        } else {
            spdlog::warn("[NamedLayer] Object with name '{}' not found for removal.", name);
        }
    }

    void NamedLayer::UpdateObjectName(std::string const& oldName, std::string const& newName) {
        auto it = namedObjects_.find(oldName);
        if (it != namedObjects_.end()) {
            // Update the key in the map
            namedObjects_[newName] = it->second;
            namedObjects_.erase(it);  // Remove the old key
        } else {
            spdlog::warn("[NamedLayer] Object with name '{}' not found for update.", oldName);
        }
    }
}  // namespace Akr
