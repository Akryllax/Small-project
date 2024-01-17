/**
 * @file Core.h
 * @brief Definition of the Core class.
 */

#pragma once

#include "DataLayer.h"
#include "ITickable.h"
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include <typeindex>
#include "spdlog/spdlog.h"

namespace Akr {

// Type trait to check if T is derived from DataLayer
template <typename T>
struct IsDerivedFromDataLayer {
  static constexpr bool value = std::is_base_of_v<DataLayer, T>;
};

/**
 * @brief Core class representing the core functionality.
 *
 * This class is a singleton that manages data layers and provides tick
 * functionality. It inherits from ITickable.
 */
class Core : public ITickable {
public:
  /**
   * @brief Virtual destructor of the class
   */
  virtual ~Core() = default;

  /**
   * @brief Get the singleton instance of the Core class.
   *
   * @return Reference to the Core instance.
   */
  [[nodiscard("Don't forget about me")]] static Core& GetInstance() {
    static Core instance;  // Define and initialize the static member
    return instance;
  }

  /**
   * @brief Adds a data layer to the Core.
   *
   * This function template adds a data layer to the Core. The provided type T
   * must be derived from DataLayer. If a layer of the same type already exists,
   * it can be overridden.
   *
   * @tparam T Type of the data layer. Must be derived from DataLayer.
   * @param dataLayer Shared pointer to the data layer.
   */
  template <typename T, std::enable_if_t<IsDerivedFromDataLayer<T>::value, int> = 0>
  void AddDataLayer(std::shared_ptr<T> dataLayer) {
    if (auto it = dataLayerMap_.find(std::type_index(typeid(T))); it != dataLayerMap_.end()) {
      std::cout << ", OVERRIDING an existing layer";
      // You can choose to update the existing layer here if needed.
      it->second = dataLayer;
    } else {
      dataLayerMap_[std::type_index(typeid(T))] = dataLayer;  // Use std::type_index
    }

    spdlog::trace("Added data layer, new size: {}", dataLayerMap_.size());
  }

  /**
   * @brief Function overload to dynamically add a data layer.
   *
   * This function template creates and adds a data layer of the specified type
   * to the Core.
   *
   * @tparam T Type of the data layer.
   */
  template <typename T>
  void AddDataLayer() {
    AddDataLayer(std::make_shared<T>());
  }

  /**
   * @brief Function template to get a data layer.
   *
   * This function template retrieves a shared pointer to a data layer of the
   * specified type. If the layer doesn't exist, it creates and adds a new layer
   * to the Core.
   *
   * @tparam T Type of the data layer.
   * @return Shared pointer to the data layer.
   */
  template <typename T, std::enable_if_t<IsDerivedFromDataLayer<T>::value, int> = 0>
  static std::shared_ptr<T> GetDataLayer() {
    auto it = GetInstance().dataLayerMap_.find(typeid(T));
    std::shared_ptr<T> typedLayer;

    if (it == GetInstance().dataLayerMap_.end()) {
      typedLayer = std::make_shared<T>();
      GetInstance().AddDataLayer(typedLayer);
    } else {
      typedLayer = std::dynamic_pointer_cast<T>(it->second);
    }

    return typedLayer;
  }

  /**
   * @brief Implementation of the ITickable interface.
   *
   * This function is called to perform tick operations on all data layers.
   *
   * @param delta Time difference since the last tick.
   */
  void Tick(std::chrono::milliseconds const delta) override {
    for (auto const& [type, dataLayer] : dataLayerMap_) {
      spdlog::trace("{}::Tick()", type.name());

      dataLayer->Tick(delta);
    }

    frameCount_++;
  }

  /**
   * @brief Get the current frame count.
   *
   * @return Current frame count.
   */
  inline uint64_t GetFrameCount() const { return frameCount_; }
  inline size_t GetLayerCount() const { return this->dataLayerMap_.size(); }

private:
  uint64_t frameCount_ = 0;  ///< Frame count variable.

  std::map<std::type_index, std::shared_ptr<DataLayer>> dataLayerMap_;  ///< Map to store data layers.

  /**
   * @brief Private constructor for singleton pattern.
   */
  Core() = default;

  /**
   * @brief Private deleted constructor for singleton pattern.
   */
  Core(Core const& core) = delete;
};

}  // namespace Akr
