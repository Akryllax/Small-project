#pragma once

#include "DataLayer.h"
#include "ITickable.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <typeindex>

namespace Akr {
class Core : public ITickable {
 public:
  static Core& GetInstance() {
    // Ensure that there is only one instance created.
    static Core instance;
    return instance;
  }

  template <typename T>
  void AddDataLayer(std::shared_ptr<T> dataLayer) {
    std::cout << "Added data layer";

    auto it = dataLayerMap_.find(std::type_index(typeid(T)));

    if (it != dataLayerMap_.end()) {
      std::cout << ", OVERRIDING an existing layer";
      // You can choose to update the existing layer here if needed.
      it->second = dataLayer;
    } else {
      dataLayerMap_[std::type_index(typeid(T))] =
          dataLayer;  // Use std::type_index
    }

    std::cout << ", new size: " << dataLayerMap_.size() << std::endl;
  }

  template <typename T>
  std::shared_ptr<T const> GetDataLayer() const {
    auto it = dataLayerMap_.find(typeid(T));
    std::shared_ptr<T const> typedLayer;

    if (it == dataLayerMap_.end()) {
      typedLayer = std::make_shared<T>();
      AddDataLayer(typedLayer);
    } else {
      std::dynamic_pointer_cast<T const>(it->second);
    }

    return typedLayer;
  }

  void Tick(std::chrono::milliseconds const delta) override {
    for (auto& entry : dataLayerMap_) {
      std::cout << entry.first.name() << std::endl;
      std::cout << entry.second << std::endl;

      entry.second->Tick(delta);
    }

    frameCount_++;
  }

  inline uint64_t GetFrameCount() const { return frameCount_; }

 private:
  uint64_t frameCount_;

 private:
  std::map<std::type_index, std::shared_ptr<DataLayer>> dataLayerMap_;

 private:
  Core() : frameCount_(0){};
};
}  // namespace Akr
