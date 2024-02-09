#include "GObject.h"
#include "GObject.h"  // Include the header file that defines Akr::Game::GObject
#include "Tree.h"     // Include the header file that defines Tree and TreeNode
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
  tree_.insert("node1", std::make_shared<Akr::Game::GObject>(/* Initialize Akr::Game::GObject parameters */));
  tree_.insert("node2", std::make_shared<Akr::Game::GObject>(/* Initialize Akr::Game::GObject parameters */));
  tree_.insert("node3", std::make_shared<Akr::Game::GObject>(/* Initialize Akr::Game::GObject parameters */));

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

// You can define more test cases here to cover other functionalities of the Tree class

// Define the main function to run the tests
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
