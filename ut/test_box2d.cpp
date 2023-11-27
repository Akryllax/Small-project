#include "Core.h"
#include "DataLayer.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include <gtest/gtest.h>
#include <memory>

TEST(Box2DIntegration, BasicTest) {
  auto core1 = &Akr::Core::GetInstance();
  auto core2 = &Akr::Core::GetInstance();

  ASSERT_EQ(core1, core2);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
