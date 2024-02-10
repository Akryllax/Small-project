#pragma once

#include "DataLayer.h"
#include "INamedObject.h"
#include "spdlog/spdlog.h"
#include <memory>
#include <unordered_map>
#include <vector>

namespace Akr {
    /**
     * @brief A class representing a layer that manages named objects.
     *
     * This class extends the DataLayer class and provides functionality to manage named objects.
     */
    class NamedLayer : public DataLayer {
    public:
        /**
         * @brief Executes a tick operation for the named layer.
         *
         * @param delta The time interval since the last tick.
         */
        void Tick(std::chrono::milliseconds const& delta) override;

        /**
         * @brief Registers a named object with the layer.
         *
         * @param name The name of the object to register.
         * @param namedObject A weak pointer to the named object.
         */
        void RegisterNamedObject(const Common::NamedString& name, std::weak_ptr<Akr::Common::INamedObject> namedObject);

        /**
         * @brief Finds a named object by its name.
         *
         * @param name The name of the object to find.
         * @return A weak pointer to the found object, or nullptr if not found.
         */
        std::weak_ptr<Akr::Common::INamedObject> FindNamedObject(const Common::NamedString& name) const;

        /**
         * @brief Removes a named object from the layer.
         *
         * @param name The name of the object to remove.
         */
        void RemoveNamedObject(const Common::NamedString& name);

        /**
         * @brief Updates the name of a named object.
         *
         * @param oldName The current name of the object.
         * @param newName The new name to assign to the object.
         */
        void UpdateObjectName(const Common::NamedString& oldName, const Common::NamedString& newName);

    private:
        std::unordered_map<Common::NamedString, std::weak_ptr<Common::INamedObject>> namedObjects_; /**< A map of named objects managed by the layer. */
    };
}  // namespace Akr
