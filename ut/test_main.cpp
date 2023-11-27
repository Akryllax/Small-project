#include "Core.h"
#include "DataLayer.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include <gtest/gtest.h>
#include <memory>

TEST(CoreTest, Core_Instance_SingletonCheck) {
  auto core1 = &Akr::Core::GetInstance();
  auto core2 = &Akr::Core::GetInstance();

  ASSERT_EQ(core1, core2);
}

TEST(CoreTest, Core_GetLayer_Single_AddLayer_Ok) {
  auto core = Akr::Core::GetInstance();

  core.AddDataLayer<Akr::NamedLayer>();
  ASSERT_EQ(core.GetLayerCount(), 1);

  core.AddDataLayer<Akr::NamedLayer>();
  ASSERT_EQ(core.GetLayerCount(), 1);
}

TEST(CoreTest, Core_GetLayer_Multi_AddLayer_Ok) {
  auto core = Akr::Core::GetInstance();

  core.AddDataLayer<Akr::NamedLayer>();
  ASSERT_EQ(core.GetLayerCount(), 1);

  core.AddDataLayer<Akr::PhysicsLayer>();
  ASSERT_EQ(core.GetLayerCount(), 2);

  ASSERT_NE(std::dynamic_pointer_cast<Akr::DataLayer>(core.GetDataLayer<Akr::NamedLayer>()), std::dynamic_pointer_cast<Akr::DataLayer>(core.GetDataLayer<Akr::PhysicsLayer>()));
}

TEST(CoreTest, Core_GetLayer_NoDuplicated_Ok) {
  std::shared_ptr<Akr::PhysicsLayer> layer1 = Akr::Core::GetInstance().GetDataLayer<Akr::PhysicsLayer>();
  std::shared_ptr<Akr::PhysicsLayer> layer2 = Akr::Core::GetInstance().GetDataLayer<Akr::PhysicsLayer>();

  ASSERT_TRUE(layer1);
  ASSERT_TRUE(layer2);
  ASSERT_EQ(layer1, layer2);
  ASSERT_EQ(Akr::Core::GetInstance().GetLayerCount(), 1);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
