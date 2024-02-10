#include "Core.h"
#include "DataLayer.h"
#include "INamedObject.h"
#include "NamedLayer.h"
#include "PhysicsLayer.h"
#include "Screen.h"
#include "allegro5/allegro5.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>

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
  std::vector<std::shared_ptr<Akr::Common::INamedObject>> testNamedObjects {
    std::make_shared<Akr::Common::INamedObject>("object1"), std::make_shared<Akr::Common::INamedObject>("object2")
  };  // We keep the keep-alives here, and autodelete out-of-scope

  void SetUp() override {
    // Initialize objects or perform setup tasks before each test
    namedLayer.RegisterNamedObject(testNamedObjects[0]->GetName(), testNamedObjects[0]);
    namedLayer.RegisterNamedObject(testNamedObjects[1]->GetName(), testNamedObjects[1]);
  }

  // Declare variables needed for testing
  Akr::NamedLayer namedLayer;
};

// Test case for finding a named object
TEST_F(NamedLayerTest, FindNamedObject) {
  auto object1 = namedLayer.FindNamedObject("object1");
  auto object2 = namedLayer.FindNamedObject("object2");
  auto nonExistentObject = namedLayer.FindNamedObject("non_existent");

  ASSERT_TRUE(!object1.expired());           // Check if object1 exists
  ASSERT_TRUE(!object2.expired());           // Check if object2 exists
  ASSERT_TRUE(nonExistentObject.expired());  // Check if non-existent object returns nullptr
}

// Test case for removing a named object
TEST_F(NamedLayerTest, RemoveNamedObject) {
  namedLayer.RemoveNamedObject("object1");
  auto object1 = namedLayer.FindNamedObject("object1");

  ASSERT_TRUE(object1.expired());  // Check if object1 has been removed
}

// Test case for updating the name of a named object
TEST_F(NamedLayerTest, UpdateObjectName) {
  namedLayer.UpdateObjectName("object1", "new_object1");
  auto object1 = namedLayer.FindNamedObject("object1");
  auto newObject1 = namedLayer.FindNamedObject("new_object1");

  ASSERT_TRUE(object1.expired());      // Check if old name no longer exists
  ASSERT_TRUE(!newObject1.expired());  // Check if object has been updated successfully
}

// Test case for registering a new named object
TEST_F(NamedLayerTest, RegisterNamedObject) {
  auto newObj = std::make_shared<Akr::Common::INamedObject>("New Object");
  testNamedObjects.push_back(newObj);
  namedLayer.RegisterNamedObject(testNamedObjects.back()->GetName(), testNamedObjects.back());
  auto newObject = namedLayer.FindNamedObject("New Object");

  ASSERT_TRUE(!newObject.expired());  // Check if new object has been registered successfully

  testNamedObjects.erase(--testNamedObjects.end());
}

// Test case for registering a duplicated named object
TEST_F(NamedLayerTest, RegisterObjectWithDuplicatedName) {
  auto oldObj = std::make_shared<Akr::Common::INamedObject>("New Object");
  auto newObj = std::make_shared<Akr::Common::INamedObject>("New Object");

  testNamedObjects.push_back(oldObj);
  namedLayer.RegisterNamedObject(testNamedObjects.back()->GetName(), testNamedObjects.back());
  testNamedObjects.push_back(newObj);
  namedLayer.RegisterNamedObject(testNamedObjects.back()->GetName(), testNamedObjects.back());

  auto foundOldObject = namedLayer.FindNamedObject("New Object");
  auto foundNewObject = namedLayer.FindNamedObject("New Object_1");


  ASSERT_TRUE(!foundOldObject.expired());  // Check if old object hasn't been replace
  ASSERT_TRUE(!foundNewObject.expired());  // Check if new object has been registered successfully
  ASSERT_NE(foundOldObject.lock(), foundNewObject.lock());  // Check they are different
  ASSERT_EQ(foundNewObject.lock()->GetName(), "New Object_1");  // Check if name of new object has been autoincremented
}

// Test case for ticking the named layer
TEST_F(NamedLayerTest, Tick) {
  // This test only checks if the Tick function runs without errors
  namedLayer.Tick(std::chrono::milliseconds(100));
  // Add more detailed tests if Tick function has specific behaviors to verify
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
