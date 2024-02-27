#include "GObject.h"
#include "GObject.h"  // Include the header file that defines Akr::Game::GObject
#include "Scene.h"
#include "Tree.h"  // Include the header file that defines Tree and TreeNode
#include <gtest/gtest.h>
#include <memory>

// Define your test fixture
class TreeTest : public ::testing::Test {
protected:
  // Define any setup code that needs to be executed before each test
  void SetUp() override {
    // Initialize any objects or variables needed for the tests
  }

  // Define any teardown code that needs to be executed after each test
  void TearDown() override {
    // Clean up any resources allocated during the tests
  }

  // Add member variables that are common to all test cases
  Akr::Common::Tree<std::string, std::shared_ptr<Akr::Game::GObject>> tree_;
};

// Define test cases to test different functionalities of the Tree class
TEST_F(TreeTest, InsertAndFind) {
  // Insert nodes into the tree
  tree_.insert("node1", Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>(/* Initialize Akr::Game::GObject parameters */));
  tree_.insert("node2", Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>(/* Initialize Akr::Game::GObject parameters */));
  tree_.insert("node3", Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>(/* Initialize Akr::Game::GObject parameters */));

  // Find nodes in the tree
  auto node1 = tree_.find("node1");
  auto node2 = tree_.find("node2");
  auto node3 = tree_.find("node3");

  // Assert that the nodes were inserted and found successfully
  ASSERT_TRUE(node1 != nullptr);
  ASSERT_TRUE(node2 != nullptr);
  ASSERT_TRUE(node3 != nullptr);

  // Optionally, add more assertions to test other functionalities
}
// Define a fixture for the Scene tests
class SceneTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize any objects or variables needed for the tests
    scene.AddRootObject(Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>("testObject"));
  }

  // Declare any objects or variables needed for the tests
  Akr::Game::Scene scene;
};

// Test case for adding a GameObject to the scene
TEST_F(SceneTest, AddToScene) {
  // Add a new GameObject to the scene
  scene.AddToScene(Akr::Game::GObject::make_shared_gobject<Akr::Game::GObject>("newObject"));

  // Verify that the GameObject is added to the scene
  ASSERT_TRUE(scene.FindInScene("newObject") != nullptr);
}

// Test case for removing a GameObject from the scene
TEST_F(SceneTest, RemoveRootObject) {
  // Remove the root GameObject from the scene
  scene.RemoveRootObject("testObject");

  // Verify that the root GameObject is removed from the scene
  ASSERT_TRUE(scene.FindInScene("testObject") == nullptr);
}

// Test case for finding a GameObject in the scene
TEST_F(SceneTest, FindInScene) {
  // Find a GameObject in the scene
  auto gameObject = scene.FindInScene("testObject");

  // Verify that the GameObject is found in the scene
  ASSERT_TRUE(gameObject != nullptr);
  ASSERT_EQ(gameObject->GetName(), "testObject");
}

// Test case for deleting a GameObject from the scene
TEST_F(SceneTest, DeleteGObject) {
  // Find the GameObject to delete
  auto gameObject = scene.FindInScene("testObject");

  // Delete the GameObject from the scene
  scene.DeleteGObject(gameObject);

  // Verify that the GameObject is deleted from the scene
  ASSERT_TRUE(scene.FindInScene("testObject") == nullptr);
}

// Test case for getting the root GameObject of the scene
TEST_F(SceneTest, GetRootObject) {
  // Get the root GameObject of the scene
  auto& rootObject = scene.GetRootObject();

  // Verify that the correct root GameObject is returned
  ASSERT_EQ(rootObject.GetName(), "root");
}

// Test case for getting the root TreeNode of the scene
TEST_F(SceneTest, GetTreeRoot) {
  // Get the root TreeNode of the scene
  auto treeRoot = scene.GetTreeRoot();

  // Verify that the correct root TreeNode is returned
  ASSERT_TRUE(treeRoot != nullptr);
}

// Define the main function to run the tests
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
