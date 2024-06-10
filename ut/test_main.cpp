#include "Core.h"
#include "DataLayer.h"
#include "GObject.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "Screen.h"
#include "TestShip.h"
#include "allegro5/allegro5.h"
#include "spdlog/common.h"
#include "spdlog/spdlog.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

#ifdef _WIN32
#include <fileapi.h>
#endif

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

// Define a test fixture for NamedLayer
class NamedLayerTest : public testing::Test {
protected:
  std::vector<std::shared_ptr<Akr::Game::GObject>> testNamedObjects;  // Use shared_ptr for memory management

  void SetUp() override {
    testNamedObjects.push_back(Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>("object1"));
    testNamedObjects.push_back(Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>("object2"));
  }
};

// Test case for finding a named object
TEST_F(NamedLayerTest, FindNamedObject) {
  auto object1 = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("object1");
  auto object2 = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("object2");
  auto nonExistentObject = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("non_existent");

  ASSERT_TRUE(object1 != nullptr);            // Check if object1 exists
  ASSERT_TRUE(object2 != nullptr);            // Check if object2 exists
  ASSERT_TRUE(nonExistentObject == nullptr);  // Check if non-existent object returns nullptr
}

// Test case for removing a named object
TEST_F(NamedLayerTest, RemoveNamedObject) {
  Akr::Core::GetDataLayer<Akr::NamedLayer>()->RemoveNamedObject("object1");
  auto object1 = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("object1");

  ASSERT_TRUE(!object1);  // Check if object1 has been removed
}

// Test case for updating the name of a named object
TEST_F(NamedLayerTest, UpdateObjectName) {
  Akr::Core::GetDataLayer<Akr::NamedLayer>()->UpdateObjectName("object1", "new_object1");
  auto object1 = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("object1");
  auto newObject1 = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("new_object1");

  ASSERT_TRUE(!object1);    // Check if old name no longer exists
  ASSERT_TRUE(newObject1);  // Check if object has been updated successfully
}

// Test case for registering a new named object
TEST_F(NamedLayerTest, RegisterNamedObject) {
  auto newObj = Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>("New Object");
  testNamedObjects.push_back(newObj);
  auto newObject = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("New Object");

  ASSERT_TRUE(newObject);  // Check if new object has been registered successfully

  testNamedObjects.pop_back(); // Remove the object after the test
}

// Test case for registering a duplicated named object
TEST_F(NamedLayerTest, RegisterObjectWithDuplicatedName) {
  auto oldObj = Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>("New Object");
  auto newObj = Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>("New Object");

  testNamedObjects.push_back(oldObj);
  testNamedObjects.push_back(newObj);

  auto foundOldObject = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("New Object");
  auto foundNewObject = Akr::Core::GetDataLayer<Akr::NamedLayer>()->FindNamedObject("New Object_1");

  ASSERT_TRUE(foundOldObject);                           // Check if old object hasn't been replaced
  ASSERT_TRUE(foundNewObject);                           // Check if new object has been registered successfully
  ASSERT_NE(foundOldObject, foundNewObject);             // Check they are different
  ASSERT_EQ(foundNewObject->GetName(), "New Object_1");  // Check if name of new object has been autoincremented

  // Remove objects after the test
  testNamedObjects.pop_back();
  testNamedObjects.pop_back();
}

// Test case for ticking the named layer
TEST_F(NamedLayerTest, Tick) {
  // This test only checks if the Tick function runs without errors
  Akr::Core::GetDataLayer<Akr::NamedLayer>()->Tick(std::chrono::milliseconds(100));
  // Add more detailed tests if Tick function has specific behaviors to verify
}

// Test fixture for GameLayer
class GameLayerTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize GameLayer
    gameLayer.Initialize();
  }

  void TearDown() override {
    // Clean up resources
    gameLayer.Kill();
  }

  // Test GameLayer instance
  Akr::GameLayer gameLayer;
};

// Test case to verify tracking of objects in GameLayer
TEST_F(GameLayerTest, TrackedObjects) {
  // Create a test GObject
  auto gObject = Akr::Game::GObject::make_shared_gobject<Akr::TestShip>("TestObject");

  // Track the test GObject in GameLayer
  gameLayer.TrackGObject(gObject);

  // Check if the test GObject is tracked in GameLayer
  EXPECT_TRUE(gameLayer.IsGObjectTracked(gObject)) << "Test object should be tracked in GameLayer";
}

int main(int argc, char** argv) {
  spdlog::set_level(spdlog::level::trace);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
