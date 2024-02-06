#include "Core.h"
#include "DataLayer.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "Screen.h"
#include "allegro5/allegro5.h"
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

  ASSERT_NE(std::dynamic_pointer_cast<Akr::DataLayer>(core.GetDataLayer<Akr::NamedLayer>()),
            std::dynamic_pointer_cast<Akr::DataLayer>(core.GetDataLayer<Akr::PhysicsLayer>()));
}

class ScreenTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize Allegro 5 components
    ASSERT_TRUE(al_init());              // Initialize Allegro
    ASSERT_TRUE(al_install_keyboard());  // Install keyboard
    ASSERT_TRUE(al_install_mouse());     // Install mouse

    // Create the display for testing
    display_ = al_create_display(800, 600);
    ASSERT_TRUE(display_ != nullptr);

    // Register the display
    Akr::Screen::RegisterDisplay(display_);
  }

  void TearDown() override {
    // Clean up resources
    if (display_) {
      al_destroy_display(display_);  // Destroy the display
    }

    al_uninstall_mouse();     // Uninstall mouse
    al_uninstall_keyboard();  // Uninstall keyboard
    al_uninstall_system();    // Uninstall Allegro system
  }

  ALLEGRO_DISPLAY* display_;  // Pointer to the test display
};

TEST_F(ScreenTest, InitialScreenSize) {
  b2Vec2 initialSize = Akr::Screen::getScreenSize();
  ASSERT_EQ(initialSize.x, 800);
  ASSERT_EQ(initialSize.y, 600);
}

TEST_F(ScreenTest, RegisterDisplay) {
  ALLEGRO_DISPLAY* registeredDisplay = Akr::Screen::getDisplay();
  ASSERT_EQ(registeredDisplay, display_);
}

TEST_F(ScreenTest, ResizeScreenSize) {
  Akr::Screen::ResizeDisplay({1280, 720});
  b2Vec2 updatedSize = Akr::Screen::getScreenSize();
  ASSERT_EQ(1280, updatedSize.x);
  ASSERT_EQ(720, updatedSize.y);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
