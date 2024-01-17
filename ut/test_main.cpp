#include "Core.h"
#include "DataLayer.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include <gtest/gtest.h>
#include <memory>

TEST(CoreTest, Core_Instance_SingletonCheck) {
  auto& core1 = Akr::Core::GetInstance();
  auto& core2 = Akr::Core::GetInstance();

  ASSERT_EQ(&core1, &core2);
}

TEST(CoreTest, Core_GetLayer_Single_AddLayer_Ok) {
  auto& core = Akr::Core::GetInstance();

  core.AddDataLayer<Akr::NamedLayer>();
  ASSERT_EQ(core.GetLayerCount(), 1);

  core.AddDataLayer<Akr::NamedLayer>();
  ASSERT_EQ(core.GetLayerCount(), 1);
}

TEST(CoreTest, Core_GetLayer_Multi_AddLayer_Ok) {
  auto& core = Akr::Core::GetInstance();

  core.AddDataLayer<Akr::NamedLayer>();
  ASSERT_EQ(core.GetLayerCount(), 1);

  core.AddDataLayer<Akr::PhysicsLayer>();
  ASSERT_EQ(core.GetLayerCount(), 2);

  ASSERT_NE(std::dynamic_pointer_cast<Akr::DataLayer>(core.GetDataLayer<Akr::NamedLayer>()), std::dynamic_pointer_cast<Akr::DataLayer>(core.GetDataLayer<Akr::PhysicsLayer>()));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
